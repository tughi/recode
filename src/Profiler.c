#include "Profiler.h"
#include "GUI.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Profile_Call *profile_call_child(Profile_Call *parent, IR_Function *function) {
    for (size_t i = 0; i < parent->children_size; i++) {
        if (parent->children[i]->function == function) {
            return parent->children[i];
        }
    }
    if (parent->children_size == parent->children_capacity) {
        parent->children_capacity = parent->children_capacity == 0 ? 4 : parent->children_capacity * 2;
        parent->children = realloc(parent->children, parent->children_capacity * sizeof(Profile_Call *));
    }
    Profile_Call *child = calloc(1, sizeof(Profile_Call));
    child->function = function;
    child->parent = parent;
    parent->children[parent->children_size++] = child;
    return child;
}

#define ROW_HEIGHT 20
#define HEADER_HEIGHT 44

typedef struct {
    Panel panel;
    Scrollbar scrollbar;
} Flamegraph_Panel;

typedef struct {
    Panel panel;
    Scrollbar scrollbar;
} Functions_Panel;

typedef enum {
    SORT_COLUMN__FUNCTION,
    SORT_COLUMN__SELF_TIME,
    SORT_COLUMN__TOTAL_TIME,
    SORT_COLUMN__CALLS,
} Sort_Column;

typedef struct {
    GUI gui;
    IR_Module *module;
    Profile_Call *root;
    uint64_t total_time;
    Profile_Call *focus;
    Profile_Call *hovered;
    IR_Function **functions;
    size_t functions_size;
    Sort_Column sort_column;
    bool sort_reversed;
    Panel *flamegraph_panel;
    Panel *functions_panel;
} Profiler;

static Color node_color(IR_Function *function) {
    uint64_t hash = (uint64_t)(uintptr_t)function * 2654435761u;
    float hue = 18.0f + (float)(hash % 42);
    float saturation = 0.62f + (float)((hash >> 8) & 0x3f) / 63.0f * 0.18f;
    return ColorFromHSV(hue, saturation, 0.92f);
}

static void draw_clipped_text(Font font, String text, float x, float y, float right, Color color) {
    Vector2 position = {x, y};
    draw_text(font, text, color, &position, right);
}

static void draw_header(Profiler *profiler, Rectangle bounds, const char *hints) {
    DrawRectangle((int)bounds.x, (int)bounds.y, (int)bounds.width, HEADER_HEIGHT, (Color){36, 36, 42, 255});
    char header[256];
    int length = snprintf(header, sizeof(header), "%.*s   %.3f ms total   %s", STRING(profiler->module->lexed_file.file.path), (double)profiler->total_time / 1e6, hints);
    draw_clipped_text(profiler->gui.font, (String){header, (size_t)length}, bounds.x + 8.0f, bounds.y + 12.0f, bounds.x + bounds.width - 8.0f, RAYWHITE);
}

static void draw_node(Profiler *profiler, Profile_Call *node, float x, float y, float width) {
    if (width < 1.0f) {
        return;
    }
    Rectangle rectangle = {x, y, width - 1.0f, ROW_HEIGHT - 1.0f};
    bool hovered = CheckCollisionPointRec(GetMousePosition(), rectangle);
    if (hovered) {
        profiler->hovered = node;
    }
    Color color = node_color(node->function);
    if (hovered) {
        color = ColorBrightness(color, 0.25f);
    }
    DrawRectangleRec(rectangle, color);

    String name = node->function->name;
    if (width > 12.0f) {
        draw_clipped_text(profiler->gui.font, name, x + 3.0f, y + 2.0f, x + width - 2.0f, (Color){20, 20, 20, 255});
    }
}

static void draw_subtree(Profiler *profiler, Profile_Call *node, float x, float y, float width) {
    draw_node(profiler, node, x, y, width);
    if (node->time == 0) {
        return;
    }
    float child_x = x;
    for (size_t i = 0; i < node->children_size; i++) {
        Profile_Call *child = node->children[i];
        float child_width = width * (double)child->time / (double)node->time;
        draw_subtree(profiler, child, child_x, y + ROW_HEIGHT, child_width);
        child_x += child_width;
    }
}

