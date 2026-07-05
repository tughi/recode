#include "Debugger.h"
#include "IR.h"
#include "Interpreter.h"
#include "String.h"
#include <limits.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    DEBUGGER_MODE__STEP,
    DEBUGGER_MODE__NEXT,
    DEBUGGER_MODE__CONTINUE,
} Debugger_Mode;

typedef struct Panel Panel;

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
    Observer observer;
    IR_Module *module;
    File *sources;
    Debugger_Mode mode;
    size_t next_depth;
    double last_render_time;
    IR_Instruction_List breakpoints;
    Font font;
    Call_Frame *current_frame;
    Frame_Debug_State *frame_states;
    size_t frame_states_size;
    size_t frame_states_capacity;
    Panel *root_panel;
    Panel *active_panel;
    double last_interaction_time;
} Debugger;

struct Panel {
    void (*draw)(Panel *self, Debugger *debugger, Rectangle bounds);
    void (*handle_input)(Panel *self, Debugger *debugger);
    void (*handle_step)(Panel *self, Debugger *debugger);
    Panel *(*pick)(Panel *self, Vector2 position);
    Rectangle bounds;
    float weight;
};

typedef struct {
    float scroll_y;
    bool dragging;
    float drag_offset;
    float opacity;
} Scrollbar;

typedef struct {
    Panel panel;
    Scrollbar scrollbar;
} IR_Panel;

typedef struct {
    Panel panel;
    Scrollbar scrollbar;
} Source_Panel;

typedef enum {
    SPLIT_DIRECTION__HORIZONTAL,
    SPLIT_DIRECTION__VERTICAL,
} Split_Direction;

typedef struct {
    Panel panel;
    Split_Direction direction;
    Panel **children;
    size_t children_size;
    size_t dragged_gutter;
} Split_Panel;

typedef struct {
    Panel panel;
} Stack_Panel;

typedef struct {
    Panel panel;
    Scrollbar scrollbar;
} Variables_Panel;

#define GUTTER_SIZE 4

static bool is_breakpoint(Debugger *debugger, IR_Instruction *instruction) {
    for (size_t i = 0; i < debugger->breakpoints.size; i++) {
        if (debugger->breakpoints.items[i] == instruction) {
            return true;
        }
    }
    return false;
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
        return (Source_Location){0};
    }
    return state->origin;
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

static bool ir_line_has_breakpoint(Debugger *debugger, size_t line) {
    for (size_t i = 0; i < debugger->breakpoints.size; i++) {
        if (debugger->breakpoints.items[i]->location.line == line) {
            return true;
        }
    }
    return false;
}

static bool source_line_has_breakpoint(Debugger *debugger, size_t line) {
    String source = debugger_current_origin(debugger).source;
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

static bool draw_text(Font font, String text, Color color, Vector2 *position, float max_right) {
    for (size_t i = 0; i < text.length; i++) {
        int codepoint = text.content[i];
        int glyph_index = GetGlyphIndex(font, codepoint);
        DrawTextCodepoint(font, codepoint, *position, font.baseSize, color);
        position->x += (float)font.glyphs[glyph_index].advanceX;
        if (position->x > max_right) {
            return false;
        }
    }
    return true;
}

static bool draw_token_text(Font font, Token *token, Color color, Vector2 *position, float max_right) {
    return draw_text(font, token->lexeme, color, position, max_right);
}

static void draw_panel_scrollbar(Rectangle bounds, float content_height, Scrollbar *scrollbar) {
    if (content_height <= bounds.height) {
        scrollbar->dragging = false;
        scrollbar->opacity = 0;
        return;
    }
    float scrollbar_width = 8;
    float track_x = bounds.x + bounds.width - scrollbar_width;
    float thumb_height = bounds.height * bounds.height / content_height;
    if (thumb_height < 20) {
        thumb_height = 20;
    }
    float max_scroll = content_height - bounds.height;
    float thumb_travel = bounds.height - thumb_height;
    float thumb_y = bounds.y + thumb_travel * (scrollbar->scroll_y / max_scroll);

    Vector2 mouse = GetMousePosition();
    Rectangle thumb_rect = {track_x, thumb_y, scrollbar_width, thumb_height};
    if (scrollbar->dragging) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            float new_thumb_y = mouse.y - scrollbar->drag_offset;
            scrollbar->scroll_y = (new_thumb_y - bounds.y) / thumb_travel * max_scroll;
            if (scrollbar->scroll_y < 0) {
                scrollbar->scroll_y = 0;
            }
            if (scrollbar->scroll_y > max_scroll) {
                scrollbar->scroll_y = max_scroll;
            }
            thumb_y = bounds.y + thumb_travel * (scrollbar->scroll_y / max_scroll);
        } else {
            scrollbar->dragging = false;
        }
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, thumb_rect)) {
        scrollbar->dragging = true;
        scrollbar->drag_offset = mouse.y - thumb_y;
    }

    bool active = scrollbar->dragging || CheckCollisionPointRec(mouse, bounds);
    float fade_step = GetFrameTime() / 0.2f;
    scrollbar->opacity += active ? fade_step : -fade_step;
    if (scrollbar->opacity < 0) {
        scrollbar->opacity = 0;
    }
    if (scrollbar->opacity > 1) {
        scrollbar->opacity = 1;
    }
    if (scrollbar->opacity <= 0) {
        return;
    }
    Color thumb_color = scrollbar->dragging ? LIGHTGRAY : GRAY;
    thumb_color.a = (unsigned char)(thumb_color.a * scrollbar->opacity);
    DrawRectangle((int)track_x, (int)bounds.y, (int)scrollbar_width, (int)bounds.height, (Color){255, 255, 255, (unsigned char)(40 * scrollbar->opacity)});
    DrawRectangle((int)track_x, (int)thumb_y, (int)scrollbar_width, (int)thumb_height, thumb_color);
}

