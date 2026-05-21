#include "Debugger.h"
#include "IR.h"
#include "Interpreter.h"
#include "String.h"
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
    Observer observer;
    IR_Module *module;
    Debugger_Mode mode;
    size_t next_depth;
    IR_Instruction_List breakpoints;
    Font font;
    Call_Frame *current_frame;
    Panel *root_panel;
    Panel *active_panel;
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
    Panel panel;
    float scroll_y;
    bool scrollbar_dragging;
    float scrollbar_drag_offset;
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

#define GUTTER_SIZE 4

static bool is_breakpoint(Debugger *debugger, IR_Instruction *instruction) {
    for (size_t i = 0; i < debugger->breakpoints.size; i++) {
        if (debugger->breakpoints.items[i] == instruction) {
            return true;
        }
    }
    return false;
}

#if 0
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

static IR_Instruction *add_breakpoint_at_line(Debugger *debugger, size_t line) {
    IR_Instruction *instruction = find_instruction_at_line(debugger->module, line);
    if (instruction == NULL || is_breakpoint(debugger, instruction)) {
        return instruction;
    }
    ir_instruction_list_add(&debugger->breakpoints, instruction);
    return instruction;
}

static bool remove_breakpoint_at_line(Debugger *debugger, size_t line) {
    for (size_t i = 0; i < debugger->breakpoints.size; i++) {
        if (debugger->breakpoints.items[i]->location.line == line) {
            debugger->breakpoints.items[i] = debugger->breakpoints.items[--debugger->breakpoints.size];
            return true;
        }
    }
    return false;
}

static void list_breakpoints(Debugger *debugger) {
    if (debugger->breakpoints.size == 0) {
        fprintf(stderr, "No breakpoints\n");
        return;
    }
    for (size_t i = 0; i < debugger->breakpoints.size; i++) {
        IR_Instruction *instruction = debugger->breakpoints.items[i];
        fprintf(stderr, "  %.*s:%zu\n", STRING(instruction->location.source), instruction->location.line);
    }
}

static void break_command(Debugger *debugger, Call_Frame *frame, const char *arg) {
    while (*arg == ' ') {
        arg++;
    }
    IR_Instruction *instruction;
    if (*arg == '\0') {
        instruction = frame->instruction;
        if (!is_breakpoint(debugger, instruction)) {
            ir_instruction_list_add(&debugger->breakpoints, instruction);
        }
    } else {
        size_t line = (size_t)atoi(arg);
        if (line == 0) {
            fprintf(stderr, "Usage: b [<line>]\n");
            return;
        }
        instruction = add_breakpoint_at_line(debugger, line);
        if (instruction == NULL) {
            fprintf(stderr, "No instruction at line %zu\n", line);
            return;
        }
    }
    fprintf(stderr, "Breakpoint at %.*s:%zu\n", STRING(instruction->location.source), instruction->location.line);
}

static void delete_command(Debugger *debugger, const char *arg) {
    while (*arg == ' ') {
        arg++;
    }
    size_t line = (size_t)atoi(arg);
    if (line == 0) {
        fprintf(stderr, "Usage: d <line>\n");
        return;
    }
    if (!remove_breakpoint_at_line(debugger, line)) {
        fprintf(stderr, "No breakpoint at line %zu\n", line);
    }
}
#endif

static size_t frame_depth(Call_Frame *frame) {
    size_t depth = 0;
    for (Call_Frame *f = frame; f != NULL; f = f->caller) {
        depth++;
    }
    return depth;
}

#if 0
static IR_Value *lookup_local(IR_Function *function, String name) {
    for (size_t i = 0; i < function->parameters.size; i++) {
        if (string_equals(function->parameters.items[i]->name, name)) {
            return function->parameters.items[i];
        }
    }
    for (size_t b = 0; b < function->blocks.size; b++) {
        IR_Block *block = function->blocks.items[b];
        for (size_t i = 0; i < block->instructions.size; i++) {
            IR_Instruction *instruction = block->instructions.items[i];
            if (instruction->result.name.length > 0 && string_equals(instruction->result.name, name)) {
                return &instruction->result;
            }
        }
    }
    return NULL;
}

static IR_Value *lookup_global(IR_Module *module, String name) {
    for (size_t i = 0; i < module->global_variables.size; i++) {
        if (string_equals(module->global_variables.items[i]->name, name)) {
            return &module->global_variables.items[i]->value;
        }
    }
    for (size_t i = 0; i < module->functions.size; i++) {
        if (string_equals(module->functions.items[i]->name, name)) {
            return &module->functions.items[i]->value;
        }
    }
    return NULL;
}

