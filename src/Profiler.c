#include "Profiler.h"
#include "GUI.h"
#include <inttypes.h>
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t profile_nanoseconds(uint64_t ticks) {
    static mach_timebase_info_data_t timebase;
    if (timebase.denom == 0) {
        mach_timebase_info(&timebase);
    }
    return ticks * timebase.numer / timebase.denom;
}

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

typedef struct {
    Panel panel;
    Scrollbar scrollbar;
} Profile_Source_Panel;

typedef struct {
    Panel panel;
    Scrollbar scrollbar;
} Sandwich_Panel;

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
    double max_metric;
    uint64_t max_calls;
    uint64_t total_bytes;
    bool memory_mode;
    bool show_help;
    File *sources;
    IR_Function *selected_function;
    File *selected_source;
    String selected_source_path;
    Profile_Call *sandwich_callers;
    Profile_Call *sandwich_callees;
    bool sandwich_scroll_pending;
    Panel *flamegraph_panel;
    Panel *functions_panel;
    Panel *source_panel;
    Panel *sandwich_panel;
} Profiler;

static double function_metric(Sort_Column sort_column, IR_Function *function) {
    switch (sort_column) {
    case SORT_COLUMN__TOTAL_TIME:
        return (double)function->profile.inclusive_time;
    case SORT_COLUMN__CALLS:
        return (double)function->profile.calls;
    default:
        return (double)function->profile.exclusive_time;
    }
}

static Color node_color(Profiler *profiler, IR_Function *function) {
    double heat = profiler->max_metric > 0.0 ? function_metric(profiler->sort_column, function) / profiler->max_metric : 0.0;
    float position = 1.0f - (float)heat;
    return ColorFromHSV(60.0f * position, 0.85f, 0.55f + 0.4f * position);
}

static bool color_is_dark(Color color) {
    return color.r * 299 + color.g * 587 + color.b * 114 < 128000;
}

static void draw_clipped_text(Font font, String text, float x, float y, float right, Color color) {
    Vector2 position = {x, y};
    draw_text(font, text, color, &position, right);
}

static int format_bytes(char *buffer, size_t buffer_size, uint64_t bytes) {
    if (bytes >= 1024 * 1024) {
        return snprintf(buffer, buffer_size, "%.1f MB", (double)bytes / (1024.0 * 1024.0));
    }
    if (bytes >= 1024) {
        return snprintf(buffer, buffer_size, "%.1f KB", (double)bytes / 1024.0);
    }
    return snprintf(buffer, buffer_size, "%llu B", (unsigned long long)bytes);
}

#define TAB_COUNT 4
#define BUTTON_COUNT (TAB_COUNT + 1)

static const char *button_labels[BUTTON_COUNT] = {"Flamegraph", "Memory", "Functions", "Sandwich", "?"};

static Panel *tab_panel(Profiler *profiler, size_t index) {
    if (index <= 1) {
        return profiler->flamegraph_panel;
    }
    if (index == 2) {
        return profiler->functions_panel;
    }
    return profiler->sandwich_panel;
}

static bool tab_active(Profiler *profiler, size_t index) {
    if (profiler->gui.root_panel != tab_panel(profiler, index)) {
        return false;
    }
    if (index <= 1) {
        return profiler->memory_mode == (index == 1);
    }
    return true;
}

static void header_buttons(Font font, float right, float top, Rectangle buttons[BUTTON_COUNT]) {
    for (size_t i = BUTTON_COUNT; i-- > 0;) {
        float width = measure_text_width(font, string_from((char *)button_labels[i])) + 20.0f;
        buttons[i] = (Rectangle){right - width, top, width, HEADER_HEIGHT - 16.0f};
        right = buttons[i].x - (i == BUTTON_COUNT - 1 ? 14.0f : 6.0f);
    }
}