static float text_panel_gutter_width(Debugger *debugger, size_t lines_size) {
    Font font = debugger->font;
    int gutter_digits = 1;
    for (size_t n = lines_size; n >= 10; n /= 10) {
        gutter_digits++;
    }
    int digit_advance = font.glyphs[GetGlyphIndex(font, '0')].advanceX;
    return (float)(gutter_digits * digit_advance) + digit_advance;
}

static void text_panel_scroll_to_line(Scrollbar *scrollbar, float panel_height, size_t line, int line_height) {
    if (line == 0) {
        return;
    }
    float line_y = (float)(line - 1) * line_height;
    if (line_y < scrollbar->scroll_y) {
        scrollbar->scroll_y = line_y;
    } else if (line_y + line_height > scrollbar->scroll_y + panel_height) {
        scrollbar->scroll_y = line_y + line_height - panel_height;
    }
}

static size_t text_panel_scroll_input(Debugger *debugger, Panel *panel, Scrollbar *scrollbar, size_t lines_size) {
    int line_height = debugger->font.baseSize;
    float panel_height = panel->bounds.height;
    float content_height = (float)lines_size * line_height;
    float max_scroll = content_height > panel_height ? content_height - panel_height : 0;

    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        scrollbar->scroll_y -= wheel * line_height * 3;
    }
    if (IsKeyDown(KEY_UP)) {
        scrollbar->scroll_y -= line_height * 0.5f;
    }
    if (IsKeyDown(KEY_DOWN)) {
        scrollbar->scroll_y += line_height * 0.5f;
    }
    if (IsKeyPressed(KEY_PAGE_UP) || IsKeyPressedRepeat(KEY_PAGE_UP)) {
        scrollbar->scroll_y -= panel_height;
    }
    if (IsKeyPressed(KEY_PAGE_DOWN) || IsKeyPressedRepeat(KEY_PAGE_DOWN)) {
        scrollbar->scroll_y += panel_height;
    }
    if (IsKeyPressed(KEY_HOME)) {
        scrollbar->scroll_y = 0;
    }
    if (IsKeyPressed(KEY_END)) {
        scrollbar->scroll_y = max_scroll;
    }
    if (scrollbar->scroll_y > max_scroll) {
        scrollbar->scroll_y = max_scroll;
    }
    if (scrollbar->scroll_y < 0) {
        scrollbar->scroll_y = 0;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse = GetMousePosition();
        Rectangle bounds = panel->bounds;
        float gutter_width = text_panel_gutter_width(debugger, lines_size);
        if (mouse.x >= bounds.x && mouse.x < bounds.x + gutter_width && mouse.y >= bounds.y && mouse.y < bounds.y + bounds.height) {
            return (size_t)((mouse.y - bounds.y + scrollbar->scroll_y) / line_height) + 1;
        }
    }
    return 0;
}

