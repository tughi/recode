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
    Panel *panels;
    Panel *active_panel;
} Debugger;

struct Panel {
    void (*draw)(Panel *self, Debugger *debugger);
    void (*handle_input)(Panel *self, Debugger *debugger);
    void (*handle_step)(Panel *self, Debugger *debugger);
    Rectangle bounds;
    Panel *next;
};

typedef struct {
    Panel panel;
    float scroll_y;
    bool scrollbar_dragging;
    float scrollbar_drag_offset;
} Source_Panel;

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
static void print_backtrace(Call_Frame *frame) {
    size_t i = 0;
    for (Call_Frame *f = frame; f != NULL; f = f->caller) {
        fprintf(stderr, "  #%zu %.*s at %.*s:%zu\n", i++, STRING(f->function->name), STRING(f->instruction->location.source), f->instruction->location.line);
    }
}

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

static void source_panel_draw(Source_Panel *source_panel, Debugger *debugger) {
    Rectangle bounds = source_panel->panel.bounds;
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

    for (Panel *panel = debugger->panels; panel != NULL; panel = panel->next) {
        panel->bounds = (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()};
    }

    for (Panel *panel = debugger->panels; panel != NULL; panel = panel->next) {
        panel->handle_step(panel, debugger);
    }

    while (!WindowShouldClose()) {
        for (Panel *panel = debugger->panels; panel != NULL; panel = panel->next) {
            panel->bounds = (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()};
        }

        debugger->active_panel->handle_input(debugger->active_panel, debugger);

        BeginDrawing();
        ClearBackground(BLACK);
        for (Panel *panel = debugger->panels; panel != NULL; panel = panel->next) {
            panel->draw(panel, debugger);
        }
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

    Source_Panel source_panel = {
        .panel = {
            .draw = (void (*)(Panel *, Debugger *))source_panel_draw,
            .handle_input = (void (*)(Panel *, Debugger *))source_panel_handle_input,
            .handle_step = (void (*)(Panel *, Debugger *))source_panel_handle_step,
        },
    };
    Debugger debugger = {
        .observer = {.on_step = debugger_on_step},
        .module = module,
        .mode = DEBUGGER_MODE__STEP,
        .next_depth = 0,
        .font = load_bitmap_font("fonts/Code.font"),
        .panels = &source_panel.panel,
        .active_panel = &source_panel.panel,
    };
    int64_t result = interpret(module, argc, argv, &debugger.observer);

    UnloadFont(debugger.font);
    CloseWindow();
    return result;
}