static size_t call_depth(Profile_Call *node) {
    size_t depth = 0;
    for (Profile_Call *ancestor = node->parent; ancestor != NULL; ancestor = ancestor->parent) {
        depth++;
    }
    return depth;
}

static size_t call_max_depth(Profile_Call *node) {
    size_t max_depth = 0;
    for (size_t i = 0; i < node->children_size; i++) {
        size_t child_depth = call_max_depth(node->children[i]) + 1;
        if (child_depth > max_depth) {
            max_depth = child_depth;
        }
    }
    return max_depth;
}

static float flamegraph_content_height(Profile_Call *focus) {
    return (float)(call_depth(focus) + 1 + call_max_depth(focus)) * ROW_HEIGHT;
}

static void draw_tooltip(Profiler *profiler, Profile_Call *node) {
    Font font = profiler->gui.font;
    String name = node->function->name;
    char line[256];
    double milliseconds = (double)node->time / 1e6;
    double percent = profiler->total_time > 0 ? (double)node->time / (double)profiler->total_time * 100.0 : 0.0;
    int length = snprintf(line, sizeof(line), "%.*s   %.3f ms   %.1f%%   %llu call(s)", (int)name.length, name.content, milliseconds, percent, (unsigned long long)node->calls);
    String text = {line, (size_t)length};

    Vector2 mouse = GetMousePosition();
    Vector2 size = {measure_text_width(font, text) + 12.0f, (float)font.baseSize + 8.0f};
    float x = mouse.x + 12.0f;
    float y = mouse.y + 12.0f;
    if (x + size.x > (float)GetScreenWidth()) {
        x = (float)GetScreenWidth() - size.x;
    }
    if (y + size.y > (float)GetScreenHeight()) {
        y = (float)GetScreenHeight() - size.y;
    }
    DrawRectangle((int)x, (int)y, (int)size.x, (int)size.y, (Color){30, 30, 30, 240});
    DrawRectangleLines((int)x, (int)y, (int)size.x, (int)size.y, (Color){90, 90, 90, 255});
    draw_clipped_text(font, text, x + 6.0f, y + 4.0f, x + size.x, RAYWHITE);
}

static void flamegraph_panel_draw(Flamegraph_Panel *flamegraph_panel, GUI *gui, Rectangle bounds) {
    Profiler *profiler = gui->context;
    DrawRectangleRec(bounds, (Color){24, 24, 28, 255});
    profiler->hovered = NULL;

    Profile_Call *focus = profiler->focus;
    size_t focus_depth = call_depth(focus);
    Rectangle flame_bounds = {bounds.x, bounds.y + HEADER_HEIGHT, bounds.width, bounds.height - HEADER_HEIGHT};
    float base = flame_bounds.y - floorf(flamegraph_panel->scrollbar.scroll_y);

    BeginScissorMode((int)flame_bounds.x, (int)flame_bounds.y, (int)flame_bounds.width, (int)flame_bounds.height);
    Profile_Call *ancestor = focus->parent;
    for (size_t i = focus_depth; i > 0; i--) {
        float y = base + (float)(i - 1) * ROW_HEIGHT;
        draw_node(profiler, ancestor, bounds.x, y, bounds.width);
        ancestor = ancestor->parent;
    }
    draw_subtree(profiler, focus, bounds.x, base + (float)focus_depth * ROW_HEIGHT, bounds.width);
    EndScissorMode();
    draw_panel_scrollbar(flame_bounds, flamegraph_content_height(focus), &flamegraph_panel->scrollbar);

    draw_header(profiler, bounds, "click to zoom, right-click to reset, Tab: functions, Q: quit");
    if (profiler->hovered != NULL) {
        draw_tooltip(profiler, profiler->hovered);
    }
}