static void draw_header(Profiler *profiler, Rectangle bounds, bool memory) {
    DrawRectangle((int)bounds.x, (int)bounds.y, (int)bounds.width, HEADER_HEIGHT, (Color){36, 36, 42, 255});
    char total[64];
    if (memory) {
        char bytes_text[32];
        format_bytes(bytes_text, sizeof(bytes_text), profiler->total_bytes);
        snprintf(total, sizeof(total), "%s allocated", bytes_text);
    } else {
        snprintf(total, sizeof(total), "%.3f ms total", (double)profile_nanoseconds(profiler->total_time) / 1e6);
    }
    Font font = profiler->gui.font;
    Rectangle buttons[BUTTON_COUNT];
    header_buttons(font, bounds.x + bounds.width - 8.0f, bounds.y + 8.0f, buttons);
    float text_y = bounds.y + 8.0f + floorf((HEADER_HEIGHT - 16.0f - (float)font.baseSize) / 2.0f);
    Vector2 mouse = GetMousePosition();
    for (size_t i = 0; i < BUTTON_COUNT; i++) {
        Rectangle button = buttons[i];
        bool active = i < TAB_COUNT ? tab_active(profiler, i) : profiler->show_help;
        bool hovered = CheckCollisionPointRec(mouse, button);
        Color fill = active ? (Color){70, 70, 86, 255} : hovered ? (Color){56, 56, 68, 255} : (Color){44, 44, 52, 255};
        DrawRectangleRec(button, fill);
        if (active) {
            DrawRectangleLinesEx(button, 1.0f, (Color){110, 110, 130, 255});
        }
        draw_clipped_text(font, string_from((char *)button_labels[i]), button.x + 10.0f, text_y, button.x + button.width, active ? RAYWHITE : LIGHTGRAY);
        if (hovered) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        }
    }
    char header[256];
    int length = snprintf(header, sizeof(header), "%.*s   %s", STRING(profiler->module->lexed_file.file.path), total);
    draw_clipped_text(font, (String){header, (size_t)length}, bounds.x + 8.0f, text_y, buttons[0].x - 12.0f, RAYWHITE);
}

static IR_Instruction *function_first_line(IR_Function *function) {
    for (size_t b = 0; b < function->blocks.size; b++) {
        IR_Block *block = function->blocks.items[b];
        for (size_t i = 0; i < block->instructions.size; i++) {
            IR_Instruction *instruction = block->instructions.items[i];
            if (instruction->kind == IR_INSTRUCTION__DBG_LINE) {
                return instruction;
            }
        }
    }
    return NULL;
}

static void free_calls(Profile_Call *node) {
    for (size_t i = 0; i < node->children_size; i++) {
        free_calls(node->children[i]);
    }
    free(node->children);
    free(node);
}

static void merge_callees(Profile_Call *merged, Profile_Call *node) {
    for (size_t i = 0; i < node->children_size; i++) {
        Profile_Call *child = node->children[i];
        Profile_Call *merged_child = profile_call_child(merged, child->function);
        merged_child->time += child->time;
        merged_child->calls += child->calls;
        merged_child->bytes += child->bytes;
        merge_callees(merged_child, child);
    }
}

// The whole ancestor chain of an occurrence gets the occurrence's weight.
static void merge_callers(Profile_Call *merged, Profile_Call *node) {
    Profile_Call *merged_node = merged;
    for (Profile_Call *caller = node->parent; caller != NULL; caller = caller->parent) {
        merged_node = profile_call_child(merged_node, caller->function);
        merged_node->time += node->time;
        merged_node->calls += node->calls;
        merged_node->bytes += node->bytes;
    }
}

// Node time/bytes are inclusive, so only outermost occurrences count — an inner
// recursive occurrence is already contained in its ancestor's totals.
static void merge_occurrences(Profiler *profiler, Profile_Call *node, bool inside) {
    bool matches = node->function == profiler->selected_function;
    if (matches && !inside) {
        Profile_Call *callees = profiler->sandwich_callees;
        callees->time += node->time;
        callees->calls += node->calls;
        callees->bytes += node->bytes;
        merge_callees(callees, node);
        merge_callers(profiler->sandwich_callers, node);
    }
    for (size_t i = 0; i < node->children_size; i++) {
        merge_occurrences(profiler, node->children[i], inside || matches);
    }
}

static void build_sandwich(Profiler *profiler) {
    if (profiler->sandwich_callees != NULL) {
        free_calls(profiler->sandwich_callees);
        free_calls(profiler->sandwich_callers);
    }
    profiler->sandwich_callees = calloc(1, sizeof(Profile_Call));
    profiler->sandwich_callees->function = profiler->selected_function;
    profiler->sandwich_callers = calloc(1, sizeof(Profile_Call));
    profiler->sandwich_callers->function = profiler->selected_function;
    merge_occurrences(profiler, profiler->root, false);
    profiler->sandwich_callers->time = profiler->sandwich_callees->time;
    profiler->sandwich_callers->calls = profiler->sandwich_callees->calls;
    profiler->sandwich_callers->bytes = profiler->sandwich_callees->bytes;
    profiler->sandwich_scroll_pending = true;
}

