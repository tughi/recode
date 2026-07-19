#include "Debugger.h"
#include "GUI.h"
#include "IR.h"
#include "Interpreter.h"
#include "String.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    DEBUGGER_MODE__STEP,
    DEBUGGER_MODE__NEXT,
    DEBUGGER_MODE__SOURCE_STEP,
    DEBUGGER_MODE__SOURCE_NEXT,
    DEBUGGER_MODE__CONTINUE,
} Debugger_Mode;

typedef struct {
    String name;
    IR_Value *value;
    bool indirect;
} Dbg_Binding;

typedef struct {
    Call_Frame *frame;
    Source_Location origin;
    Dbg_Binding *bindings;
    size_t bindings_size;
    size_t bindings_capacity;
} Frame_Debug_State;

typedef struct {
    uint8_t *address;
    size_t size;
    Source_Location location;
} Heap_Allocation;

typedef struct {
    char path[256];
    char name[64];
    IR_Type *type;
    uint8_t *address;
    size_t depth;
    bool expandable;
    bool expanded;
} Var_Node;

typedef struct {
    Observer observer;
    IR_Module *module;
    File *sources;
    Debugger_Mode mode;
    size_t next_depth;
    double last_render_time;
    IR_Instruction_List breakpoints;
    GUI gui;
    Call_Frame *current_frame;
    Call_Frame *selected_frame;
    Source_Location last_origin;
    Source_Location view_origin;
    Frame_Debug_State *frame_states;
    size_t frame_states_size;
    size_t frame_states_capacity;
    Heap_Allocation *heap_allocations;
    size_t heap_allocations_size;
    size_t heap_allocations_capacity;
    uint8_t *memory_target;
    size_t memory_target_size;
    char **expanded_paths;
    size_t expanded_paths_size;
    size_t expanded_paths_capacity;
    Var_Node *var_nodes;
    size_t var_nodes_size;
    size_t var_nodes_capacity;
    Panel *ir_panel;
    Panel *source_panel;
    bool source_stepping;
    double last_interaction_time;
    bool restart_requested;
} Debugger;

typedef struct {
    Panel panel;
    Scrollbar scrollbar;
} IR_Panel;

typedef struct {
    Panel panel;
    Scrollbar scrollbar;
} Source_Panel;

typedef struct {
    Panel panel;
    Scrollbar scrollbar;
} Stack_Panel;

typedef struct {
    Panel panel;
    Scrollbar scrollbar;
} Variables_Panel;

typedef struct {
    Panel panel;
    Scrollbar scrollbar;
} Memory_Panel;

static bool is_breakpoint(Debugger *debugger, IR_Instruction *instruction) {
    for (size_t i = 0; i < debugger->breakpoints.size; i++) {
        if (debugger->breakpoints.items[i] == instruction) {
            return true;
        }
    }
    return false;
}

static bool is_exit_call(Call_Frame *frame) {
    IR_Instruction *instruction = frame->instruction;
    if (instruction->kind != IR_INSTRUCTION__CALL) {
        return false;
    }
    IR_Value *callee_value = instruction->arguments.items[0];
    uint8_t *base = callee_value->kind <= IR_VALUE__GLOBAL_VARIABLE ? frame->globals_data : frame->frame_data;
    IR_Function *callee = *(IR_Function **)(base + callee_value->slot.offset);
    return callee != NULL && callee->is_external && callee->which == IR_EXTERNAL_FUNCTION__exit;
}

static IR_Instruction *find_instruction_at_line(IR_Module *module, size_t line) {
    for (size_t f = 0; f < module->functions.size; f++) {
        IR_Function *function = module->functions.items[f];
        for (size_t b = 0; b < function->blocks.size; b++) {
            IR_Block *block = function->blocks.items[b];
            for (size_t i = 0; i < block->instructions.size; i++) {
                IR_Instruction *instruction = block->instructions.items[i];
                if (instruction->location.line == line) {
                    return instruction;
                }
            }
        }
    }
    return NULL;
}

static IR_Instruction *find_instruction_at_origin_line(IR_Module *module, String source, size_t line) {
    for (size_t f = 0; f < module->functions.size; f++) {
        IR_Function *function = module->functions.items[f];
        if (function->is_external) {
            continue;
        }
        for (size_t b = 0; b < function->blocks.size; b++) {
            IR_Block *block = function->blocks.items[b];
            for (size_t i = 0; i < block->instructions.size; i++) {
                IR_Instruction *instruction = block->instructions.items[i];
                if (instruction->kind == IR_INSTRUCTION__DBG_LINE && instruction->dbg_line_instruction.location.line == line && string_equals(instruction->dbg_line_instruction.location.source, source)) {
                    return instruction;
                }
            }
        }
    }
    return NULL;
}

static void toggle_breakpoint(Debugger *debugger, IR_Instruction *instruction) {
    for (size_t i = 0; i < debugger->breakpoints.size; i++) {
        if (debugger->breakpoints.items[i] == instruction) {
            debugger->breakpoints.items[i] = debugger->breakpoints.items[--debugger->breakpoints.size];
            return;
        }
    }
    ir_instruction_list_add(&debugger->breakpoints, instruction);
}

static Frame_Debug_State *debugger_frame_state(Debugger *debugger, Call_Frame *frame) {
    for (size_t i = debugger->frame_states_size; i > 0; i--) {
        if (debugger->frame_states[i - 1].frame == frame) {
            return &debugger->frame_states[i - 1];
        }
    }
    return NULL;
}

static Source_Location debugger_current_origin(Debugger *debugger) {
    Frame_Debug_State *state = debugger_frame_state(debugger, debugger->current_frame);
    if (state == NULL) {
        return debugger->last_origin;
    }
    return state->origin;
}

static Source_Location source_panel_origin(Debugger *debugger) {
    if (debugger->view_origin.line != 0) {
        return debugger->view_origin;
    }
    return debugger_current_origin(debugger);
}

static Frame_Debug_State *sync_frame_states(Debugger *debugger, Call_Frame *frame, size_t depth) {
    while (debugger->frame_states_size > depth) {
        free(debugger->frame_states[--debugger->frame_states_size].bindings);
    }
    if (debugger->frame_states_size == depth && debugger->frame_states[depth - 1].frame != frame) {
        free(debugger->frame_states[--debugger->frame_states_size].bindings);
    }
    while (debugger->frame_states_size < depth) {
        if (debugger->frame_states_size == debugger->frame_states_capacity) {
            debugger->frame_states_capacity = debugger->frame_states_capacity == 0 ? 8 : debugger->frame_states_capacity * 2;
            debugger->frame_states = realloc(debugger->frame_states, debugger->frame_states_capacity * sizeof(Frame_Debug_State));
        }
        debugger->frame_states[debugger->frame_states_size++] = (Frame_Debug_State){.frame = frame};
    }
    return &debugger->frame_states[depth - 1];
}