static void flamegraph_panel_handle_input(Flamegraph_Panel *flamegraph_panel, GUI *gui) {
    Profiler *profiler = gui->context;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && profiler->hovered != NULL) {
        profiler->focus = profiler->hovered;
        flamegraph_panel->scrollbar.scroll_y = (float)call_depth(profiler->focus) * ROW_HEIGHT;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        profiler->focus = profiler->root;
        flamegraph_panel->scrollbar.scroll_y = 0;
    }
    float flame_height = flamegraph_panel->panel.bounds.height - HEADER_HEIGHT;
    scrollbar_wheel_input(&flamegraph_panel->scrollbar, flame_height, flamegraph_content_height(profiler->focus), ROW_HEIGHT);
}

static void flamegraph_panel_handle_step(Flamegraph_Panel *flamegraph_panel, GUI *gui) {
    (void)flamegraph_panel;
    (void)gui;
}

static Panel *flamegraph_panel_pick(Flamegraph_Panel *flamegraph_panel, Vector2 position) {
    (void)position;
    return &flamegraph_panel->panel;
}

static Flamegraph_Panel make_flamegraph_panel(float weight) {
    return (Flamegraph_Panel){
        .panel = {
            .draw = (void (*)(Panel *, GUI *, Rectangle))flamegraph_panel_draw,
            .handle_input = (void (*)(Panel *, GUI *))flamegraph_panel_handle_input,
            .handle_step = (void (*)(Panel *, GUI *))flamegraph_panel_handle_step,
            .pick = (Panel * (*)(Panel *, Vector2)) flamegraph_panel_pick,
            .weight = weight,
        },
    };
}

static int compare_by_name(const void *a, const void *b) {
    String name_a = (*(IR_Function *const *)a)->name;
    String name_b = (*(IR_Function *const *)b)->name;
    size_t length = name_a.length < name_b.length ? name_a.length : name_b.length;
    int order = memcmp(name_a.content, name_b.content, length);
    if (order != 0) {
        return order;
    }
    if (name_a.length != name_b.length) {
        return name_a.length < name_b.length ? -1 : 1;
    }
    return 0;
}

static int compare_by_self_time(const void *a, const void *b) {
    const IR_Function *function_a = *(IR_Function *const *)a;
    const IR_Function *function_b = *(IR_Function *const *)b;
    if (function_a->profile.exclusive_time != function_b->profile.exclusive_time) {
        return function_a->profile.exclusive_time > function_b->profile.exclusive_time ? -1 : 1;
    }
    return 0;
}

static int compare_by_total_time(const void *a, const void *b) {
    const IR_Function *function_a = *(IR_Function *const *)a;
    const IR_Function *function_b = *(IR_Function *const *)b;
    if (function_a->profile.inclusive_time != function_b->profile.inclusive_time) {
        return function_a->profile.inclusive_time > function_b->profile.inclusive_time ? -1 : 1;
    }
    return compare_by_self_time(a, b);
}

static int compare_by_calls(const void *a, const void *b) {
    const IR_Function *function_a = *(IR_Function *const *)a;
    const IR_Function *function_b = *(IR_Function *const *)b;
    if (function_a->profile.calls != function_b->profile.calls) {
        return function_a->profile.calls > function_b->profile.calls ? -1 : 1;
    }
    return compare_by_self_time(a, b);
}

static void sort_functions(Profiler *profiler) {
    int (*compare)(const void *, const void *);
    switch (profiler->sort_column) {
    case SORT_COLUMN__FUNCTION:
        compare = compare_by_name;
        break;
    case SORT_COLUMN__TOTAL_TIME:
        compare = compare_by_total_time;
        break;
    case SORT_COLUMN__CALLS:
        compare = compare_by_calls;
        break;
    default:
        compare = compare_by_self_time;
        break;
    }
    qsort(profiler->functions, profiler->functions_size, sizeof(IR_Function *), compare);
    if (profiler->sort_reversed) {
        for (size_t i = 0, j = profiler->functions_size - 1; i < j; i++, j--) {
            IR_Function *swap = profiler->functions[i];
            profiler->functions[i] = profiler->functions[j];
            profiler->functions[j] = swap;
        }
    }
}