static void select_function(Profiler *profiler, IR_Function *function) {
    profiler->selected_function = function;
    profiler->selected_source = NULL;
    build_sandwich(profiler);
    IR_Instruction *first_line = function_first_line(function);
    if (first_line == NULL || profiler->sources == NULL) {
        return;
    }
    String path = first_line->dbg_line_instruction.location.source;
    File *file = NULL;
    for (size_t i = 0; i < profiler->module->source_files.size; i++) {
        if (string_equals(profiler->module->source_files.items[i], path)) {
            file = &profiler->sources[i];
            break;
        }
    }
    if (file == NULL || file->lines_size == 0) {
        return;
    }
    profiler->selected_source = file;
    profiler->selected_source_path = path;

    Profile_Source_Panel *source_panel = (Profile_Source_Panel *)profiler->source_panel;
    text_panel_scroll_to_line(&source_panel->scrollbar, source_panel->panel.bounds.height - ROW_HEIGHT, first_line->dbg_line_instruction.location.line, file->lines_size, profiler->gui.font.baseSize);
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
    Color color = node_color(profiler, node->function);
    if (hovered) {
        color = ColorBrightness(color, 0.25f);
    }
    DrawRectangleRec(rectangle, color);

    String name = node->function->name;
    if (width > 12.0f) {
        draw_clipped_text(profiler->gui.font, name, x + 3.0f, y + 2.0f, x + width - 2.0f, color_is_dark(color) ? RAYWHITE : (Color){20, 20, 20, 255});
    }
}

#define MIN_NODE_WIDTH 2.0f

static uint64_t call_metric(Profiler *profiler, Profile_Call *node) {
    return profiler->memory_mode ? node->bytes : node->time;
}

static void draw_subtree(Profiler *profiler, Profile_Call *node, float x, float y, float width, float row_step);

static void draw_subtree_children(Profiler *profiler, Profile_Call *node, float x, float y, float width, float row_step) {
    uint64_t node_metric = call_metric(profiler, node);
    if (node_metric == 0) {
        return;
    }
    float child_x = x;
    for (size_t i = 0; i < node->children_size; i++) {
        Profile_Call *child = node->children[i];
        uint64_t child_metric = call_metric(profiler, child);
        float child_width = width * (double)child_metric / (double)node_metric;
        bool called = profiler->memory_mode ? child_metric > 0 : child->calls > 0;
        if (called && child_width < MIN_NODE_WIDTH) {
            child_width = MIN_NODE_WIDTH;
        }
        if (!called && child_width <= 0.0f) {
            continue;
        }
        if (child_x + child_width > x + width) {
            child_width = x + width - child_x;
        }
        if (child_width <= 0.0f) {
            break;
        }
        draw_subtree(profiler, child, child_x, y, child_width, row_step);
        child_x += child_width;
    }
}

static void draw_subtree(Profiler *profiler, Profile_Call *node, float x, float y, float width, float row_step) {
    draw_node(profiler, node, x, y, width);
    draw_subtree_children(profiler, node, x, y + row_step, width, row_step);
}

static size_t call_depth(Profile_Call *node) {
    size_t depth = 0;
    for (Profile_Call *ancestor = node->parent; ancestor != NULL; ancestor = ancestor->parent) {
        depth++;
    }
    return depth;
}

// Depth of the deepest *drawn* row: mirrors draw_subtree_children's layout and
// stops where rectangles collapse below one pixel, so the scroll range matches
// what is actually visible.
static size_t call_max_depth(Profiler *profiler, Profile_Call *node, float width) {
    size_t max_depth = 0;
    uint64_t node_metric = call_metric(profiler, node);
    if (node_metric == 0) {
        return 0;
    }
    float child_x = 0.0f;
    for (size_t i = 0; i < node->children_size; i++) {
        Profile_Call *child = node->children[i];
        uint64_t child_metric = call_metric(profiler, child);
        float child_width = width * (double)child_metric / (double)node_metric;
        bool called = profiler->memory_mode ? child_metric > 0 : child->calls > 0;
        if (called && child_width < MIN_NODE_WIDTH) {
            child_width = MIN_NODE_WIDTH;
        }
        if (!called && child_width <= 0.0f) {
            continue;
        }
        if (child_x + child_width > width) {
            child_width = width - child_x;
        }
        if (child_width <= 0.0f) {
            break;
        }
        if (child_width >= 1.0f) {
            size_t child_depth = call_max_depth(profiler, child, child_width) + 1;
            if (child_depth > max_depth) {
                max_depth = child_depth;
            }
        }
        child_x += child_width;
    }
    return max_depth;
}

static float flamegraph_content_height(Profiler *profiler, Profile_Call *focus, float width) {
    return (float)(call_depth(focus) + 1 + call_max_depth(profiler, focus, width)) * ROW_HEIGHT;
}