static void print_typed(IR_Type *type, uint8_t *address) {
    switch (type->kind) {
    case IR_TYPE__BOOL:
        fprintf(stderr, "%s", *(uint8_t *)address ? "true" : "false");
        break;
    case IR_TYPE__I8:
        fprintf(stderr, "%d", *(int8_t *)address);
        break;
    case IR_TYPE__I16:
        fprintf(stderr, "%d", *(int16_t *)address);
        break;
    case IR_TYPE__I32:
        fprintf(stderr, "%d", *(int32_t *)address);
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        fprintf(stderr, "%lld", *(int64_t *)address);
        break;
    case IR_TYPE__U8:
        fprintf(stderr, "%u", *(uint8_t *)address);
        break;
    case IR_TYPE__U16:
        fprintf(stderr, "%u", *(uint16_t *)address);
        break;
    case IR_TYPE__U32:
        fprintf(stderr, "%u", *(uint32_t *)address);
        break;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        fprintf(stderr, "%llu", *(uint64_t *)address);
        break;
    case IR_TYPE__PTR:
    case IR_TYPE__MULTI_PTR:
    case IR_TYPE__PROC:
        fprintf(stderr, "%p", *(void **)address);
        break;
    case IR_TYPE__STRUCT: {
        fprintf(stderr, "{");
        size_t offset = 0;
        for (size_t i = 0; i < type->struct_field_count; i++) {
            IR_Struct_Field *field = type->struct_fields[i];
            fprintf(stderr, "%s .%.*s = ", i == 0 ? "" : ",", STRING(field->name));
            print_typed(field->type, address + offset);
            offset += ir_type_size(field->type);
        }
        fprintf(stderr, " }");
        break;
    }
    case IR_TYPE__VOID:
        fprintf(stderr, "(void)");
        break;
    default:
        fprintf(stderr, "<%zu bytes @ %p>", ir_type_size(type), (void *)address);
        break;
    }
}

static void print_value(Call_Frame *frame, IR_Value *value) {
    uint8_t *base = value->name.content[0] == '$' ? frame->globals_data : frame->frame_data;
    uint8_t *address = base + value->slot.offset;
    fprintf(stderr, "%.*s: ", STRING(value->name));
    fprint_ir_type(stderr, value->type);
    fprintf(stderr, " = ");
    print_typed(value->type, address);
    fprintf(stderr, "\n");
}

static void print_command(Debugger *debugger, Call_Frame *frame, const char *arg) {
    while (*arg == ' ') {
        arg++;
    }
    if (*arg == '\0') {
        fprintf(stderr, "Usage: p <%%name|$name>\n");
        return;
    }
    String name = string_from(arg);
    IR_Value *value;
    if (name.content[0] == '$') {
        value = lookup_global(debugger->module, name);
    } else if (name.content[0] == '%') {
        value = lookup_local(frame->function, name);
    } else {
        fprintf(stderr, "Names must start with '%%' or '$'\n");
        return;
    }
    if (value == NULL) {
        fprintf(stderr, "No value named '%.*s'\n", STRING(name));
        return;
    }
    print_value(frame, value);
}
#endif

static bool draw_token_text(Font font, Token *token, Color color, Vector2 *position, float max_right) {
    for (size_t i = 0; i < token->lexeme.length; i++) {
        int codepoint = token->lexeme.content[i];
        int glyph_index = GetGlyphIndex(font, codepoint);
        DrawTextCodepoint(font, codepoint, *position, font.baseSize, color);
        position->x += (float)font.glyphs[glyph_index].advanceX;
        if (position->x > max_right) {
            return false;
        }
    }
    return true;
}