static float text_panel_draw_gutter(Debugger *debugger, Rectangle bounds, float row_y, size_t line, size_t current_line, int gutter_digits, float gutter_width, bool has_breakpoint) {
    Font font = debugger->font;
    int line_height = font.baseSize;
    if (line == current_line) {
        DrawRectangle((int)bounds.x, (int)row_y, (int)bounds.width, line_height, DARKBLUE);
    }
    if (has_breakpoint) {
        DrawRectangle((int)bounds.x, (int)row_y, (int)gutter_width, line_height, MAROON);
    }

    char number_text[32];
    snprintf(number_text, sizeof(number_text), "%0*zu", gutter_digits, line);
    size_t leading = 0;
    while (leading + 1 < (size_t)gutter_digits && number_text[leading] == '0') {
        leading++;
    }
    int digit_advance = font.glyphs[GetGlyphIndex(font, '0')].advanceX;
    Color number_color = line == current_line ? GRAY : DARKGRAY;
    Color dim_color = {number_color.r, number_color.g, number_color.b, number_color.a / 2};
    Vector2 number_position = {bounds.x, row_y};
    for (int j = 0; number_text[j] != '\0'; j++) {
        int codepoint = number_text[j];
        Color color = (size_t)j < leading ? dim_color : number_color;
        DrawTextCodepoint(font, codepoint, number_position, font.baseSize, color);
        number_position.x += digit_advance;
    }
    return bounds.x + gutter_width;
}

static Panel *ir_panel_pick(IR_Panel *ir_panel, Vector2 position) {
    (void)position;
    return &ir_panel->panel;
}

static void ir_panel_handle_step(IR_Panel *ir_panel, Debugger *debugger) {
    size_t line = debugger->current_frame->instruction->location.line;
    text_panel_scroll_to_line(&ir_panel->scrollbar, ir_panel->panel.bounds.height, line, debugger->font.baseSize);
}

static void ir_panel_handle_input(IR_Panel *ir_panel, Debugger *debugger) {
    size_t lines_size = debugger->module->lexed_file.lines_size;
    size_t line = text_panel_scroll_input(debugger, &ir_panel->panel, &ir_panel->scrollbar, lines_size);
    if (line != 0) {
        IR_Instruction *instruction = find_instruction_at_line(debugger->module, line);
        if (instruction != NULL) {
            toggle_breakpoint(debugger, instruction);
        }
    }
}

static void ir_panel_draw(IR_Panel *ir_panel, Debugger *debugger, Rectangle bounds) {
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
    Font font = debugger->font;
    int line_height = font.baseSize;
    float right = bounds.x + bounds.width;
    float bottom = bounds.y + bounds.height;
    Scrollbar *scrollbar = &ir_panel->scrollbar;
    size_t first_line = (size_t)(scrollbar->scroll_y / line_height);
    float y_origin = bounds.y - (scrollbar->scroll_y - (float)first_line * line_height);

    int gutter_digits = 1;
    for (size_t n = lines_size; n >= 10; n /= 10) {
        gutter_digits++;
    }
    float gutter_width = text_panel_gutter_width(debugger, lines_size);

    BeginScissorMode((int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height);
    for (size_t i = first_line; i < lines_size; i++) {
        float row_y = y_origin + (float)(i - first_line) * line_height;
        if (row_y >= bottom) {
            break;
        }
        float source_x = text_panel_draw_gutter(debugger, bounds, row_y, i + 1, current_line, gutter_digits, gutter_width, ir_line_has_breakpoint(debugger, i + 1));

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
            .draw = (void (*)(Panel *, Debugger *, Rectangle))ir_panel_draw,
            .handle_input = (void (*)(Panel *, Debugger *))ir_panel_handle_input,
            .handle_step = (void (*)(Panel *, Debugger *))ir_panel_handle_step,
            .pick = (Panel * (*)(Panel *, Vector2)) ir_panel_pick,
            .weight = weight,
        },
    };
}