static void draw_tooltip(Profiler *profiler, Profile_Call *node) {
    Font font = profiler->gui.font;
    String name = node->function->name;
    char line[256];
    int length;
    if (profiler->memory_mode) {
        char bytes_text[32];
        format_bytes(bytes_text, sizeof(bytes_text), node->bytes);
        double percent = profiler->total_bytes > 0 ? (double)node->bytes / (double)profiler->total_bytes * 100.0 : 0.0;
        length = snprintf(line, sizeof(line), "%.*s   %s   %.1f%%   %llu call(s)", (int)name.length, name.content, bytes_text, percent, (unsigned long long)node->calls);
    } else {
        double milliseconds = (double)profile_nanoseconds(node->time) / 1e6;
        double percent = profiler->total_time > 0 ? (double)node->time / (double)profiler->total_time * 100.0 : 0.0;
        length = snprintf(line, sizeof(line), "%.*s   %.3f ms   %.1f%%   %llu call(s)", (int)name.length, name.content, milliseconds, percent, (unsigned long long)node->calls);
    }
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
    draw_subtree(profiler, focus, bounds.x, base + (float)focus_depth * ROW_HEIGHT, bounds.width, ROW_HEIGHT);
    EndScissorMode();
    draw_panel_scrollbar(flame_bounds, flamegraph_content_height(profiler, focus, bounds.width), &flamegraph_panel->scrollbar);

    draw_header(profiler, bounds, profiler->memory_mode);
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
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) && profiler->hovered != NULL) {
        select_function(profiler, profiler->hovered->function);
        gui->root_panel = profiler->functions_panel;
        profiler->hovered = NULL;
    }
    float flame_height = flamegraph_panel->panel.bounds.height - HEADER_HEIGHT;
    scrollbar_wheel_input(&flamegraph_panel->scrollbar, flame_height, flamegraph_content_height(profiler, profiler->focus, flamegraph_panel->panel.bounds.width), ROW_HEIGHT);
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

static float sandwich_content_height(Profiler *profiler, float width) {
    return (float)(call_max_depth(profiler, profiler->sandwich_callers, width) + 1 + call_max_depth(profiler, profiler->sandwich_callees, width)) * ROW_HEIGHT;
}

static void sandwich_panel_draw(Sandwich_Panel *sandwich_panel, GUI *gui, Rectangle bounds) {
    Profiler *profiler = gui->context;
    // The sandwich always shows time; memory mode belongs to the Memory tab.
    bool memory_mode = profiler->memory_mode;
    profiler->memory_mode = false;
    DrawRectangleRec(bounds, (Color){24, 24, 28, 255});
    profiler->hovered = NULL;

    Profile_Call *callers = profiler->sandwich_callers;
    Profile_Call *callees = profiler->sandwich_callees;
    Rectangle flame_bounds = {bounds.x, bounds.y + HEADER_HEIGHT, bounds.width, bounds.height - HEADER_HEIGHT};
    size_t callers_depth = call_max_depth(profiler, callers, bounds.width);
    if (profiler->sandwich_scroll_pending) {
        float snap = (float)callers_depth * ROW_HEIGHT - (flame_bounds.height - ROW_HEIGHT) / 2.0f;
        sandwich_panel->scrollbar.scroll_y = snap > 0.0f ? snap : 0.0f;
        profiler->sandwich_scroll_pending = false;
    }
    float center_y = flame_bounds.y - floorf(sandwich_panel->scrollbar.scroll_y) + (float)callers_depth * ROW_HEIGHT;

    BeginScissorMode((int)flame_bounds.x, (int)flame_bounds.y, (int)flame_bounds.width, (int)flame_bounds.height);
    draw_subtree_children(profiler, callers, bounds.x, center_y - ROW_HEIGHT, bounds.width, -ROW_HEIGHT);
    draw_subtree(profiler, callees, bounds.x, center_y, bounds.width, ROW_HEIGHT);
    EndScissorMode();
    draw_panel_scrollbar(flame_bounds, sandwich_content_height(profiler, bounds.width), &sandwich_panel->scrollbar);

    draw_header(profiler, bounds, false);
    if (profiler->hovered != NULL) {
        draw_tooltip(profiler, profiler->hovered);
    }
    profiler->memory_mode = memory_mode;
}

static void sandwich_panel_handle_input(Sandwich_Panel *sandwich_panel, GUI *gui) {
    Profiler *profiler = gui->context;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && profiler->hovered != NULL && profiler->hovered->function != profiler->selected_function) {
        select_function(profiler, profiler->hovered->function);
        profiler->hovered = NULL;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) && profiler->hovered != NULL) {
        select_function(profiler, profiler->hovered->function);
        gui->root_panel = profiler->functions_panel;
        profiler->hovered = NULL;
    }
    bool memory_mode = profiler->memory_mode;
    profiler->memory_mode = false;
    float flame_height = sandwich_panel->panel.bounds.height - HEADER_HEIGHT;
    scrollbar_wheel_input(&sandwich_panel->scrollbar, flame_height, sandwich_content_height(profiler, sandwich_panel->panel.bounds.width), ROW_HEIGHT);
    profiler->memory_mode = memory_mode;
}

static void sandwich_panel_handle_step(Sandwich_Panel *sandwich_panel, GUI *gui) {
    (void)sandwich_panel;
    (void)gui;
}

static Panel *sandwich_panel_pick(Sandwich_Panel *sandwich_panel, Vector2 position) {
    (void)position;
    return &sandwich_panel->panel;
}