static void record_binding(Frame_Debug_State *state, IR_Instruction *instruction) {
    String name = instruction->dbg_bind_instruction.variable_name;
    IR_Value *value = instruction->arguments.items[0];
    bool indirect = instruction->dbg_bind_instruction.indirect;
    for (size_t i = 0; i < state->bindings_size; i++) {
        if (string_equals(state->bindings[i].name, name)) {
            state->bindings[i].value = value;
            state->bindings[i].indirect = indirect;
            return;
        }
    }
    if (state->bindings_size == state->bindings_capacity) {
        state->bindings_capacity = state->bindings_capacity == 0 ? 8 : state->bindings_capacity * 2;
        state->bindings = realloc(state->bindings, state->bindings_capacity * sizeof(Dbg_Binding));
    }
    state->bindings[state->bindings_size++] = (Dbg_Binding){.name = name, .value = value, .indirect = indirect};
}

static Heap_Allocation *find_heap_allocation(Debugger *debugger, uint8_t *address) {
    for (size_t i = 0; i < debugger->heap_allocations_size; i++) {
        Heap_Allocation *allocation = &debugger->heap_allocations[i];
        if (address >= allocation->address && address < allocation->address + allocation->size) {
            return allocation;
        }
    }
    return NULL;
}

static void set_memory_target(Debugger *debugger, uint8_t *pointer, IR_Type *pointer_type) {
    if (pointer == NULL) {
        return;
    }
    debugger->memory_target = pointer;
    Heap_Allocation *allocation = find_heap_allocation(debugger, pointer);
    if (allocation != NULL) {
        debugger->memory_target_size = (size_t)(allocation->address + allocation->size - pointer);
    } else {
        debugger->memory_target_size = pointer_type->kind == IR_TYPE__PTR ? ir_type_size(pointer_type->pointee) : 256;
    }
}

static void debugger_on_heap_alloc(Observer *observer, uint8_t *address, size_t size, Source_Location location) {
    Debugger *debugger = (Debugger *)observer;
    if (debugger->heap_allocations_size == debugger->heap_allocations_capacity) {
        debugger->heap_allocations_capacity = debugger->heap_allocations_capacity == 0 ? 8 : debugger->heap_allocations_capacity * 2;
        debugger->heap_allocations = realloc(debugger->heap_allocations, debugger->heap_allocations_capacity * sizeof(Heap_Allocation));
    }
    debugger->heap_allocations[debugger->heap_allocations_size++] = (Heap_Allocation){.address = address, .size = size, .location = location};
}

static void debugger_on_heap_free(Observer *observer, uint8_t *address) {
    Debugger *debugger = (Debugger *)observer;
    for (size_t i = 0; i < debugger->heap_allocations_size; i++) {
        Heap_Allocation *allocation = &debugger->heap_allocations[i];
        if (allocation->address == address) {
            if (debugger->memory_target >= allocation->address && debugger->memory_target < allocation->address + allocation->size) {
                debugger->memory_target = NULL;
                debugger->memory_target_size = 0;
            }
            *allocation = debugger->heap_allocations[--debugger->heap_allocations_size];
            return;
        }
    }
}

static bool ir_line_has_breakpoint(Debugger *debugger, size_t line) {
    for (size_t i = 0; i < debugger->breakpoints.size; i++) {
        if (debugger->breakpoints.items[i]->location.line == line) {
            return true;
        }
    }
    return false;
}

static bool source_line_has_breakpoint(Debugger *debugger, size_t line) {
    String source = source_panel_origin(debugger).source;
    for (size_t i = 0; i < debugger->breakpoints.size; i++) {
        IR_Instruction *breakpoint = debugger->breakpoints.items[i];
        if (breakpoint->kind == IR_INSTRUCTION__DBG_LINE && breakpoint->dbg_line_instruction.location.line == line && string_equals(breakpoint->dbg_line_instruction.location.source, source)) {
            return true;
        }
    }
    return false;
}

static size_t frame_depth(Call_Frame *frame) {
    size_t depth = 0;
    for (Call_Frame *f = frame; f != NULL; f = f->caller) {
        depth++;
    }
    return depth;
}

static bool draw_token_text(Font font, Token *token, Color color, Vector2 *position, float max_right) {
    return draw_text(font, token->lexeme, color, position, max_right);
}

static Panel *ir_panel_pick(IR_Panel *ir_panel, Vector2 position) {
    (void)position;
    return &ir_panel->panel;
}

static void ir_panel_handle_step(IR_Panel *ir_panel, GUI *gui) {
    Debugger *debugger = gui->context;
    size_t line = debugger->current_frame->instruction->location.line;
    text_panel_scroll_to_line(&ir_panel->scrollbar, ir_panel->panel.bounds.height, line, debugger->module->lexed_file.lines_size, gui->font.baseSize);
}

static void navigate_to_source(Debugger *debugger, Source_Location location) {
    IR_Source_File_List *source_files = &debugger->module->source_files;
    for (size_t i = 0; i < source_files->size; i++) {
        if (string_equals(source_files->items[i], location.source)) {
            File *file = &debugger->sources[i];
            if (file->lines == NULL) {
                return;
            }
            debugger->view_origin = location;
            Source_Panel *source_panel = (Source_Panel *)debugger->source_panel;
            text_panel_scroll_to_line(&source_panel->scrollbar, source_panel->panel.bounds.height, location.line, file->lines_size, debugger->gui.font.baseSize);
            return;
        }
    }
}