static void draw_panel_scrollbar(Rectangle bounds, float content_height, float *scroll_y, bool *dragging, float *drag_offset) {
    if (content_height <= bounds.height) {
        *dragging = false;
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
    float thumb_y = bounds.y + thumb_travel * (*scroll_y / max_scroll);

    Vector2 mouse = GetMousePosition();
    Rectangle thumb_rect = {track_x, thumb_y, scrollbar_width, thumb_height};
    if (*dragging) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            float new_thumb_y = mouse.y - *drag_offset;
            *scroll_y = (new_thumb_y - bounds.y) / thumb_travel * max_scroll;
            if (*scroll_y < 0) {
                *scroll_y = 0;
            }
            if (*scroll_y > max_scroll) {
                *scroll_y = max_scroll;
            }
            thumb_y = bounds.y + thumb_travel * (*scroll_y / max_scroll);
        } else {
            *dragging = false;
        }
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, thumb_rect)) {
        *dragging = true;
        *drag_offset = mouse.y - thumb_y;
    }

    Color thumb_color = *dragging ? LIGHTGRAY : GRAY;
    DrawRectangle((int)track_x, (int)bounds.y, (int)scrollbar_width, (int)bounds.height, (Color){255, 255, 255, 40});
    DrawRectangle((int)track_x, (int)thumb_y, (int)scrollbar_width, (int)thumb_height, thumb_color);
}

static Panel *source_panel_pick(Source_Panel *source_panel, Vector2 position) {
    (void)position;
    return &source_panel->panel;
}

static void source_panel_handle_step(Source_Panel *source_panel, Debugger *debugger) {
    int line_height = debugger->font.baseSize;
    float panel_height = source_panel->panel.bounds.height;
    float line_y = (float)(debugger->current_frame->instruction->location.line - 1) * line_height;
    if (line_y < source_panel->scroll_y) {
        source_panel->scroll_y = line_y;
    } else if (line_y + line_height > source_panel->scroll_y + panel_height) {
        source_panel->scroll_y = line_y + line_height - panel_height;
    }
}

static void source_panel_handle_input(Source_Panel *source_panel, Debugger *debugger) {
    int line_height = debugger->font.baseSize;
    float panel_height = source_panel->panel.bounds.height;
    float content_height = (float)debugger->module->lexed_source.lines_size * line_height;
    float max_scroll = content_height > panel_height ? content_height - panel_height : 0;

    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        source_panel->scroll_y -= wheel * line_height * 3;
    }
    if (IsKeyDown(KEY_UP)) {
        source_panel->scroll_y -= line_height * 0.5f;
    }
    if (IsKeyDown(KEY_DOWN)) {
        source_panel->scroll_y += line_height * 0.5f;
    }
    if (IsKeyPressed(KEY_PAGE_UP) || IsKeyPressedRepeat(KEY_PAGE_UP)) {
        source_panel->scroll_y -= panel_height;
    }
    if (IsKeyPressed(KEY_PAGE_DOWN) || IsKeyPressedRepeat(KEY_PAGE_DOWN)) {
        source_panel->scroll_y += panel_height;
    }
    if (IsKeyPressed(KEY_HOME)) {
        source_panel->scroll_y = 0;
    }
    if (IsKeyPressed(KEY_END)) {
        source_panel->scroll_y = max_scroll;
    }
    if (source_panel->scroll_y > max_scroll) {
        source_panel->scroll_y = max_scroll;
    }
    if (source_panel->scroll_y < 0) {
        source_panel->scroll_y = 0;
    }
}