static Sandwich_Panel make_sandwich_panel(float weight) {
    return (Sandwich_Panel){
        .panel = {
            .draw = (void (*)(Panel *, GUI *, Rectangle))sandwich_panel_draw,
            .handle_input = (void (*)(Panel *, GUI *))sandwich_panel_handle_input,
            .handle_step = (void (*)(Panel *, GUI *))sandwich_panel_handle_step,
            .pick = (Panel * (*)(Panel *, Vector2)) sandwich_panel_pick,
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
    profiler->max_metric = 0.0;
    for (size_t i = 0; i < profiler->functions_size; i++) {
        double metric = function_metric(profiler->sort_column, profiler->functions[i]);
        if (metric > profiler->max_metric) {
            profiler->max_metric = metric;
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
    DrawTextCodepoint(font, codepoint, (Vector2){roundf(right - HEADER_GLYPH_WIDTH), roundf(y)}, (float)font.baseSize, color);
}

static void draw_value_bar(Profiler *profiler, Font font, IR_Function *function, bool active, double fraction, String text, float left, float right, float y) {
    float width = right - left;
    DrawRectangle((int)left, (int)y, (int)width, ROW_HEIGHT - 2, (Color){40, 40, 48, 255});
    Color fill = active ? node_color(profiler, function) : GRAY;
    DrawRectangle((int)left, (int)y, (int)(width * fraction), ROW_HEIGHT - 2, fill);
    draw_text_right_aligned(font, text, right - 6.0f, y + 2.0f, RAYWHITE);
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
        } else if (function == profiler->selected_function) {
            DrawRectangle((int)bounds.x, (int)y, (int)bounds.width, ROW_HEIGHT - 2, (Color){44, 44, 66, 255});
        }

        draw_clipped_text(font, function->name, columns.name_left, y + 2.0f, columns.name_right, RAYWHITE);

        char percent[32];
        double self_fraction = profiler->total_time > 0 ? (double)function->profile.exclusive_time / (double)profiler->total_time : 0.0;
        int percent_length = snprintf(percent, sizeof(percent), "%.1f%%", self_fraction * 100.0);
        draw_value_bar(profiler, font, function, sort_column == SORT_COLUMN__SELF_TIME, self_fraction, (String){percent, (size_t)percent_length}, columns.self_left, columns.self_right, y);

        double total_fraction = profiler->total_time > 0 ? (double)function->profile.inclusive_time / (double)profiler->total_time : 0.0;
        percent_length = snprintf(percent, sizeof(percent), "%.1f%%", total_fraction * 100.0);
        draw_value_bar(profiler, font, function, sort_column == SORT_COLUMN__TOTAL_TIME, total_fraction, (String){percent, (size_t)percent_length}, columns.total_left, columns.total_right, y);

        char calls[32];
        double calls_fraction = profiler->max_calls > 0 ? (double)function->profile.calls / (double)profiler->max_calls : 0.0;
        int calls_length = snprintf(calls, sizeof(calls), "%llu", (unsigned long long)function->profile.calls);
        draw_value_bar(profiler, font, function, sort_column == SORT_COLUMN__CALLS, calls_fraction, (String){calls, (size_t)calls_length}, columns.calls_left, columns.calls_right, y);
    }
    EndScissorMode();
    draw_panel_scrollbar(rows_bounds, (float)profiler->functions_size * ROW_HEIGHT, &functions_panel->scrollbar);

    draw_header(profiler, bounds, false);
}

static void functions_panel_handle_input(Functions_Panel *functions_panel, GUI *gui) {
    Profiler *profiler = gui->context;
    Rectangle bounds = functions_panel->panel.bounds;
    Vector2 mouse = GetMousePosition();
    Sort_Column sort_column;
    if (functions_panel_header_hit(bounds, mouse, &sort_column)) {
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
    float rows_top = functions_panel_rows_top(bounds);
    if (mouse.y >= rows_top && mouse.y < bounds.y + bounds.height) {
        size_t index = (size_t)((mouse.y - rows_top + functions_panel->scrollbar.scroll_y) / ROW_HEIGHT);
        if (index < profiler->functions_size) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                select_function(profiler, profiler->functions[index]);
            }
        }
    }
    float rows_height = bounds.y + bounds.height - rows_top;
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

static void profile_source_panel_draw(Profile_Source_Panel *source_panel, GUI *gui, Rectangle bounds) {
    Profiler *profiler = gui->context;
    Font font = gui->font;
    DrawRectangleRec(bounds, (Color){24, 24, 28, 255});
    float right = bounds.x + bounds.width;

    DrawRectangle((int)bounds.x, (int)bounds.y, (int)bounds.width, ROW_HEIGHT, (Color){36, 36, 42, 255});
    File *file = profiler->selected_source;
    if (file == NULL) {
        draw_clipped_text(font, string_from("no source info"), bounds.x + 12.0f, bounds.y + 2.0f, right, GRAY);
        return;
    }
    IR_Function *function = profiler->selected_function;
    char title[512];
    int title_length = snprintf(title, sizeof(title), "%.*s - %.*s   %.3f ms self", STRING(profiler->selected_source_path), STRING(function->name), (double)profile_nanoseconds(function->profile.exclusive_time) / 1e6);
    draw_clipped_text(font, (String){title, (size_t)title_length}, bounds.x + 12.0f, bounds.y + 2.0f, right, RAYWHITE);

    Rectangle text_bounds = {bounds.x, bounds.y + ROW_HEIGHT, bounds.width, bounds.height - ROW_HEIGHT};
    int line_height = font.baseSize;
    float bottom = bounds.y + bounds.height;
    Scrollbar *scrollbar = &source_panel->scrollbar;
    size_t lines_size = file->lines_size;
    size_t first_line = (size_t)(scrollbar->scroll_y / (float)line_height);
    float y_origin = text_bounds.y - floorf(scrollbar->scroll_y - (float)first_line * (float)line_height);

    int gutter_digits = 1;
    for (size_t n = lines_size; n >= 10; n /= 10) {
        gutter_digits++;
    }
    float gutter_width = text_panel_gutter_width(font, lines_size);
    Rectangle gutter_bounds = {bounds.x, text_bounds.y, bounds.width, text_bounds.height};

    BeginScissorMode((int)text_bounds.x, (int)text_bounds.y, (int)text_bounds.width, (int)text_bounds.height);
    for (size_t i = first_line; i < lines_size; i++) {
        float row_y = y_origin + (float)(i - first_line) * (float)line_height;
        if (row_y >= bottom) {
            break;
        }
        float source_x = text_panel_draw_gutter(font, gutter_bounds, row_y, i + 1, 0, 0, gutter_digits, gutter_width, false);
        Vector2 position = {source_x, row_y};
        draw_text(font, file->lines[i], LIGHTGRAY, &position, right);
    }
    EndScissorMode();

    draw_panel_scrollbar(text_bounds, (float)lines_size * (float)line_height, scrollbar);
}

static void profile_source_panel_handle_input(Profile_Source_Panel *source_panel, GUI *gui) {
    Profiler *profiler = gui->context;
    if (profiler->selected_source == NULL) {
        return;
    }
    float panel_height = source_panel->panel.bounds.height - ROW_HEIGHT;
    int line_height = gui->font.baseSize;
    scrollbar_wheel_input(&source_panel->scrollbar, panel_height, (float)profiler->selected_source->lines_size * (float)line_height, line_height);
}

static void profile_source_panel_handle_step(Profile_Source_Panel *source_panel, GUI *gui) {
    (void)source_panel;
    (void)gui;
}

static Panel *profile_source_panel_pick(Profile_Source_Panel *source_panel, Vector2 position) {
    (void)position;
    return &source_panel->panel;
}

static Profile_Source_Panel make_profile_source_panel(float weight) {
    return (Profile_Source_Panel){
        .panel = {
            .draw = (void (*)(Panel *, GUI *, Rectangle))profile_source_panel_draw,
            .handle_input = (void (*)(Panel *, GUI *))profile_source_panel_handle_input,
            .handle_step = (void (*)(Panel *, GUI *))profile_source_panel_handle_step,
            .pick = (Panel * (*)(Panel *, Vector2)) profile_source_panel_pick,
            .weight = weight,
        },
    };
}

typedef struct {
    const char *text;
    bool heading;
} Help_Line;

static const Help_Line help_profile_lines[] = {
    {"Reading the profile", true},
    {"", false},
    {"Self    time spent in the function's own instructions, callees excluded.", false},
    {"        All Self values add up to 100% - this is where the time really goes.", false},
    {"Total   time from call to return, callees included.", false},
    {"        $main is always 100%; a parent's Total contains its children's.", false},
    {"Calls   how many times the function was entered.", false},
    {"        Self divided by Calls is the average cost of one call.", false},
    {"", false},
};

static const Help_Line help_flamegraph_lines[] = {
    {"Flamegraph", true},
    {"", false},
    {"Width is the share of the parent's time.", false},
    {"Color is heat: dark red marks the sorted column's maximum, yellow near zero.", false},
    {"Left-click zooms into a subtree, right-click resets, middle-click opens source.", false},
};

static const Help_Line help_memory_lines[] = {
    {"Memory", true},
    {"", false},
    {"An allocation flamegraph: width is the share of the parent's allocated bytes,", false},
    {"every allocation in a subtree rolled up into its parents.", false},
    {"Color is heat: dark red marks the sorted column's maximum, yellow near zero.", false},
    {"Left-click zooms into a subtree, right-click resets, middle-click opens source.", false},
};

static const Help_Line help_functions_lines[] = {
    {"Functions", true},
    {"", false},
    {"Click a column header to sort, click it again to reverse; the sorted column", false},
    {"drives the heat colors in every view. Click a row to open its source.", false},
    {"", false},
    {"What the numbers say", true},
    {"", false},
    {"High Self               a hot worker: check its source lines.", false},
    {"High Total, low Self    a coordinator: the cost is in its callees.", false},
    {"High Calls, low Self    call overhead: fewer, fatter calls help.", false},
    {"Self equals Total       a leaf: it calls nothing (externals always are).", false},
};

static const Help_Line help_sandwich_lines[] = {
    {"Sandwich", true},
    {"", false},
    {"The selected function at full width in the middle; its merged callers stack", false},
    {"upward above it, its merged callees stack downward below.", false},
    {"Left-click re-roots the view on any frame, middle-click opens source.", false},
};

typedef struct {
    const Help_Line *lines;
    size_t size;
} Help_Section;

static void draw_help(Profiler *profiler) {
    Help_Section view;
    if (profiler->gui.root_panel == profiler->functions_panel) {
        view = (Help_Section){help_functions_lines, sizeof(help_functions_lines) / sizeof(help_functions_lines[0])};
    } else if (profiler->gui.root_panel == profiler->sandwich_panel) {
        view = (Help_Section){help_sandwich_lines, sizeof(help_sandwich_lines) / sizeof(help_sandwich_lines[0])};
    } else if (profiler->memory_mode) {
        view = (Help_Section){help_memory_lines, sizeof(help_memory_lines) / sizeof(help_memory_lines[0])};
    } else {
        view = (Help_Section){help_flamegraph_lines, sizeof(help_flamegraph_lines) / sizeof(help_flamegraph_lines[0])};
    }
    Help_Section sections[] = {
        {help_profile_lines, sizeof(help_profile_lines) / sizeof(help_profile_lines[0])},
        view,
    };
    size_t sections_size = sizeof(sections) / sizeof(sections[0]);

    Font font = profiler->gui.font;
    float line_height = (float)font.baseSize + 2.0f;
    size_t lines_size = 0;
    float text_width = 0.0f;
    for (size_t s = 0; s < sections_size; s++) {
        lines_size += sections[s].size;
        for (size_t i = 0; i < sections[s].size; i++) {
            float line_width = measure_text_width(font, string_from((char *)sections[s].lines[i].text));
            if (line_width > text_width) {
                text_width = line_width;
            }
        }
    }
    float padding = 24.0f;
    float box_width = text_width + padding * 2.0f;
    float box_height = (float)lines_size * line_height + padding * 2.0f;
    float box_x = floorf(((float)GetScreenWidth() - box_width) / 2.0f);
    float box_y = floorf(((float)GetScreenHeight() - box_height) / 2.0f);

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 160});
    DrawRectangle((int)box_x, (int)box_y, (int)box_width, (int)box_height, (Color){30, 30, 36, 255});
    DrawRectangleLines((int)box_x, (int)box_y, (int)box_width, (int)box_height, (Color){90, 90, 90, 255});
    size_t line = 0;
    for (size_t s = 0; s < sections_size; s++) {
        for (size_t i = 0; i < sections[s].size; i++, line++) {
            Vector2 position = {box_x + padding, box_y + padding + (float)line * line_height};
            draw_text(font, string_from((char *)sections[s].lines[i].text), sections[s].lines[i].heading ? RAYWHITE : LIGHTGRAY, &position, box_x + box_width);
        }
    }
}