static File *source_panel_text(Debugger *debugger) {
    if (debugger->current_frame == NULL) {
        return NULL;
    }
    Source_Location origin = debugger_current_origin(debugger);
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

static void source_panel_handle_step(Source_Panel *source_panel, Debugger *debugger) {
    size_t line = debugger_current_origin(debugger).line;
    text_panel_scroll_to_line(&source_panel->scrollbar, source_panel->panel.bounds.height, line, debugger->font.baseSize);
}

static void source_panel_handle_input(Source_Panel *source_panel, Debugger *debugger) {
    File *text = source_panel_text(debugger);
    if (text == NULL) {
        return;
    }
    size_t line = text_panel_scroll_input(debugger, &source_panel->panel, &source_panel->scrollbar, text->lines_size);
    if (line != 0) {
        IR_Instruction *instruction = find_instruction_at_origin_line(debugger->module, debugger_current_origin(debugger).source, line);
        if (instruction != NULL) {
            toggle_breakpoint(debugger, instruction);
        }
    }
}

static void source_panel_draw(Source_Panel *source_panel, Debugger *debugger, Rectangle bounds) {
    File *text = source_panel_text(debugger);
    if (text == NULL) {
        return;
    }
    size_t lines_size = text->lines_size;
    size_t current_line = debugger_current_origin(debugger).line;
    Font font = debugger->font;
    int line_height = font.baseSize;
    float right = bounds.x + bounds.width;
    float bottom = bounds.y + bounds.height;
    Scrollbar *scrollbar = &source_panel->scrollbar;
    size_t first_line = (size_t)(scrollbar->scroll_y / line_height);
    float y_origin = bounds.y - (scrollbar->scroll_y - (float)first_line * line_height);

    int gutter_digits = 1;
    for (size_t n = lines_size; n >= 10; n /= 10) {
        gutter_digits++;
    }
    float gutter_width = text_panel_gutter_width(debugger, lines_size);

    BeginScissorMode((int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height);
    for (size_t i = first_line; i < lines_size; i++) {
        float row_y = y_origin + (float)(i - first_line) * line_height;
        if (row_y >= bottom) {
            break;
        }
        float source_x = text_panel_draw_gutter(debugger, bounds, row_y, i + 1, current_line, gutter_digits, gutter_width, source_line_has_breakpoint(debugger, i + 1));
        Vector2 position = {source_x, row_y};
        draw_text(font, text->lines[i], LIGHTGRAY, &position, right);
    }
    EndScissorMode();

    draw_panel_scrollbar(bounds, (float)lines_size * line_height, scrollbar);
}

static Source_Panel make_source_panel(float weight) {
    return (Source_Panel){
        .panel = {
            .draw = (void (*)(Panel *, Debugger *, Rectangle))source_panel_draw,
            .handle_input = (void (*)(Panel *, Debugger *))source_panel_handle_input,
            .handle_step = (void (*)(Panel *, Debugger *))source_panel_handle_step,
            .pick = (Panel * (*)(Panel *, Vector2)) source_panel_pick,
            .weight = weight,
        },
    };
}

static Rectangle split_panel_child_bounds(Split_Panel *split, size_t index, Rectangle bounds) {
    float gutters_total = (float)((split->children_size - 1) * GUTTER_SIZE);
    if (split->direction == SPLIT_DIRECTION__HORIZONTAL) {
        float available = bounds.width - gutters_total;
        float remaining = available;
        float x = bounds.x;
        for (size_t i = 0; i < index; i++) {
            float width = remaining * split->children[i]->weight;
            x += width + GUTTER_SIZE;
            remaining -= width;
        }
        return (Rectangle){x, bounds.y, remaining * split->children[index]->weight, bounds.height};
    } else {
        float available = bounds.height - gutters_total;
        float remaining = available;
        float y = bounds.y;
        for (size_t i = 0; i < index; i++) {
            float height = remaining * split->children[i]->weight;
            y += height + GUTTER_SIZE;
            remaining -= height;
        }
        return (Rectangle){bounds.x, y, bounds.width, remaining * split->children[index]->weight};
    }
}

static Rectangle split_panel_gutter_bounds(Split_Panel *split, size_t index, Rectangle bounds) {
    Rectangle child = split_panel_child_bounds(split, index, bounds);
    if (split->direction == SPLIT_DIRECTION__HORIZONTAL) {
        return (Rectangle){child.x + child.width, bounds.y, GUTTER_SIZE, bounds.height};
    } else {
        return (Rectangle){bounds.x, child.y + child.height, bounds.width, GUTTER_SIZE};
    }
}

static void split_panel_draw(Split_Panel *split, Debugger *debugger, Rectangle bounds) {
    for (size_t i = 0; i < split->children_size; i++) {
        Panel *child = split->children[i];
        Rectangle child_bounds = split_panel_child_bounds(split, i, bounds);
        child->bounds = child_bounds;
        child->draw(child, debugger, child_bounds);
    }
    bool dragging = debugger->active_panel == &split->panel && IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    for (size_t i = 0; i + 1 < split->children_size; i++) {
        Rectangle gutter = split_panel_gutter_bounds(split, i, bounds);
        Color color = dragging && i == split->dragged_gutter ? GRAY : DARKGRAY;
        DrawRectangleRec(gutter, color);
    }
}

static void split_panel_handle_step(Split_Panel *split, Debugger *debugger) {
    for (size_t i = 0; i < split->children_size; i++) {
        Panel *child = split->children[i];
        child->bounds = split_panel_child_bounds(split, i, split->panel.bounds);
        child->handle_step(child, debugger);
    }
}

static void split_panel_handle_input(Split_Panel *split, Debugger *debugger) {
    (void)debugger;
    Vector2 mouse = GetMousePosition();
    Rectangle bounds = split->panel.bounds;
    MouseCursor resize_cursor = split->direction == SPLIT_DIRECTION__HORIZONTAL ? MOUSE_CURSOR_RESIZE_EW : MOUSE_CURSOR_RESIZE_NS;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (size_t i = 0; i + 1 < split->children_size; i++) {
            Rectangle gutter = split_panel_gutter_bounds(split, i, bounds);
            if (CheckCollisionPointRec(mouse, gutter)) {
                split->dragged_gutter = i;
                break;
            }
        }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        SetMouseCursor(resize_cursor);
        size_t i = split->dragged_gutter;
        float gutters_total = (float)((split->children_size - 1) * GUTTER_SIZE);
        float new_weight;
        if (split->direction == SPLIT_DIRECTION__HORIZONTAL) {
            float available = bounds.width - gutters_total;
            float remaining = available;
            float x = bounds.x;
            for (size_t k = 0; k < i; k++) {
                float width = remaining * split->children[k]->weight;
                x += width + GUTTER_SIZE;
                remaining -= width;
            }
            new_weight = (mouse.x - x) / remaining;
        } else {
            float available = bounds.height - gutters_total;
            float remaining = available;
            float y = bounds.y;
            for (size_t k = 0; k < i; k++) {
                float height = remaining * split->children[k]->weight;
                y += height + GUTTER_SIZE;
                remaining -= height;
            }
            new_weight = (mouse.y - y) / remaining;
        }
        if (new_weight < 0.05f) {
            new_weight = 0.05f;
        }
        if (new_weight > 0.95f) {
            new_weight = 0.95f;
        }
        split->children[i]->weight = new_weight;
        return;
    }

    for (size_t i = 0; i + 1 < split->children_size; i++) {
        Rectangle gutter = split_panel_gutter_bounds(split, i, bounds);
        if (CheckCollisionPointRec(mouse, gutter)) {
            SetMouseCursor(resize_cursor);
            break;
        }
    }
}

static Panel *split_panel_pick(Split_Panel *split, Vector2 position) {
    for (size_t i = 0; i < split->children_size; i++) {
        Panel *child = split->children[i];
        if (CheckCollisionPointRec(position, child->bounds)) {
            return child->pick(child, position);
        }
    }
    return &split->panel;
}

static Split_Panel make_split_panel(float weight, Split_Direction direction, Panel **children, size_t children_size) {
    return (Split_Panel){
        .panel = {
            .draw = (void (*)(Panel *, Debugger *, Rectangle))split_panel_draw,
            .handle_input = (void (*)(Panel *, Debugger *))split_panel_handle_input,
            .handle_step = (void (*)(Panel *, Debugger *))split_panel_handle_step,
            .pick = (Panel * (*)(Panel *, Vector2)) split_panel_pick,
            .weight = weight,
        },
        .direction = direction,
        .children = children,
        .children_size = children_size,
    };
}

static void stack_panel_draw(Stack_Panel *stack_panel, Debugger *debugger, Rectangle bounds) {
    (void)stack_panel;
    if (debugger->current_frame == NULL) {
        return;
    }
    Font font = debugger->font;
    int line_height = font.baseSize;
    BeginScissorMode((int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height);
    float y = bounds.y;
    bool first = true;
    for (Call_Frame *f = debugger->current_frame; f != NULL; f = f->caller) {
        if (first) {
            DrawRectangle((int)bounds.x, (int)y, (int)bounds.width, line_height, DARKBLUE);
            first = false;
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
        y += line_height;
        if (y >= bounds.y + bounds.height) {
            break;
        }
    }
    EndScissorMode();
}

static void stack_panel_handle_input(Stack_Panel *stack_panel, Debugger *debugger) {
    (void)stack_panel;
    (void)debugger;
}

static void stack_panel_handle_step(Stack_Panel *stack_panel, Debugger *debugger) {
    (void)stack_panel;
    (void)debugger;
}

static Panel *stack_panel_pick(Stack_Panel *stack_panel, Vector2 position) {
    (void)position;
    return &stack_panel->panel;
}

static Stack_Panel make_stack_panel(float weight) {
    return (Stack_Panel){
        .panel = {
            .draw = (void (*)(Panel *, Debugger *, Rectangle))stack_panel_draw,
            .handle_input = (void (*)(Panel *, Debugger *))stack_panel_handle_input,
            .handle_step = (void (*)(Panel *, Debugger *))stack_panel_handle_step,
            .pick = (Panel * (*)(Panel *, Vector2)) stack_panel_pick,
            .weight = weight,
        },
    };
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
        size_t offset = 0;
        for (size_t i = 0; i < type->struct_field_count; i++) {
            IR_Struct_Field *field = type->struct_fields[i];
            n += (size_t)snprintf(buf + n, n < size ? size - n : 0, "%s .%.*s = ", i == 0 ? "" : ",", STRING(field->name));
            n += format_typed(buf + n, n < size ? size - n : 0, field->type, address + offset);
            offset += ir_type_size(field->type);
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

static void draw_binding_line(Font font, Rectangle bounds, float y, Call_Frame *frame, Dbg_Binding *binding) {
    int line_height = font.baseSize;
    IR_Value *value = binding->value;
    uint8_t *base = value->kind <= IR_VALUE__GLOBAL_VARIABLE ? frame->globals_data : frame->frame_data;
    uint8_t *slot = base + value->slot.offset;

    IR_Type *display_type;
    uint8_t *address;
    if (binding->indirect) {
        address = *(uint8_t **)slot;
        display_type = value->type->pointee;
    } else {
        address = slot;
        display_type = value->type;
    }

    char value_text[256];
    if (binding->indirect && address == NULL) {
        snprintf(value_text, sizeof(value_text), "<uninitialized>");
    } else {
        format_typed(value_text, sizeof(value_text), display_type, address);
    }
    Vector2 value_size = MeasureTextEx(font, value_text, line_height, 0);

    char name_text[64];
    snprintf(name_text, sizeof(name_text), "%.*s", STRING(binding->name));
    DrawTextEx(font, name_text, (Vector2){bounds.x, y}, line_height, 0, RAYWHITE);
    Vector2 name_size = MeasureTextEx(font, name_text, line_height, 0);

    char type_text[128];
    FILE *f = fmemopen(type_text, sizeof(type_text), "w");
    fputs(": ", f);
    fprint_ir_type(f, display_type);
    fclose(f);
    DrawTextEx(font, type_text, (Vector2){bounds.x + name_size.x, y}, line_height, 0, GRAY);

    DrawTextEx(font, value_text, (Vector2){bounds.x + bounds.width - value_size.x, y}, line_height, 0, RAYWHITE);
}

static size_t variables_panel_count(Debugger *debugger) {
    Frame_Debug_State *state = debugger_frame_state(debugger, debugger->current_frame);
    return state == NULL ? 0 : state->bindings_size;
}

static void variables_panel_draw(Variables_Panel *variables_panel, Debugger *debugger, Rectangle bounds) {
    if (debugger->current_frame == NULL) {
        return;
    }
    Frame_Debug_State *state = debugger_frame_state(debugger, debugger->current_frame);
    if (state == NULL) {
        return;
    }
    Font font = debugger->font;
    int line_height = font.baseSize;
    BeginScissorMode((int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height);
    Call_Frame *frame = debugger->current_frame;
    float y = bounds.y - variables_panel->scrollbar.scroll_y;
    float bottom = bounds.y + bounds.height;
    for (size_t i = 0; i < state->bindings_size; i++) {
        if (y + line_height > bounds.y && y < bottom) {
            draw_binding_line(font, bounds, y, frame, &state->bindings[i]);
        }
        y += line_height;
    }
    EndScissorMode();
    float content_height = (float)state->bindings_size * line_height;
    draw_panel_scrollbar(bounds, content_height, &variables_panel->scrollbar);
}

static void variables_panel_handle_input(Variables_Panel *variables_panel, Debugger *debugger) {
    int line_height = debugger->font.baseSize;
    float panel_height = variables_panel->panel.bounds.height;
    float content_height = (float)variables_panel_count(debugger) * line_height;
    float max_scroll = content_height > panel_height ? content_height - panel_height : 0;

    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        variables_panel->scrollbar.scroll_y -= wheel * line_height * 3;
    }
    if (variables_panel->scrollbar.scroll_y > max_scroll) {
        variables_panel->scrollbar.scroll_y = max_scroll;
    }
    if (variables_panel->scrollbar.scroll_y < 0) {
        variables_panel->scrollbar.scroll_y = 0;
    }
}

static void variables_panel_handle_step(Variables_Panel *variables_panel, Debugger *debugger) {
    (void)debugger;
    variables_panel->scrollbar.scroll_y = 0;
}

static Panel *variables_panel_pick(Variables_Panel *variables_panel, Vector2 position) {
    (void)position;
    return &variables_panel->panel;
}

static Variables_Panel make_variables_panel(float weight) {
    return (Variables_Panel){
        .panel = {
            .draw = (void (*)(Panel *, Debugger *, Rectangle))variables_panel_draw,
            .handle_input = (void (*)(Panel *, Debugger *))variables_panel_handle_input,
            .handle_step = (void (*)(Panel *, Debugger *))variables_panel_handle_step,
            .pick = (Panel * (*)(Panel *, Vector2)) variables_panel_pick,
            .weight = weight,
        },
    };
}

static void debugger_render_frame(Debugger *debugger) {
    debugger->root_panel->bounds = (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()};

    if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        debugger->active_panel = debugger->root_panel->pick(debugger->root_panel, GetMousePosition());
    }
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    debugger->active_panel->handle_input(debugger->active_panel, debugger);

    BeginDrawing();
    ClearBackground(BLACK);
    debugger->root_panel->draw(debugger->root_panel, debugger, debugger->root_panel->bounds);
    EndDrawing();
}

static void debugger_on_step(Observer *observer, Call_Frame *current_frame) {
    Debugger *debugger = (Debugger *)observer;

    size_t depth = frame_depth(current_frame);
    Frame_Debug_State *state = sync_frame_states(debugger, current_frame, depth);

    IR_Instruction *instruction = current_frame->instruction;
    if (instruction->kind == IR_INSTRUCTION__DBG_LINE) {
        state->origin = instruction->dbg_line_instruction.location;
    } else if (instruction->kind == IR_INSTRUCTION__DBG_BIND) {
        record_binding(state, instruction);
    }

    bool at_breakpoint = is_breakpoint(debugger, instruction);
    if ((instruction->kind == IR_INSTRUCTION__DBG_LINE || instruction->kind == IR_INSTRUCTION__DBG_BIND) && !at_breakpoint) {
        return;
    }
    bool running = debugger->mode == DEBUGGER_MODE__CONTINUE || (debugger->mode == DEBUGGER_MODE__NEXT && depth > debugger->next_depth);
    if (running && !at_breakpoint) {
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
        } else if (IsKeyPressed(KEY_Q)) {
            exit(0);
        }
        return;
    }

    debugger->current_frame = current_frame;

    debugger->root_panel->bounds = (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()};
    debugger->root_panel->handle_step(debugger->root_panel, debugger);

    while (!WindowShouldClose()) {
        debugger_render_frame(debugger);

        if (IsKeyPressed(KEY_S)) {
            debugger->mode = DEBUGGER_MODE__STEP;
            return;
        }
        if (IsKeyPressed(KEY_N)) {
            debugger->mode = DEBUGGER_MODE__NEXT;
            debugger->next_depth = depth;
            debugger->current_frame = NULL;
            return;
        }
        if (IsKeyPressed(KEY_C)) {
            debugger->mode = DEBUGGER_MODE__CONTINUE;
            debugger->current_frame = NULL;
            return;
        }
        if (IsKeyPressed(KEY_Q)) {
            exit(0);
        }
    }
    debugger->mode = DEBUGGER_MODE__CONTINUE;
}

Font load_bitmap_font(const char *path) {
    char resolved_path[PATH_MAX];
    const char *runner_home = getenv("RUNNER_HOME");
    if (runner_home != NULL && runner_home[0] != '\0') {
        snprintf(resolved_path, sizeof(resolved_path), "%s/%s", runner_home, path);
        path = resolved_path;
    }

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "Cannot open font file: %s\n", path);
        return (Font){0};
    }

    int font_height = 0;
    int font_base_line = 0;

    int glyphs_capacity = 95; // printable ASCII characters
    int glyphs_size = 0;
    GlyphInfo *glyphs = malloc(sizeof(GlyphInfo) * glyphs_capacity);

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "font.height: ", 13) == 0) {
            font_height = atoi(line + 13);
        } else if (strncmp(line, "font.base_line: ", 16) == 0) {
            font_base_line = atoi(line + 16);
        } else if (strncmp(line, "glyph:", 6) == 0) {
            if (fgets(line, sizeof(line), file) == NULL) {
                break;
            }
            int glyph_code = atoi(line + strlen("glyph.width:"));
            if (fgets(line, sizeof(line), file) == NULL) {
                break;
            }
            int glyph_width = atoi(line + strlen("glyph.width:"));
            Image glyph_image = GenImageColor(glyph_width, font_height, BLANK);
            for (int row = 0; row < font_height; row++) {
                if (fgets(line, sizeof(line), file) == NULL) {
                    break;
                }
                for (int column = 0; column < glyph_width; column++) {
                    if (line[column * 2] == 'F') {
                        ImageDrawPixel(&glyph_image, column, row, WHITE);
                    }
                }
            }
            if (glyphs_size == glyphs_capacity) {
                glyphs_capacity += glyphs_capacity / 2;
                glyphs = realloc(glyphs, sizeof(GlyphInfo) * glyphs_capacity);
            }
            glyphs[glyphs_size] = (GlyphInfo){
                .value = glyph_code,
                .offsetX = 0,
                .offsetY = 0,
                .advanceX = glyph_width,
                .image = glyph_image,
            };
            glyphs_size++;
        }
    }
    fclose(file);

    int atlas_width = 0;
    for (int i = 0; i < glyphs_size; i++) {
        atlas_width += (int)glyphs[i].image.width;
    }

    Image atlas = GenImageColor(atlas_width, font_height, BLANK);
    Rectangle *recs = malloc(sizeof(Rectangle) * glyphs_size);
    int x = 0;
    for (int i = 0; i < glyphs_size; i++) {
        int width = glyphs[i].image.width;
        ImageDraw(&atlas, glyphs[i].image, (Rectangle){0, 0, width, font_height}, (Rectangle){x, 0, width, font_height}, WHITE);
        recs[i] = (Rectangle){x, 0, width, font_height};
        x += width;
    }

    Font font = {
        .baseSize = font_height,
        .glyphCount = glyphs_size,
        .glyphPadding = 0,
        .texture = LoadTextureFromImage(atlas),
        .recs = recs,
        .glyphs = glyphs,
    };
    UnloadImage(atlas);
    (void)font_base_line;
    return font;
}