static void navigate_to_directive(Debugger *debugger, size_t line) {
    Token *token = debugger->module->lexed_file.lines[line - 1];
    if (token->kind == TOKEN_KIND__SPACE) {
        token++;
    }
    if (token->kind != TOKEN_KIND__OTHER || token->other.value != '.') {
        return;
    }
    token++;
    if (token->kind != TOKEN_KIND__IDENTIFIER) {
        return;
    }
    if (string_equals_cstr(token->lexeme, "line")) {
        IR_Instruction *instruction = find_instruction_at_line(debugger->module, line);
        if (instruction != NULL && instruction->kind == IR_INSTRUCTION__DBG_LINE) {
            navigate_to_source(debugger, instruction->dbg_line_instruction.location);
        }
    } else if (string_equals_cstr(token->lexeme, "source")) {
        while (token->kind != TOKEN_KIND__INTEGER && token->kind != TOKEN_KIND__END_OF_LINE && token->kind != TOKEN_KIND__END_OF_FILE) {
            token++;
        }
        IR_Source_File_List *source_files = &debugger->module->source_files;
        if (token->kind == TOKEN_KIND__INTEGER && token->integer.value >= 1 && token->integer.value <= source_files->size) {
            navigate_to_source(debugger, (Source_Location){.source = source_files->items[token->integer.value - 1], .line = 1});
        }
    }
}

static void ir_panel_handle_input(IR_Panel *ir_panel, GUI *gui) {
    Debugger *debugger = gui->context;
    size_t lines_size = debugger->module->lexed_file.lines_size;
    size_t line = text_panel_scroll_input(gui->font, &ir_panel->panel, &ir_panel->scrollbar, lines_size);
    if (line != 0) {
        IR_Instruction *instruction = find_instruction_at_line(debugger->module, line);
        if (instruction != NULL) {
            toggle_breakpoint(debugger, instruction);
        }
        return;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse = GetMousePosition();
        Rectangle bounds = ir_panel->panel.bounds;
        float gutter_width = text_panel_gutter_width(gui->font, lines_size);
        if (mouse.x >= bounds.x + gutter_width && mouse.x < bounds.x + bounds.width - 8 && mouse.y >= bounds.y && mouse.y < bounds.y + bounds.height) {
            size_t clicked_line = (size_t)((mouse.y - bounds.y + ir_panel->scrollbar.scroll_y) / gui->font.baseSize) + 1;
            if (clicked_line <= lines_size) {
                navigate_to_directive(debugger, clicked_line);
            }
        }
    }
}