static uint64_t accumulate_bytes(Profile_Call *node) {
    uint64_t total = node->bytes;
    for (size_t i = 0; i < node->children_size; i++) {
        total += accumulate_bytes(node->children[i]);
    }
    node->bytes = total;
    return total;
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
    uint64_t total_bytes = accumulate_bytes(root);

    IR_Function **functions = malloc(module->functions.size * sizeof(IR_Function *));
    size_t functions_size = 0;
    uint64_t max_calls = 0;
    for (size_t i = 0; i < module->functions.size; i++) {
        IR_Function *function = module->functions.items[i];
        if (function->profile.calls > 0) {
            functions[functions_size++] = function;
            if (function->profile.calls > max_calls) {
                max_calls = function->profile.calls;
            }
        }
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1000, 600, "Code IR Profiler");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    Flamegraph_Panel flamegraph_panel = make_flamegraph_panel(1.0f);
    Functions_Panel functions_panel = make_functions_panel(0.5f);
    Profile_Source_Panel source_panel = make_profile_source_panel(1.0f);
    Sandwich_Panel sandwich_panel = make_sandwich_panel(1.0f);
    Panel *functions_children[] = {&functions_panel.panel, &source_panel.panel};
    Split_Panel functions_split = make_split_panel(1.0f, SPLIT_DIRECTION__VERTICAL, functions_children, 2);
    Profiler profiler = {
        .gui = {.font = load_bitmap_font("fonts/Code.font"), .root_panel = &flamegraph_panel.panel},
        .module = module,
        .root = root,
        .total_time = root->time,
        .focus = root,
        .functions = functions,
        .functions_size = functions_size,
        .sort_column = SORT_COLUMN__TOTAL_TIME,
        .max_calls = max_calls,
        .total_bytes = total_bytes,
        .sources = ir_load_source_files(module),
        .flamegraph_panel = &flamegraph_panel.panel,
        .functions_panel = &functions_split.panel,
        .source_panel = &source_panel.panel,
        .sandwich_panel = &sandwich_panel.panel,
    };
    profiler.gui.context = &profiler;
    sort_functions(&profiler);
    if (functions_size > 0) {
        select_function(&profiler, profiler.functions[0]);
    }

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SLASH)) {
            profiler.show_help = !profiler.show_help;
        }
        if (profiler.show_help) {
            if (IsKeyPressed(KEY_ESCAPE)) {
                profiler.show_help = false;
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Rectangle buttons[BUTTON_COUNT];
                header_buttons(profiler.gui.font, (float)GetScreenWidth() - 8.0f, 8.0f, buttons);
                if (CheckCollisionPointRec(GetMousePosition(), buttons[TAB_COUNT])) {
                    profiler.show_help = false;
                }
            }
            Panel *root_panel = profiler.gui.root_panel;
            root_panel->bounds = (Rectangle){0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
            BeginDrawing();
            ClearBackground(BLACK);
            root_panel->draw(root_panel, &profiler.gui, root_panel->bounds);
            draw_help(&profiler);
            EndDrawing();
            continue;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Rectangle buttons[BUTTON_COUNT];
            header_buttons(profiler.gui.font, (float)GetScreenWidth() - 8.0f, 8.0f, buttons);
            Vector2 mouse = GetMousePosition();
            for (size_t i = 0; i < BUTTON_COUNT; i++) {
                if (CheckCollisionPointRec(mouse, buttons[i])) {
                    if (i < TAB_COUNT) {
                        profiler.gui.root_panel = tab_panel(&profiler, i);
                        if (i <= 1 && profiler.memory_mode != (i == 1)) {
                            profiler.memory_mode = i == 1;
                            flamegraph_panel.scrollbar.scroll_y = 0;
                        }
                        profiler.hovered = NULL;
                    } else {
                        profiler.show_help = true;
                    }
                }
            }
        }
        gui_render_frame(&profiler.gui);
    }

    if (profiler.sandwich_callees != NULL) {
        free_calls(profiler.sandwich_callees);
        free_calls(profiler.sandwich_callers);
    }
    free(functions);
    UnloadFont(profiler.gui.font);
    CloseWindow();
}