static void source_panel_draw(Source_Panel *source_panel, Debugger *debugger, Rectangle bounds) {
    size_t current_line = debugger->current_frame->instruction->location.line;
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
        [TOKEN_KIND__VARIABLE] = WHITE,
    };
    Lexed_Source *lexed_source = &debugger->module->lexed_source;
    Font font = debugger->font;
    int line_height = font.baseSize;
    float right = bounds.x + bounds.width;
    float bottom = bounds.y + bounds.height;
    size_t first_line = (size_t)(source_panel->scroll_y / line_height);
    float y_origin = bounds.y - (source_panel->scroll_y - (float)first_line * line_height);

    int gutter_digits = 1;
    for (size_t n = lexed_source->lines_size; n >= 10; n /= 10) {
        gutter_digits++;
    }
    int digit_advance = font.glyphs[GetGlyphIndex(font, '0')].advanceX;
    float gutter_width = (float)(gutter_digits * digit_advance) + digit_advance;
    float source_x = bounds.x + gutter_width;

    BeginScissorMode((int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height);
    for (size_t i = first_line; i < lexed_source->lines_size; i++) {
        float row_y = y_origin + (float)(i - first_line) * line_height;
        if (row_y >= bottom) {
            break;
        }
        if (i + 1 == current_line) {
            DrawRectangle((int)bounds.x, (int)row_y, (int)bounds.width, line_height, DARKBLUE);
        }

        char number_text[32];
        snprintf(number_text, sizeof(number_text), "%0*zu", gutter_digits, i + 1);
        size_t leading = 0;
        while (leading + 1 < (size_t)gutter_digits && number_text[leading] == '0') {
            leading++;
        }
        Color number_color = i + 1 == current_line ? GRAY : DARKGRAY;
        Color dim_color = {number_color.r, number_color.g, number_color.b, number_color.a / 2};
        Vector2 number_position = {bounds.x, row_y};
        for (int j = 0; number_text[j] != '\0'; j++) {
            int codepoint = number_text[j];
            Color color = (size_t)j < leading ? dim_color : number_color;
            DrawTextCodepoint(font, codepoint, number_position, font.baseSize, color);
            number_position.x += digit_advance;
        }

        Vector2 position = {source_x, row_y};
        Token *line_token = lexed_source->lines[i];
        Token *first_token = line_token;
        if (first_token->kind == TOKEN_KIND__SPACE) {
            first_token++;
        }
        bool is_liveness_line = first_token->kind == TOKEN_KIND__OTHER && first_token->other.value == '[';
        while (line_token->kind != TOKEN_KIND__END_OF_LINE && line_token->kind != TOKEN_KIND__END_OF_FILE) {
            Color color = is_liveness_line ? DARKGRAY : colors[line_token->kind];
            if (!draw_token_text(font, line_token, color, &position, right)) {
                break;
            }
            line_token++;
        }
    }
    EndScissorMode();

    float content_height = (float)lexed_source->lines_size * line_height;
    draw_panel_scrollbar(bounds, content_height, &source_panel->scroll_y, &source_panel->scrollbar_dragging, &source_panel->scrollbar_drag_offset);
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
        String source = f->instruction->location.source;
        for (size_t i = source.length; i > 0; i--) {
            if (source.content[i - 1] == '/') {
                source.content += i;
                source.length -= i;
                break;
            }
        }
        char location[128];
        snprintf(location, sizeof(location), "%.*s:%zu", STRING(source), f->instruction->location.line);
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

static void debugger_on_step(Observer *observer, Call_Frame *current_frame) {
    Debugger *debugger = (Debugger *)observer;

    size_t depth = frame_depth(current_frame);
    bool at_breakpoint = is_breakpoint(debugger, current_frame->instruction);
    if (debugger->mode == DEBUGGER_MODE__CONTINUE && !at_breakpoint) {
        return;
    }
    if (debugger->mode == DEBUGGER_MODE__NEXT && depth > debugger->next_depth && !at_breakpoint) {
        return;
    }

    debugger->current_frame = current_frame;

    debugger->root_panel->bounds = (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()};
    debugger->root_panel->handle_step(debugger->root_panel, debugger);

    while (!WindowShouldClose()) {
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

        if (IsKeyPressed(KEY_S)) {
            debugger->mode = DEBUGGER_MODE__STEP;
            return;
        }
        if (IsKeyPressed(KEY_N)) {
            debugger->mode = DEBUGGER_MODE__NEXT;
            debugger->next_depth = depth;
            return;
        }
        if (IsKeyPressed(KEY_C)) {
            debugger->mode = DEBUGGER_MODE__CONTINUE;
            return;
        }
        if (IsKeyPressed(KEY_Q)) {
            exit(0);
        }
    }
    debugger->mode = DEBUGGER_MODE__CONTINUE;
}

Font load_bitmap_font(const char *path) {
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

int64_t debug(IR_Module *module, int argc, char *argv[]) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Code IR Debugger");
    SetTargetFPS(60);

    Source_Panel source_panel = make_source_panel(0.5f);
    Stack_Panel stack_panel = make_stack_panel(0.3f);
    Source_Panel right_bottom_panel = make_source_panel(1.0f);
    Panel *right_panel_children[] = {&stack_panel.panel, &right_bottom_panel.panel};
    Split_Panel right_panel = make_split_panel(1.0f, SPLIT_DIRECTION__VERTICAL, right_panel_children, 2);
    Panel *split_children[] = {&source_panel.panel, &right_panel.panel};
    Split_Panel split_panel = make_split_panel(1.0f, SPLIT_DIRECTION__HORIZONTAL, split_children, sizeof(split_children) / sizeof(*split_children));
    Debugger debugger = {
        .observer = {.on_step = debugger_on_step},
        .module = module,
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
