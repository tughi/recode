#pragma once

#include "String.h"
#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct GUI GUI;
typedef struct Panel Panel;

struct Panel {
    void (*draw)(Panel *self, GUI *gui, Rectangle bounds);
    void (*handle_input)(Panel *self, GUI *gui);
    void (*handle_step)(Panel *self, GUI *gui);
    Panel *(*pick)(Panel *self, Vector2 position);
    Rectangle bounds;
    float weight;
};

struct GUI {
    Font font;
    Panel *root_panel;
    Panel *active_panel;
    void *context;
};

Font load_bitmap_font(const char *path);
bool draw_text(Font font, String text, Color color, Vector2 *position, float max_right);
float measure_text_width(Font font, String text);
void draw_text_right_aligned(Font font, String text, float right, float y, Color color);

typedef struct {
    float scroll_y;
    bool dragging;
    float drag_offset;
    float opacity;
} Scrollbar;

void draw_panel_scrollbar(Rectangle bounds, float content_height, Scrollbar *scrollbar);
void scrollbar_wheel_input(Scrollbar *scrollbar, float panel_height, float content_height, int line_height);
void text_panel_scroll_to_line(Scrollbar *scrollbar, float panel_height, size_t line, size_t lines_size, int line_height);

float text_panel_gutter_width(Font font, size_t lines_size);
size_t text_panel_scroll_input(Font font, Panel *panel, Scrollbar *scrollbar, size_t lines_size);
float text_panel_draw_gutter(Font font, Rectangle bounds, float row_y, size_t line, size_t current_line, size_t view_line, int gutter_digits, float gutter_width, bool has_breakpoint);

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

Split_Panel make_split_panel(float weight, Split_Direction direction, Panel **children, size_t children_size);

void gui_render_frame(GUI *gui);