static void save_call_tree(FILE *file, Profile_Call *node, int depth) {
    fprintf(file, "%14" PRIu64 " %12" PRIu64 " %12" PRIu64 "  %*s%.*s\n", profile_nanoseconds(node->time), node->calls, node->bytes, depth * 2, "", STRING(node->function->name));
    for (size_t i = 0; i < node->children_size; i++) {
        save_call_tree(file, node->children[i], depth + 1);
    }
}

void profile_save(IR_Module *module, const char *path) {
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
    uint64_t total_bytes = accumulate_bytes(root);

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        fprintf(stderr, "Runner: cannot write profile to %s\n", path);
        return;
    }

    fprintf(file, "total: %" PRIu64 " ns\n", profile_nanoseconds(root->time));
    fprintf(file, "allocated: %" PRIu64 " bytes\n", total_bytes);

    IR_Function **functions = malloc(module->functions.size * sizeof(IR_Function *));
    size_t functions_size = 0;
    for (size_t i = 0; i < module->functions.size; i++) {
        IR_Function *function = module->functions.items[i];
        if (function->profile.calls > 0) {
            functions[functions_size++] = function;
        }
    }
    qsort(functions, functions_size, sizeof(IR_Function *), compare_by_self_time);

    fprintf(file, "\nfunctions:\n");
    fprintf(file, "     self (ns)   total (ns)        calls  function\n");
    for (size_t i = 0; i < functions_size; i++) {
        IR_Function *function = functions[i];
        fprintf(file, "%14" PRIu64 " %12" PRIu64 " %12" PRIu64 "  %.*s\n", profile_nanoseconds(function->profile.exclusive_time), profile_nanoseconds(function->profile.inclusive_time), function->profile.calls, STRING(function->name));
    }
    free(functions);

    fprintf(file, "\ncalls:\n");
    fprintf(file, "     time (ns)        calls        bytes  function\n");
    save_call_tree(file, root, 0);

    fclose(file);
}