#define HEADER_GLYPH_WIDTH 9
#define HEADER_GLYPH__BULLET 7
#define HEADER_GLYPH__HOLLOW_BULLET 9
#define HEADER_GLYPH__ARROW_UP 30
#define HEADER_GLYPH__ARROW_DOWN 31
#define HEADER_GLYPH__SQUARE_BULLET 256
#define VALUE_COLUMN_WIDTH (9 * 9.0f)

typedef struct {
    float name_left;
    float name_right;
    float self_left;
    float self_right;
    float total_left;
    float total_right;
    float calls_left;
    float calls_right;
} Functions_Columns;

static Functions_Columns functions_panel_columns(Rectangle bounds) {
    float padding = 12.0f;
    float gap = 12.0f;
    float calls_right = bounds.x + bounds.width - padding;
    float calls_left = calls_right - VALUE_COLUMN_WIDTH;
    float total_right = calls_left - gap;
    float total_left = total_right - VALUE_COLUMN_WIDTH * 2;
    float self_right = total_left - gap;
    float self_left = self_right - VALUE_COLUMN_WIDTH * 2;
    return (Functions_Columns){
        .name_left = bounds.x + padding,
        .name_right = self_left - gap,
        .self_left = self_left,
        .self_right = self_right,
        .total_left = total_left,
        .total_right = total_right,
        .calls_left = calls_left,
        .calls_right = calls_right,
    };
}

static bool functions_panel_header_hit(Rectangle bounds, Vector2 mouse, Sort_Column *sort_column) {
    float header_y = bounds.y + HEADER_HEIGHT + 6.0f;
    if (mouse.y < header_y || mouse.y >= header_y + ROW_HEIGHT) {
        return false;
    }
    Functions_Columns columns = functions_panel_columns(bounds);
    if (mouse.x >= columns.name_left && mouse.x < columns.name_right) {
        *sort_column = SORT_COLUMN__FUNCTION;
        return true;
    }
    if (mouse.x >= columns.self_left && mouse.x < columns.self_right) {
        *sort_column = SORT_COLUMN__SELF_TIME;
        return true;
    }
    if (mouse.x >= columns.total_left && mouse.x < columns.total_right) {
        *sort_column = SORT_COLUMN__TOTAL_TIME;
        return true;
    }
    if (mouse.x >= columns.calls_left && mouse.x <= columns.calls_right) {
        *sort_column = SORT_COLUMN__CALLS;
        return true;
    }
    return false;
}

static Color header_color(Sort_Column column, Sort_Column active_column, bool hovered, Sort_Column hovered_column) {
    if (column == active_column) {
        return RAYWHITE;
    }
    if (hovered && hovered_column == column) {
        return LIGHTGRAY;
    }
    return GRAY;
}

static void draw_column_header(Font font, String label, float left, float right, float y, Color color, bool active, bool descending) {
    draw_clipped_text(font, label, left, y, right, color);
    int codepoint = active ? (descending ? HEADER_GLYPH__ARROW_DOWN : HEADER_GLYPH__ARROW_UP) : HEADER_GLYPH__HOLLOW_BULLET;
    DrawTextCodepoint(font, codepoint, (Vector2){right - HEADER_GLYPH_WIDTH, y}, (float)font.baseSize, color);
}

static void draw_time_bar(Font font, IR_Function *function, uint64_t time, uint64_t total_time, float left, float right, float y) {
    double fraction = total_time > 0 ? (double)time / (double)total_time : 0.0;
    float width = right - left;
    DrawRectangle((int)left, (int)y, (int)width, ROW_HEIGHT - 2, (Color){40, 40, 48, 255});
    DrawRectangle((int)left, (int)y, (int)(width * fraction), ROW_HEIGHT - 2, node_color(function));
    char percent[32];
    int percent_length = snprintf(percent, sizeof(percent), "%.1f%%", fraction * 100.0);
    draw_text_right_aligned(font, (String){percent, (size_t)percent_length}, right - 6.0f, y + 2.0f, RAYWHITE);
}