static void ir_panel_draw(IR_Panel *ir_panel, GUI *gui, Rectangle bounds) {
    Debugger *debugger = gui->context;
    static const Color colors[TOKEN_KINDS] = {
        [TOKEN_KIND__CHARACTER] = BEIGE,
        [TOKEN_KIND__COMMENT] = GRAY,
        [TOKEN_KIND__ERROR] = RED,
        [TOKEN_KIND__IDENTIFIER] = WHITE,
        [TOKEN_KIND__INTEGER] = BEIGE,
        [TOKEN_KIND__LABEL] = LIGHTGRAY,
        [TOKEN_KIND__OTHER] = LIGHTGRAY,
        [TOKEN_KIND__SPACE] = DARKGRAY,
        [TOKEN_KIND__STRING] = BEIGE,
    };
    Lexed_File *lexed_file = &debugger->module->lexed_file;
    size_t lines_size = lexed_file->lines_size;
    size_t current_line = debugger->current_frame == NULL ? 0 : debugger->current_frame->instruction->location.line;
    Font font = gui->font;
    int line_height = font.baseSize;
    float right = bounds.x + bounds.width;
    float bottom = bounds.y + bounds.height;
    Scrollbar *scrollbar = &ir_panel->scrollbar;
    size_t first_line = (size_t)(scrollbar->scroll_y / line_height);
    float y_origin = bounds.y - floorf(scrollbar->scroll_y - (float)first_line * line_height);

    int gutter_digits = 1;
    for (size_t n = lines_size; n >= 10; n /= 10) {
        gutter_digits++;
    }
    float gutter_width = text_panel_gutter_width(font, lines_size);

    BeginScissorMode((int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height);
    for (size_t i = first_line; i < lines_size; i++) {
        float row_y = y_origin + (float)(i - first_line) * line_height;
        if (row_y >= bottom) {
            break;
        }
        float source_x = text_panel_draw_gutter(font, bounds, row_y, i + 1, current_line, 0, gutter_digits, gutter_width, ir_line_has_breakpoint(debugger, i + 1));

        Vector2 position = {source_x, row_y};
        Token *line_token = lexed_file->lines[i];
        Token *first_token = line_token;
        if (first_token->kind == TOKEN_KIND__SPACE) {
            first_token++;
        }
        bool is_liveness_line = first_token->kind == TOKEN_KIND__OTHER && first_token->other.value == '[';
        bool is_directive_line = first_token->kind == TOKEN_KIND__OTHER && first_token->other.value == '.';
        while (line_token->kind != TOKEN_KIND__END_OF_LINE && line_token->kind != TOKEN_KIND__END_OF_FILE) {
            Color color = is_liveness_line || is_directive_line ? DARKGRAY : colors[line_token->kind];
            if (!draw_token_text(font, line_token, color, &position, right)) {
                break;
            }
            line_token++;
        }
    }
    EndScissorMode();

    draw_panel_scrollbar(bounds, (float)lines_size * line_height, scrollbar);
}

static IR_Panel make_ir_panel(float weight) {
    return (IR_Panel){
        .panel = {
            .draw = (void (*)(Panel *, GUI *, Rectangle))ir_panel_draw,
            .handle_input = (void (*)(Panel *, GUI *))ir_panel_handle_input,
            .handle_step = (void (*)(Panel *, GUI *))ir_panel_handle_step,
            .pick = (Panel * (*)(Panel *, Vector2)) ir_panel_pick,
            .weight = weight,
        },
    };
}

static File *source_panel_text(Debugger *debugger) {
    Source_Location origin = source_panel_origin(debugger);
    if (origin.line == 0) {
        return NULL;
    }
    IR_Source_File_List *source_files = &debugger->module->source_files;
    for (size_t i = 0; i < source_files->size; i++) {
        if (string_equals(source_files->items[i], origin.source)) {
            File *file = &debugger->sources[i];
            return file->lines != NULL ? file : NULL;
        }
    }
    return NULL;
}

static Panel *source_panel_pick(Source_Panel *source_panel, Vector2 position) {
    (void)position;
    return &source_panel->panel;
}

static void source_panel_handle_step(Source_Panel *source_panel, GUI *gui) {
    Debugger *debugger = gui->context;
    debugger->view_origin = (Source_Location){0};
    File *text = source_panel_text(debugger);
    if (text == NULL) {
        return;
    }
    size_t line = debugger_current_origin(debugger).line;
    text_panel_scroll_to_line(&source_panel->scrollbar, source_panel->panel.bounds.height, line, text->lines_size, gui->font.baseSize);
}

static void source_panel_handle_input(Source_Panel *source_panel, GUI *gui) {
    Debugger *debugger = gui->context;
    File *text = source_panel_text(debugger);
    if (text == NULL) {
        return;
    }
    size_t line = text_panel_scroll_input(gui->font, &source_panel->panel, &source_panel->scrollbar, text->lines_size);
    if (line != 0) {
        IR_Instruction *instruction = find_instruction_at_origin_line(debugger->module, source_panel_origin(debugger).source, line);
        if (instruction != NULL) {
            toggle_breakpoint(debugger, instruction);
        }
    }
}

static void source_panel_draw(Source_Panel *source_panel, GUI *gui, Rectangle bounds) {
    Debugger *debugger = gui->context;
    File *text = source_panel_text(debugger);
    if (text == NULL) {
        return;
    }
    size_t lines_size = text->lines_size;
    Source_Location origin = debugger_current_origin(debugger);
    size_t current_line = debugger->current_frame != NULL && string_equals(source_panel_origin(debugger).source, origin.source) ? origin.line : 0;
    Font font = gui->font;
    int line_height = font.baseSize;
    float right = bounds.x + bounds.width;
    float bottom = bounds.y + bounds.height;
    Scrollbar *scrollbar = &source_panel->scrollbar;
    size_t first_line = (size_t)(scrollbar->scroll_y / line_height);
    float y_origin = bounds.y - floorf(scrollbar->scroll_y - (float)first_line * line_height);

    int gutter_digits = 1;
    for (size_t n = lines_size; n >= 10; n /= 10) {
        gutter_digits++;
    }
    float gutter_width = text_panel_gutter_width(font, lines_size);

    BeginScissorMode((int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height);
    for (size_t i = first_line; i < lines_size; i++) {
        float row_y = y_origin + (float)(i - first_line) * line_height;
        if (row_y >= bottom) {
            break;
        }
        float source_x = text_panel_draw_gutter(font, bounds, row_y, i + 1, current_line, debugger->view_origin.line, gutter_digits, gutter_width, source_line_has_breakpoint(debugger, i + 1));
        Vector2 position = {source_x, row_y};
        draw_text(font, text->lines[i], LIGHTGRAY, &position, right);
    }
    EndScissorMode();

    draw_panel_scrollbar(bounds, (float)lines_size * line_height, scrollbar);
}

static Source_Panel make_source_panel(float weight) {
    return (Source_Panel){
        .panel = {
            .draw = (void (*)(Panel *, GUI *, Rectangle))source_panel_draw,
            .handle_input = (void (*)(Panel *, GUI *))source_panel_handle_input,
            .handle_step = (void (*)(Panel *, GUI *))source_panel_handle_step,
            .pick = (Panel * (*)(Panel *, Vector2)) source_panel_pick,
            .weight = weight,
        },
    };
}

static void stack_panel_draw(Stack_Panel *stack_panel, GUI *gui, Rectangle bounds) {
    Debugger *debugger = gui->context;
    if (debugger->current_frame == NULL) {
        return;
    }
    Font font = gui->font;
    int line_height = font.baseSize;
    float bottom = bounds.y + bounds.height;
    BeginScissorMode((int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height);
    float y = bounds.y - floorf(stack_panel->scrollbar.scroll_y);
    for (Call_Frame *f = debugger->current_frame; f != NULL; f = f->caller) {
        if (y >= bottom) {
            break;
        }
        if (y + line_height > bounds.y) {
            if (f == debugger->selected_frame) {
                DrawRectangle((int)bounds.x, (int)y, (int)bounds.width, line_height, DARKBLUE);
            }
            char name[128];
            snprintf(name, sizeof(name), "%.*s", STRING(f->function->name));
            Frame_Debug_State *frame_state = debugger_frame_state(debugger, f);
            Source_Location frame_location = frame_state != NULL && frame_state->origin.line != 0 ? frame_state->origin : f->instruction->location;
            String source = frame_location.source;
            for (size_t i = source.length; i > 0; i--) {
                if (source.content[i - 1] == '/') {
                    source.content += i;
                    source.length -= i;
                    break;
                }
            }
            char location[128];
            snprintf(location, sizeof(location), "%.*s:%zu", STRING(source), frame_location.line);
            Vector2 location_size = MeasureTextEx(font, location, line_height, 0);
            DrawTextEx(font, name, (Vector2){bounds.x, y}, line_height, 0, RAYWHITE);
            DrawTextEx(font, location, (Vector2){bounds.x + bounds.width - location_size.x, y}, line_height, 0, GRAY);
        }
        y += line_height;
    }
    EndScissorMode();
    float content_height = (float)frame_depth(debugger->current_frame) * line_height;
    draw_panel_scrollbar(bounds, content_height, &stack_panel->scrollbar);
}

static void stack_panel_handle_input(Stack_Panel *stack_panel, GUI *gui) {
    Debugger *debugger = gui->context;
    if (debugger->current_frame == NULL) {
        return;
    }
    int line_height = gui->font.baseSize;
    float content_height = (float)frame_depth(debugger->current_frame) * line_height;
    scrollbar_wheel_input(&stack_panel->scrollbar, stack_panel->panel.bounds.height, content_height, line_height);

    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        return;
    }
    Vector2 mouse = GetMousePosition();
    Rectangle bounds = stack_panel->panel.bounds;
    if (!CheckCollisionPointRec(mouse, bounds) || mouse.x >= bounds.x + bounds.width - 8) {
        return;
    }
    size_t row = (size_t)((mouse.y - bounds.y + stack_panel->scrollbar.scroll_y) / line_height);
    Call_Frame *frame = debugger->current_frame;
    for (size_t i = 0; i < row && frame != NULL; i++) {
        frame = frame->caller;
    }
    if (frame == NULL) {
        return;
    }
    debugger->selected_frame = frame;
    Frame_Debug_State *frame_state = debugger_frame_state(debugger, frame);
    if (frame_state != NULL && frame_state->origin.line != 0) {
        navigate_to_source(debugger, frame_state->origin);
    } else {
        IR_Panel *ir_panel = (IR_Panel *)debugger->ir_panel;
        text_panel_scroll_to_line(&ir_panel->scrollbar, ir_panel->panel.bounds.height, frame->instruction->location.line, debugger->module->lexed_file.lines_size, gui->font.baseSize);
    }
}

static void stack_panel_handle_step(Stack_Panel *stack_panel, GUI *gui) {
    (void)gui;
    stack_panel->scrollbar.scroll_y = 0;
}

static Panel *stack_panel_pick(Stack_Panel *stack_panel, Vector2 position) {
    (void)position;
    return &stack_panel->panel;
}

static Stack_Panel make_stack_panel(float weight) {
    return (Stack_Panel){
        .panel = {
            .draw = (void (*)(Panel *, GUI *, Rectangle))stack_panel_draw,
            .handle_input = (void (*)(Panel *, GUI *))stack_panel_handle_input,
            .handle_step = (void (*)(Panel *, GUI *))stack_panel_handle_step,
            .pick = (Panel * (*)(Panel *, Vector2)) stack_panel_pick,
            .weight = weight,
        },
    };
}

static bool is_primitive_type(IR_Type *type) {
    switch (type->kind) {
    case IR_TYPE__BOOL:
    case IR_TYPE__I8:
    case IR_TYPE__I16:
    case IR_TYPE__I32:
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
    case IR_TYPE__U8:
    case IR_TYPE__U16:
    case IR_TYPE__U32:
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        return true;
    default:
        return false;
    }
}

static size_t format_typed(char *buf, size_t size, IR_Type *type, uint8_t *address) {
    switch (type->kind) {
    case IR_TYPE__BOOL:
        return (size_t)snprintf(buf, size, "%s", *(uint8_t *)address ? "true" : "false");
    case IR_TYPE__I8:
        return (size_t)snprintf(buf, size, "%d", *(int8_t *)address);
    case IR_TYPE__I16:
        return (size_t)snprintf(buf, size, "%d", *(int16_t *)address);
    case IR_TYPE__I32:
        return (size_t)snprintf(buf, size, "%d", *(int32_t *)address);
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        return (size_t)snprintf(buf, size, "%lld", (long long)*(int64_t *)address);
    case IR_TYPE__U8:
        return (size_t)snprintf(buf, size, "%u", *(uint8_t *)address);
    case IR_TYPE__U16:
        return (size_t)snprintf(buf, size, "%u", *(uint16_t *)address);
    case IR_TYPE__U32:
        return (size_t)snprintf(buf, size, "%u", *(uint32_t *)address);
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        return (size_t)snprintf(buf, size, "%llu", (unsigned long long)*(uint64_t *)address);
    case IR_TYPE__PTR:
    case IR_TYPE__MULTI_PTR:
    case IR_TYPE__PROC:
        return (size_t)snprintf(buf, size, "%p", *(void **)address);
    case IR_TYPE__STRUCT: {
        size_t n = (size_t)snprintf(buf, size, "{");
        for (size_t i = 0; i < type->struct_field_count; i++) {
            IR_Struct_Field *field = type->struct_fields[i];
            n += (size_t)snprintf(buf + n, n < size ? size - n : 0, "%s .%.*s = ", i == 0 ? "" : ",", STRING(field->name));
            n += format_typed(buf + n, n < size ? size - n : 0, field->type, address + ir_struct_field_offset(type, i));
        }
        n += (size_t)snprintf(buf + n, n < size ? size - n : 0, " }");
        return n;
    }
    case IR_TYPE__VOID:
        return (size_t)snprintf(buf, size, "(void)");
    default:
        return (size_t)snprintf(buf, size, "<%zu bytes>", ir_type_size(type));
    }
}

static uint8_t *binding_address(Call_Frame *frame, Dbg_Binding *binding, IR_Type **display_type) {
    IR_Value *value = binding->value;
    uint8_t *base = value->kind <= IR_VALUE__GLOBAL_VARIABLE ? frame->globals_data : frame->frame_data;
    uint8_t *slot = base + value->slot.offset;
    if (binding->indirect) {
        *display_type = value->type->pointee;
        return *(uint8_t **)slot;
    }
    *display_type = value->type;
    return slot;
}

static bool is_path_expanded(Debugger *debugger, const char *path) {
    for (size_t i = 0; i < debugger->expanded_paths_size; i++) {
        if (strcmp(debugger->expanded_paths[i], path) == 0) {
            return true;
        }
    }
    return false;
}

static void toggle_path_expanded(Debugger *debugger, const char *path) {
    for (size_t i = 0; i < debugger->expanded_paths_size; i++) {
        if (strcmp(debugger->expanded_paths[i], path) == 0) {
            free(debugger->expanded_paths[i]);
            debugger->expanded_paths[i] = debugger->expanded_paths[--debugger->expanded_paths_size];
            return;
        }
    }
    if (debugger->expanded_paths_size == debugger->expanded_paths_capacity) {
        debugger->expanded_paths_capacity = debugger->expanded_paths_capacity == 0 ? 8 : debugger->expanded_paths_capacity * 2;
        debugger->expanded_paths = realloc(debugger->expanded_paths, debugger->expanded_paths_capacity * sizeof(char *));
    }
    debugger->expanded_paths[debugger->expanded_paths_size++] = strdup(path);
}

static Var_Node *new_var_node(Debugger *debugger) {
    if (debugger->var_nodes_size == debugger->var_nodes_capacity) {
        debugger->var_nodes_capacity = debugger->var_nodes_capacity == 0 ? 16 : debugger->var_nodes_capacity * 2;
        debugger->var_nodes = realloc(debugger->var_nodes, debugger->var_nodes_capacity * sizeof(Var_Node));
    }
    return &debugger->var_nodes[debugger->var_nodes_size++];
}

static void add_var_node(Debugger *debugger, const char *path, const char *name, IR_Type *type, uint8_t *address, size_t depth) {
    Var_Node *node = new_var_node(debugger);
    snprintf(node->path, sizeof(node->path), "%s", path);
    snprintf(node->name, sizeof(node->name), "%s", name);
    node->type = type;
    node->address = address;
    node->depth = depth;
    bool is_pointer = type->kind == IR_TYPE__PTR || type->kind == IR_TYPE__MULTI_PTR;
    IR_Type *target = is_pointer ? type->pointee : type;
    uint8_t *target_address = is_pointer && address != NULL ? *(uint8_t **)address : address;
    if (target_address == NULL) {
        node->expandable = false;
    } else if (target->kind == IR_TYPE__STRUCT) {
        node->expandable = true;
    } else {
        node->expandable = is_pointer && ir_type_size(target) > 0;
    }
    node->expanded = node->expandable && is_path_expanded(debugger, node->path);
    if (!node->expanded) {
        return;
    }
    if (target->kind == IR_TYPE__STRUCT) {
        for (size_t i = 0; i < target->struct_field_count; i++) {
            IR_Struct_Field *field = target->struct_fields[i];
            char field_name[64];
            snprintf(field_name, sizeof(field_name), "%.*s", STRING(field->name));
            char field_path[256];
            snprintf(field_path, sizeof(field_path), "%s.%s", path, field_name);
            add_var_node(debugger, field_path, field_name, field->type, target_address + ir_struct_field_offset(target, i), depth + 1);
        }
    } else if (type->kind == IR_TYPE__PTR) {
        char child_path[256];
        snprintf(child_path, sizeof(child_path), "%s.*", path);
        add_var_node(debugger, child_path, "*", target, target_address, depth + 1);
    } else {
        size_t element_size = ir_type_size(target);
        size_t count = 1;
        Heap_Allocation *allocation = find_heap_allocation(debugger, target_address);
        if (allocation != NULL) {
            count = (size_t)(allocation->address + allocation->size - target_address) / element_size;
            if (count > 1024) {
                count = 1024;
            }
        }
        size_t visible = 10;
        char more_path[256];
        while (visible < count) {
            snprintf(more_path, sizeof(more_path), "%s[%zu..]", path, visible);
            if (!is_path_expanded(debugger, more_path)) {
                break;
            }
            visible += 10;
        }
        if (visible > count) {
            visible = count;
        }
        for (size_t i = 0; i < visible; i++) {
            char element_name[32];
            snprintf(element_name, sizeof(element_name), "[%zu]", i);
            char element_path[256];
            snprintf(element_path, sizeof(element_path), "%s%s", path, element_name);
            add_var_node(debugger, element_path, element_name, target, target_address + i * element_size, depth + 1);
        }
        if (visible < count) {
            Var_Node *more = new_var_node(debugger);
            snprintf(more->path, sizeof(more->path), "%s", more_path);
            snprintf(more->name, sizeof(more->name), "... (%zu more)", count - visible);
            more->type = NULL;
            more->address = NULL;
            more->depth = depth + 1;
            more->expandable = true;
            more->expanded = false;
        }
    }
}

static void build_var_nodes(Debugger *debugger) {
    debugger->var_nodes_size = 0;
    if (debugger->current_frame == NULL) {
        return;
    }
    Frame_Debug_State *state = debugger_frame_state(debugger, debugger->selected_frame);
    if (state == NULL) {
        return;
    }
    for (size_t i = 0; i < state->bindings_size; i++) {
        Dbg_Binding *binding = &state->bindings[i];
        IR_Type *display_type;
        uint8_t *address = binding_address(debugger->selected_frame, binding, &display_type);
        char name[64];
        snprintf(name, sizeof(name), "%.*s", STRING(binding->name));
        add_var_node(debugger, name, name, display_type, address, 0);
    }
}

static void draw_variable_line(Font font, Rectangle bounds, float y, Var_Node *node) {
    int line_height = font.baseSize;
    int advance = font.glyphs[GetGlyphIndex(font, '0')].advanceX;
    float x = bounds.x + (float)(node->depth * 2 * advance);
    if (node->expandable) {
        char marker[2] = {node->expanded ? '-' : '+', '\0'};
        DrawTextEx(font, marker, (Vector2){x, y}, line_height, 0, GRAY);
    }
    x += 2 * advance;

    if (node->type == NULL) {
        DrawTextEx(font, node->name, (Vector2){x, y}, line_height, 0, GRAY);
        return;
    }

    DrawTextEx(font, node->name, (Vector2){x, y}, line_height, 0, RAYWHITE);
    Vector2 name_size = MeasureTextEx(font, node->name, line_height, 0);

    char type_text[128];
    FILE *f = fmemopen(type_text, sizeof(type_text), "w");
    fputs(": ", f);
    fprint_ir_type(f, node->type);
    fclose(f);
    DrawTextEx(font, type_text, (Vector2){x + name_size.x, y}, line_height, 0, GRAY);

    char value_text[256];
    if (node->address == NULL) {
        snprintf(value_text, sizeof(value_text), "<uninitialized>");
    } else if (is_primitive_type(node->type)) {
        format_typed(value_text, sizeof(value_text), node->type, node->address);
    } else {
        return;
    }
    Vector2 value_size = MeasureTextEx(font, value_text, line_height, 0);
    DrawTextEx(font, value_text, (Vector2){bounds.x + bounds.width - value_size.x, y}, line_height, 0, RAYWHITE);
}

static void variables_panel_draw(Variables_Panel *variables_panel, GUI *gui, Rectangle bounds) {
    Debugger *debugger = gui->context;
    if (debugger->current_frame == NULL) {
        return;
    }
    build_var_nodes(debugger);
    Font font = gui->font;
    int line_height = font.baseSize;
    BeginScissorMode((int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height);
    float y = bounds.y - floorf(variables_panel->scrollbar.scroll_y);
    float bottom = bounds.y + bounds.height;
    for (size_t i = 0; i < debugger->var_nodes_size; i++) {
        if (y + line_height > bounds.y && y < bottom) {
            draw_variable_line(font, bounds, y, &debugger->var_nodes[i]);
        }
        y += line_height;
    }
    EndScissorMode();
    float content_height = (float)debugger->var_nodes_size * line_height;
    draw_panel_scrollbar(bounds, content_height, &variables_panel->scrollbar);
}

static void variables_panel_handle_input(Variables_Panel *variables_panel, GUI *gui) {
    Debugger *debugger = gui->context;
    build_var_nodes(debugger);
    int line_height = gui->font.baseSize;
    float content_height = (float)debugger->var_nodes_size * line_height;
    scrollbar_wheel_input(&variables_panel->scrollbar, variables_panel->panel.bounds.height, content_height, line_height);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse = GetMousePosition();
        Rectangle bounds = variables_panel->panel.bounds;
        if (CheckCollisionPointRec(mouse, bounds) && mouse.x < bounds.x + bounds.width - 8) {
            size_t row = (size_t)((mouse.y - bounds.y + variables_panel->scrollbar.scroll_y) / line_height);
            if (row < debugger->var_nodes_size) {
                Var_Node *node = &debugger->var_nodes[row];
                if (node->expandable) {
                    toggle_path_expanded(debugger, node->path);
                }
                if (node->address != NULL) {
                    if (node->type->kind == IR_TYPE__PTR || node->type->kind == IR_TYPE__MULTI_PTR) {
                        set_memory_target(debugger, *(uint8_t **)node->address, node->type);
                    } else {
                        debugger->memory_target = node->address;
                        debugger->memory_target_size = ir_type_size(node->type);
                    }
                }
            }
        }
    }
}

static void variables_panel_handle_step(Variables_Panel *variables_panel, GUI *gui) {
    (void)gui;
    variables_panel->scrollbar.scroll_y = 0;
}

static Panel *variables_panel_pick(Variables_Panel *variables_panel, Vector2 position) {
    (void)position;
    return &variables_panel->panel;
}

static Variables_Panel make_variables_panel(float weight) {
    return (Variables_Panel){
        .panel = {
            .draw = (void (*)(Panel *, GUI *, Rectangle))variables_panel_draw,
            .handle_input = (void (*)(Panel *, GUI *))variables_panel_handle_input,
            .handle_step = (void (*)(Panel *, GUI *))variables_panel_handle_step,
            .pick = (Panel * (*)(Panel *, Vector2)) variables_panel_pick,
            .weight = weight,
        },
    };
}

static void memory_panel_draw(Memory_Panel *memory_panel, GUI *gui, Rectangle bounds) {
    Debugger *debugger = gui->context;
    if (debugger->memory_target == NULL) {
        return;
    }
    Font font = gui->font;
    int line_height = font.baseSize;
    int advance = font.glyphs[GetGlyphIndex(font, '0')].advanceX;
    size_t rows = (debugger->memory_target_size + 15) / 16;
    BeginScissorMode((int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height);
    float y = bounds.y - floorf(memory_panel->scrollbar.scroll_y);
    float bottom = bounds.y + bounds.height;
    if (y + line_height > bounds.y && y < bottom) {
        char header[64];
        snprintf(header, sizeof(header), "%p, %zu bytes", (void *)debugger->memory_target, debugger->memory_target_size);
        DrawTextEx(font, header, (Vector2){bounds.x, y}, line_height, 0, GRAY);
    }
    y += line_height;
    for (size_t row = 0; row < rows; row++) {
        if (y + line_height > bounds.y && y < bottom) {
            char offset_text[8];
            snprintf(offset_text, sizeof(offset_text), "%04zx", row * 16);
            DrawTextEx(font, offset_text, (Vector2){bounds.x, y}, line_height, 0, DARKGRAY);
            char bytes_text[3 * 16 + 1];
            char ascii_text[16 + 3];
            size_t ascii_size = 0;
            ascii_text[ascii_size++] = '|';
            for (size_t i = 0; i < 16; i++) {
                size_t index = row * 16 + i;
                if (index < debugger->memory_target_size) {
                    uint8_t byte = debugger->memory_target[index];
                    snprintf(bytes_text + i * 3, 4, "%02X ", byte);
                    ascii_text[ascii_size++] = byte >= 32 && byte < 127 ? (char)byte : '.';
                } else {
                    memcpy(bytes_text + i * 3, "   ", 3);
                }
            }
            bytes_text[3 * 16] = '\0';
            ascii_text[ascii_size++] = '|';
            ascii_text[ascii_size] = '\0';
            DrawTextEx(font, bytes_text, (Vector2){bounds.x + 6 * advance, y}, line_height, 0, RAYWHITE);
            DrawTextEx(font, ascii_text, (Vector2){bounds.x + (6 + 3 * 16 + 1) * advance, y}, line_height, 0, LIGHTGRAY);
        }
        y += line_height;
    }
    EndScissorMode();
    draw_panel_scrollbar(bounds, (float)(rows + 1) * line_height, &memory_panel->scrollbar);
}

static void memory_panel_handle_input(Memory_Panel *memory_panel, GUI *gui) {
    Debugger *debugger = gui->context;
    int line_height = gui->font.baseSize;
    size_t rows = debugger->memory_target == NULL ? 0 : (debugger->memory_target_size + 15) / 16 + 1;
    float content_height = (float)rows * line_height;
    scrollbar_wheel_input(&memory_panel->scrollbar, memory_panel->panel.bounds.height, content_height, line_height);
}

static void memory_panel_handle_step(Memory_Panel *memory_panel, GUI *gui) {
    (void)gui;
    memory_panel->scrollbar.scroll_y = 0;
}

static Panel *memory_panel_pick(Memory_Panel *memory_panel, Vector2 position) {
    (void)position;
    return &memory_panel->panel;
}

static Memory_Panel make_memory_panel(float weight) {
    return (Memory_Panel){
        .panel = {
            .draw = (void (*)(Panel *, GUI *, Rectangle))memory_panel_draw,
            .handle_input = (void (*)(Panel *, GUI *))memory_panel_handle_input,
            .handle_step = (void (*)(Panel *, GUI *))memory_panel_handle_step,
            .pick = (Panel * (*)(Panel *, Vector2)) memory_panel_pick,
            .weight = weight,
        },
    };
}

static void debugger_render_frame(Debugger *debugger) {
    gui_render_frame(&debugger->gui);
    if (debugger->gui.active_panel == debugger->source_panel) {
        debugger->source_stepping = true;
    } else if (debugger->gui.active_panel == debugger->ir_panel) {
        debugger->source_stepping = false;
    }
}

static void debugger_on_step(Observer *observer, Call_Frame *current_frame, bool *aborted) {
    Debugger *debugger = (Debugger *)observer;

    size_t depth = frame_depth(current_frame);
    Frame_Debug_State *state = sync_frame_states(debugger, current_frame, depth);

    IR_Instruction *instruction = current_frame->instruction;
    if (instruction->kind == IR_INSTRUCTION__DBG_LINE) {
        state->origin = instruction->dbg_line_instruction.location;
    } else if (instruction->kind == IR_INSTRUCTION__DBG_BIND) {
        record_binding(state, instruction);
    }

    bool at_breakpoint = is_breakpoint(debugger, instruction) || is_exit_call(current_frame);
    if (instruction->kind == IR_INSTRUCTION__DBG_LINE) {
        bool source_pause = debugger->mode == DEBUGGER_MODE__SOURCE_STEP || (debugger->mode == DEBUGGER_MODE__SOURCE_NEXT && depth <= debugger->next_depth);
        if (!at_breakpoint && !source_pause) {
            return;
        }
    } else if (instruction->kind == IR_INSTRUCTION__DBG_BIND && !at_breakpoint) {
        return;
    }
    bool paused = at_breakpoint || instruction->kind == IR_INSTRUCTION__DBG_LINE || instruction->kind == IR_INSTRUCTION__DBG_BIND || debugger->mode == DEBUGGER_MODE__STEP || (debugger->mode == DEBUGGER_MODE__NEXT && depth <= debugger->next_depth);
    if (!paused) {
        // Redraw every 0.25s to keep the window responsive, at 60 Hz around mouse activity.
        double now = GetTime();
        double interval = now - debugger->last_interaction_time < 1.0 ? 1.0 / 60 : 0.25;
        if (now - debugger->last_render_time < interval) {
            return;
        }
        debugger->last_render_time = now;
        if (WindowShouldClose()) {
            exit(0);
        }
        debugger_render_frame(debugger);
        Vector2 mouse_delta = GetMouseDelta();
        if (mouse_delta.x != 0 || mouse_delta.y != 0 || GetMouseWheelMove() != 0 || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            debugger->last_interaction_time = now;
        }
        if (IsKeyPressed(KEY_SPACE)) {
            debugger->mode = DEBUGGER_MODE__STEP;
        } else if (IsKeyPressed(KEY_R)) {
            debugger->restart_requested = true;
            *aborted = true;
        }
        return;
    }

    debugger->current_frame = current_frame;
    debugger->selected_frame = current_frame;
    debugger->last_origin = debugger_current_origin(debugger);

    debugger->gui.root_panel->bounds = (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()};
    debugger->gui.root_panel->handle_step(debugger->gui.root_panel, &debugger->gui);

    while (!WindowShouldClose()) {
        debugger_render_frame(debugger);

        if (IsKeyPressed(KEY_S)) {
            if (debugger->source_stepping) {
                debugger->mode = DEBUGGER_MODE__SOURCE_STEP;
                debugger->current_frame = NULL;
            } else {
                debugger->mode = DEBUGGER_MODE__STEP;
            }
            return;
        }
        if (IsKeyPressed(KEY_N)) {
            debugger->mode = debugger->source_stepping ? DEBUGGER_MODE__SOURCE_NEXT : DEBUGGER_MODE__NEXT;
            debugger->next_depth = depth;
            debugger->current_frame = NULL;
            return;
        }
        if (IsKeyPressed(KEY_C)) {
            debugger->mode = DEBUGGER_MODE__CONTINUE;
            debugger->current_frame = NULL;
            return;
        }
        if (IsKeyPressed(KEY_R)) {
            debugger->restart_requested = true;
            *aborted = true;
            return;
        }
    }
    debugger->mode = DEBUGGER_MODE__CONTINUE;
}

static void debugger_restart(Debugger *debugger) {
    for (size_t i = 0; i < debugger->heap_allocations_size; i++) {
        free(debugger->heap_allocations[i].address);
    }
    debugger->heap_allocations_size = 0;
    debugger->memory_target = NULL;
    debugger->memory_target_size = 0;
    while (debugger->frame_states_size > 0) {
        free(debugger->frame_states[--debugger->frame_states_size].bindings);
    }
    debugger->current_frame = NULL;
    debugger->selected_frame = NULL;
    debugger->last_origin = (Source_Location){0};
    debugger->view_origin = (Source_Location){0};
    debugger->mode = DEBUGGER_MODE__STEP;
    debugger->next_depth = 0;
    debugger->restart_requested = false;
}

int64_t debug(IR_Module *module, int argc, char *argv[]) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Code IR Debugger");
    SetExitKey(KEY_Q);
    SetTargetFPS(60);

    bool has_origins = module->source_files.size > 0;
    Source_Panel source_panel = make_source_panel(0.5f);
    IR_Panel ir_panel = make_ir_panel(has_origins ? 1.0f : 0.5f);
    Panel *left_panel_children[] = {&source_panel.panel, &ir_panel.panel};
    Split_Panel left_panel = make_split_panel(0.5f, SPLIT_DIRECTION__VERTICAL, left_panel_children, 2);
    Stack_Panel stack_panel = make_stack_panel(0.25f);
    Variables_Panel variables_panel = make_variables_panel(0.5f);
    Memory_Panel memory_panel = make_memory_panel(1.0f);
    Panel *right_panel_children[] = {&stack_panel.panel, &variables_panel.panel, &memory_panel.panel};
    Split_Panel right_panel = make_split_panel(1.0f, SPLIT_DIRECTION__VERTICAL, right_panel_children, 3);
    Panel *split_children[] = {has_origins ? &left_panel.panel : &ir_panel.panel, &right_panel.panel};
    Split_Panel split_panel = make_split_panel(1.0f, SPLIT_DIRECTION__HORIZONTAL, split_children, sizeof(split_children) / sizeof(*split_children));
    Debugger debugger = {
        .observer = {.on_step = debugger_on_step, .on_heap_alloc = debugger_on_heap_alloc, .on_heap_free = debugger_on_heap_free},
        .module = module,
        .sources = ir_load_source_files(module),
        .mode = DEBUGGER_MODE__STEP,
        .next_depth = 0,
        .gui = {.font = load_bitmap_font("fonts/Code.font"), .root_panel = &split_panel.panel},
        .ir_panel = &ir_panel.panel,
        .source_panel = &source_panel.panel,
        .source_stepping = has_origins,
    };
    debugger.gui.context = &debugger;
    int64_t result = interpret(module, argc, argv, &debugger.observer, false);
    while (debugger.restart_requested) {
        debugger_restart(&debugger);
        result = interpret(module, argc, argv, &debugger.observer, false);
    }

    if (debugger.heap_allocations_size > 0) {
        size_t total = 0;
        for (size_t i = 0; i < debugger.heap_allocations_size; i++) {
            total += debugger.heap_allocations[i].size;
        }
        fprintf(stderr, "Leaked %zu allocation(s), %zu bytes:\n", debugger.heap_allocations_size, total);
        for (size_t i = 0; i < debugger.heap_allocations_size; i++) {
            Heap_Allocation *allocation = &debugger.heap_allocations[i];
            fprintf(stderr, "  %.*s:%zu:%zu: %zu bytes at %p\n", STRING(module->lexed_file.file.path), allocation->location.line, allocation->location.column, allocation->size, (void *)allocation->address);
        }
    }

    UnloadFont(debugger.gui.font);
    CloseWindow();
    return result;
}
