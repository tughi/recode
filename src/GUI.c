#include "GUI.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

bool draw_text(Font font, String text, Color color, Vector2 *position, float max_right) {
    position->x = roundf(position->x);
    position->y = roundf(position->y);
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

float measure_text_width(Font font, String text) {
    float total = 0.0f;
    for (size_t i = 0; i < text.length; i++) {
        total += (float)font.glyphs[GetGlyphIndex(font, (unsigned char)text.content[i])].advanceX;
    }
    return total;
}

void draw_text_right_aligned(Font font, String text, float right, float y, Color color) {
    Vector2 position = {right - measure_text_width(font, text), y};
    draw_text(font, text, color, &position, right);
}

void draw_panel_scrollbar(Rectangle bounds, float content_height, Scrollbar *scrollbar) {
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

void scrollbar_wheel_input(Scrollbar *scrollbar, float panel_height, float content_height, int line_height) {
    float max_scroll = content_height > panel_height ? content_height - panel_height : 0;
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        scrollbar->scroll_y -= wheel * line_height * 3;
    }
    if (scrollbar->scroll_y > max_scroll) {
        scrollbar->scroll_y = max_scroll;
    }
    if (scrollbar->scroll_y < 0) {
        scrollbar->scroll_y = 0;
    }
}

#define SCROLL_MARGIN_LINES 5

void text_panel_scroll_to_line(Scrollbar *scrollbar, float panel_height, size_t line, size_t lines_size, int line_height) {
    if (line == 0) {
        return;
    }
    float margin = (float)(SCROLL_MARGIN_LINES * line_height);
    if (margin > (panel_height - line_height) / 2) {
        margin = (panel_height - line_height) / 2;
        if (margin < 0) {
            margin = 0;
        }
    }
    float line_y = (float)(line - 1) * line_height;
    if (line_y - margin < scrollbar->scroll_y) {
        scrollbar->scroll_y = line_y - margin;
        if (scrollbar->scroll_y < 0) {
            scrollbar->scroll_y = 0;
        }
    } else if (line_y + line_height + margin > scrollbar->scroll_y + panel_height) {
        scrollbar->scroll_y = line_y + line_height + margin - panel_height;
        float max_scroll = (float)lines_size * line_height - panel_height;
        if (max_scroll < 0) {
            max_scroll = 0;
        }
        if (scrollbar->scroll_y > max_scroll) {
            scrollbar->scroll_y = max_scroll;
        }
    }
}

float text_panel_gutter_width(Font font, size_t lines_size) {
    int gutter_digits = 1;
    for (size_t n = lines_size; n >= 10; n /= 10) {
        gutter_digits++;
    }
    int digit_advance = font.glyphs[GetGlyphIndex(font, '0')].advanceX;
    return (float)(gutter_digits * digit_advance) + digit_advance;
}

size_t text_panel_scroll_input(Font font, Panel *panel, Scrollbar *scrollbar, size_t lines_size) {
    int line_height = font.baseSize;
    float panel_height = panel->bounds.height;
    float content_height = (float)lines_size * line_height;

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
        scrollbar->scroll_y = content_height;
    }
    scrollbar_wheel_input(scrollbar, panel_height, content_height, line_height);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse = GetMousePosition();
        Rectangle bounds = panel->bounds;
        float gutter_width = text_panel_gutter_width(font, lines_size);
        if (mouse.x >= bounds.x && mouse.x < bounds.x + gutter_width && mouse.y >= bounds.y && mouse.y < bounds.y + bounds.height) {
            return (size_t)((mouse.y - bounds.y + scrollbar->scroll_y) / line_height) + 1;
        }
    }
    return 0;
}

float text_panel_draw_gutter(Font font, Rectangle bounds, float row_y, size_t line, size_t current_line, size_t view_line, int gutter_digits, float gutter_width, bool has_breakpoint) {
    int line_height = font.baseSize;
    if (line == current_line) {
        DrawRectangle((int)bounds.x, (int)row_y, (int)bounds.width, line_height, DARKBLUE);
    } else if (line == view_line) {
        DrawRectangle((int)bounds.x, (int)row_y, (int)bounds.width, line_height, DARKPURPLE);
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
    Color number_color = line == current_line || line == view_line ? GRAY : DARKGRAY;
    Color dim_color = {number_color.r, number_color.g, number_color.b, number_color.a / 2};
    Vector2 number_position = {roundf(bounds.x), roundf(row_y)};
    for (int j = 0; number_text[j] != '\0'; j++) {
        int codepoint = number_text[j];
        Color color = (size_t)j < leading ? dim_color : number_color;
        DrawTextCodepoint(font, codepoint, number_position, font.baseSize, color);
        number_position.x += digit_advance;
    }
    return bounds.x + gutter_width;
}

#define GUTTER_SIZE 4

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
        return (Rectangle){floorf(x), bounds.y, floorf(remaining * split->children[index]->weight), bounds.height};
    } else {
        float available = bounds.height - gutters_total;
        float remaining = available;
        float y = bounds.y;
        for (size_t i = 0; i < index; i++) {
            float height = remaining * split->children[i]->weight;
            y += height + GUTTER_SIZE;
            remaining -= height;
        }
        return (Rectangle){bounds.x, floorf(y), bounds.width, floorf(remaining * split->children[index]->weight)};
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

static void split_panel_draw(Split_Panel *split, GUI *gui, Rectangle bounds) {
    for (size_t i = 0; i < split->children_size; i++) {
        Panel *child = split->children[i];
        Rectangle child_bounds = split_panel_child_bounds(split, i, bounds);
        child->bounds = child_bounds;
        child->draw(child, gui, child_bounds);
    }
    bool dragging = gui->active_panel == &split->panel && IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    for (size_t i = 0; i + 1 < split->children_size; i++) {
        Rectangle gutter = split_panel_gutter_bounds(split, i, bounds);
        Color color = dragging && i == split->dragged_gutter ? GRAY : DARKGRAY;
        DrawRectangleRec(gutter, color);
    }
}

static void split_panel_handle_step(Split_Panel *split, GUI *gui) {
    for (size_t i = 0; i < split->children_size; i++) {
        Panel *child = split->children[i];
        child->bounds = split_panel_child_bounds(split, i, split->panel.bounds);
        child->handle_step(child, gui);
    }
}

static void split_panel_handle_input(Split_Panel *split, GUI *gui) {
    (void)gui;
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

Split_Panel make_split_panel(float weight, Split_Direction direction, Panel **children, size_t children_size) {
    return (Split_Panel){
        .panel = {
            .draw = (void (*)(Panel *, GUI *, Rectangle))split_panel_draw,
            .handle_input = (void (*)(Panel *, GUI *))split_panel_handle_input,
            .handle_step = (void (*)(Panel *, GUI *))split_panel_handle_step,
            .pick = (Panel * (*)(Panel *, Vector2)) split_panel_pick,
            .weight = weight,
        },
        .direction = direction,
        .children = children,
        .children_size = children_size,
    };
}

void gui_render_frame(GUI *gui) {
    gui->root_panel->bounds = (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()};

    if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        gui->active_panel = gui->root_panel->pick(gui->root_panel, GetMousePosition());
    }
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    gui->active_panel->handle_input(gui->active_panel, gui);

    BeginDrawing();
    ClearBackground(BLACK);
    gui->root_panel->draw(gui->root_panel, gui, gui->root_panel->bounds);
    EndDrawing();
}