static float functions_panel_rows_top(Rectangle bounds) {
    return bounds.y + HEADER_HEIGHT + 6.0f + ROW_HEIGHT + 4.0f;
}

static void functions_panel_draw(Functions_Panel *functions_panel, GUI *gui, Rectangle bounds) {
    Profiler *profiler = gui->context;
    Font font = gui->font;
    DrawRectangleRec(bounds, (Color){24, 24, 28, 255});

    Functions_Columns columns = functions_panel_columns(bounds);

    Vector2 mouse = GetMousePosition();
    Sort_Column hovered_column;
    bool header_hovered = functions_panel_header_hit(bounds, mouse, &hovered_column);

    float y = bounds.y + HEADER_HEIGHT + 6.0f;
    Sort_Column sort_column = profiler->sort_column;
    bool descending = (sort_column != SORT_COLUMN__FUNCTION) != profiler->sort_reversed;
    draw_column_header(font, (String){"Function", 8}, columns.name_left, columns.name_right, y + 2.0f, header_color(SORT_COLUMN__FUNCTION, sort_column, header_hovered, hovered_column), sort_column == SORT_COLUMN__FUNCTION, descending);
    draw_column_header(font, (String){"Self", 4}, columns.self_left, columns.self_right, y + 2.0f, header_color(SORT_COLUMN__SELF_TIME, sort_column, header_hovered, hovered_column), sort_column == SORT_COLUMN__SELF_TIME, descending);
    draw_column_header(font, (String){"Total", 5}, columns.total_left, columns.total_right, y + 2.0f, header_color(SORT_COLUMN__TOTAL_TIME, sort_column, header_hovered, hovered_column), sort_column == SORT_COLUMN__TOTAL_TIME, descending);
    draw_column_header(font, (String){"Calls", 5}, columns.calls_left, columns.calls_right, y + 2.0f, header_color(SORT_COLUMN__CALLS, sort_column, header_hovered, hovered_column), sort_column == SORT_COLUMN__CALLS, descending);
    y += ROW_HEIGHT;
    DrawLine((int)columns.name_left, (int)y, (int)columns.calls_right, (int)y, (Color){70, 70, 80, 255});

    float rows_top = functions_panel_rows_top(bounds);
    float rows_bottom = bounds.y + bounds.height;
    Rectangle rows_bounds = {bounds.x, rows_top, bounds.width, rows_bottom - rows_top};
    BeginScissorMode((int)rows_bounds.x, (int)rows_bounds.y, (int)rows_bounds.width, (int)rows_bounds.height);
    y = rows_top - floorf(functions_panel->scrollbar.scroll_y);
    for (size_t i = 0; i < profiler->functions_size; i++, y += ROW_HEIGHT) {
        if (y + ROW_HEIGHT <= rows_top) {
            continue;
        }
        if (y >= rows_bottom) {
            break;
        }
        IR_Function *function = profiler->functions[i];

        if (CheckCollisionPointRec(mouse, rows_bounds) && mouse.y >= y && mouse.y < y + ROW_HEIGHT) {
            DrawRectangle((int)bounds.x, (int)y, (int)bounds.width, ROW_HEIGHT - 2, (Color){48, 48, 58, 255});
        }

        draw_clipped_text(font, function->name, columns.name_left, y + 2.0f, columns.name_right, RAYWHITE);
        draw_time_bar(font, function, function->profile.exclusive_time, profiler->total_time, columns.self_left, columns.self_right, y);
        draw_time_bar(font, function, function->profile.inclusive_time, profiler->total_time, columns.total_left, columns.total_right, y);

        char calls[32];
        int calls_length = snprintf(calls, sizeof(calls), "%llu", (unsigned long long)function->profile.calls);
        draw_text_right_aligned(font, (String){calls, (size_t)calls_length}, columns.calls_right, y + 2.0f, RAYWHITE);
    }
    EndScissorMode();
    draw_panel_scrollbar(rows_bounds, (float)profiler->functions_size * ROW_HEIGHT, &functions_panel->scrollbar);

    draw_header(profiler, bounds, "click a column to sort   Tab: flamegraph, Q: quit");
}