static File *load_sources(IR_Module *module) {
    if (module->source_files.size == 0) {
        return NULL;
    }
    File *sources = calloc(module->source_files.size, sizeof(File));
    String ir_path = module->lexed_file.file.path;
    size_t dir_length = 0;
    for (size_t i = ir_path.length; i > 0; i--) {
        if (ir_path.content[i - 1] == '/') {
            dir_length = i;
            break;
        }
    }
    for (size_t i = 0; i < module->source_files.size; i++) {
        String path = module->source_files.items[i];
        char *resolved = malloc(dir_length + path.length + 1);
        size_t resolved_length = 0;
        if (path.length > 0 && path.content[0] != '/') {
            memcpy(resolved, ir_path.content, dir_length);
            resolved_length = dir_length;
        }
        memcpy(resolved + resolved_length, path.content, path.length);
        resolved_length += path.length;
        resolved[resolved_length] = '\0';
        FILE *stream = fopen(resolved, "r");
        if (stream == NULL) {
            fprintf(stderr, "Cannot open source file: %s\n", resolved);
            free(resolved);
            continue;
        }
        fclose(stream);
        sources[i] = load_file((String){resolved, resolved_length});
    }
    return sources;
}

int64_t debug(IR_Module *module, int argc, char *argv[]) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Code IR Debugger");
    SetTargetFPS(60);

    bool has_origins = module->source_files.size > 0;
    Source_Panel source_panel = make_source_panel(0.5f);
    IR_Panel ir_panel = make_ir_panel(has_origins ? 1.0f : 0.5f);
    Panel *left_panel_children[] = {&source_panel.panel, &ir_panel.panel};
    Split_Panel left_panel = make_split_panel(0.5f, SPLIT_DIRECTION__VERTICAL, left_panel_children, 2);
    Stack_Panel stack_panel = make_stack_panel(0.3f);
    Variables_Panel variables_panel = make_variables_panel(1.0f);
    Panel *right_panel_children[] = {&stack_panel.panel, &variables_panel.panel};
    Split_Panel right_panel = make_split_panel(1.0f, SPLIT_DIRECTION__VERTICAL, right_panel_children, 2);
    Panel *split_children[] = {has_origins ? &left_panel.panel : &ir_panel.panel, &right_panel.panel};
    Split_Panel split_panel = make_split_panel(1.0f, SPLIT_DIRECTION__HORIZONTAL, split_children, sizeof(split_children) / sizeof(*split_children));
    Debugger debugger = {
        .observer = {.on_step = debugger_on_step},
        .module = module,
        .sources = load_sources(module),
        .mode = DEBUGGER_MODE__STEP,
        .next_depth = 0,
        .font = load_bitmap_font("fonts/Code.font"),
        .root_panel = &split_panel.panel,
    };
    int64_t result = interpret(module, argc, argv, &debugger.observer);

    UnloadFont(debugger.font);
    CloseWindow();
    return result;
}