static void functions_panel_handle_input(Functions_Panel *functions_panel, GUI *gui) {
    Profiler *profiler = gui->context;
    Rectangle bounds = functions_panel->panel.bounds;
    Sort_Column sort_column;
    if (functions_panel_header_hit(bounds, GetMousePosition(), &sort_column)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (sort_column == profiler->sort_column) {
                profiler->sort_reversed = !profiler->sort_reversed;
            } else {
                profiler->sort_column = sort_column;
                profiler->sort_reversed = false;
            }
            sort_functions(profiler);
            functions_panel->scrollbar.scroll_y = 0;
        }
    }
    float rows_height = bounds.y + bounds.height - functions_panel_rows_top(bounds);
    scrollbar_wheel_input(&functions_panel->scrollbar, rows_height, (float)profiler->functions_size * ROW_HEIGHT, ROW_HEIGHT);
}

static void functions_panel_handle_step(Functions_Panel *functions_panel, GUI *gui) {
    (void)functions_panel;
    (void)gui;
}

static Panel *functions_panel_pick(Functions_Panel *functions_panel, Vector2 position) {
    (void)position;
    return &functions_panel->panel;
}

static Functions_Panel make_functions_panel(float weight) {
    return (Functions_Panel){
        .panel = {
            .draw = (void (*)(Panel *, GUI *, Rectangle))functions_panel_draw,
            .handle_input = (void (*)(Panel *, GUI *))functions_panel_handle_input,
            .handle_step = (void (*)(Panel *, GUI *))functions_panel_handle_step,
            .pick = (Panel * (*)(Panel *, Vector2)) functions_panel_pick,
            .weight = weight,
        },
    };
}

void profile_show(IR_Module *module) {
    Profile_Call *root = module->profile_calls;
    if (root == NULL) {
        return;
    }
    for (size_t i = 0; i < root->children_size; i++) {
        root->time += root->children[i]->time;
    }
    if (root->time == 0) {
        return;
    }
    root = root->children[0];
    root->parent = NULL;

    IR_Function **functions = malloc(module->functions.size * sizeof(IR_Function *));
    size_t functions_size = 0;
    for (size_t i = 0; i < module->functions.size; i++) {
        IR_Function *function = module->functions.items[i];
        if (function->profile.calls > 0) {
            functions[functions_size++] = function;
        }
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1000, 600, "Code IR Profiler");
    SetExitKey(KEY_Q);
    SetTargetFPS(60);

    Flamegraph_Panel flamegraph_panel = make_flamegraph_panel(1.0f);
    Functions_Panel functions_panel = make_functions_panel(1.0f);
    Profiler profiler = {
        .gui = {.font = load_bitmap_font("fonts/Code.font"), .root_panel = &flamegraph_panel.panel},
        .module = module,
        .root = root,
        .total_time = root->time,
        .focus = root,
        .functions = functions,
        .functions_size = functions_size,
        .sort_column = SORT_COLUMN__SELF_TIME,
        .flamegraph_panel = &flamegraph_panel.panel,
        .functions_panel = &functions_panel.panel,
    };
    profiler.gui.context = &profiler;
    sort_functions(&profiler);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_TAB)) {
            profiler.gui.root_panel = profiler.gui.root_panel == profiler.flamegraph_panel ? profiler.functions_panel : profiler.flamegraph_panel;
            profiler.hovered = NULL;
        }
        gui_render_frame(&profiler.gui);
    }

    free(functions);
    UnloadFont(profiler.gui.font);
    CloseWindow();
}
