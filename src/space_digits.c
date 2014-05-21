#include <pebble.h>

#include "math.h"
#include "data.h"

#define NUM_DIGITS 8
#define TRANSFORM_MAT(NUM) transform_##NUM

//==============================================================================

typedef struct Poly {
  Vec3* vertices;
  int   vert_num;
  int*  indexes;
  int   idx_num;
} Poly;

typedef struct PolyLayerData {
  Poly* poly;
  int   pos;
} PolyLayerData;

//==============================================================================

static Window *window;

static Poly digit_polys[10];
static Layer *digit_layers[NUM_DIGITS];
static Mat4 tranform_matrices[NUM_DIGITS];

static char *old_time = "--------";

//==============================================================================

static void poly_init(Poly* poly) {
  poly->idx_num  = 0;
  poly->vert_num = 0;
}

static void make_digit_poly(int num) {
  poly_init(&digit_polys[num]);
  digit_polys[num].vertices = vertices;
  digit_polys[num].vert_num = 9;
  digit_polys[num].indexes  = indexes[num];
  digit_polys[num].idx_num  = index_lengths[num];
}

//==============================================================================

static void poly_layer_update_proc(Layer *layer, GContext* ctx) {
  PolyLayerData *data = layer_get_data(layer);
  Poly* poly = data->poly;
  int pos = data->pos;
  int i;

  if (NULL == poly) {
    return;
  }

  static GPoint screen_pos[32];

  // Update frame
  GRect frame = layer_get_frame(layer);
  frame.origin.x = 0;
  frame.origin.y = 0;
  layer_set_frame(layer, frame);

  // Get poly's vertex pos in frame coordinate
  Vec3 view_pos;
  for (i = 0; i < poly->vert_num; ++i) {
    mat4_multiply_vec3(&view_pos, &tranform_matrices[pos], &poly->vertices[i]);
    vec3_project(&screen_pos[i], &view_pos);
  }

  // Draw line according to vertex idx
  int prev_vertex_idx = -1;
  int vertex_idx = -1;
  GPoint from, to;

  graphics_context_set_stroke_color(ctx, GColorWhite);

  for (i = 0; i < poly->idx_num; ++i) {
    vertex_idx = poly->indexes[i];

    if (prev_vertex_idx != -1) {
      if (vertex_idx == prev_vertex_idx) {
        prev_vertex_idx = -1;
      } else {
        from = screen_pos[prev_vertex_idx];
        to   = screen_pos[vertex_idx];

        graphics_draw_line(ctx, from, to);
        graphics_draw_line(ctx, GPoint(from.x + 1, from.y), GPoint(to.x + 1, to.y));
        graphics_draw_line(ctx, GPoint(from.x, from.y + 1), GPoint(to.x, to.y + 1));

        prev_vertex_idx = vertex_idx;
      }
    } else {
      prev_vertex_idx = vertex_idx;
    }
  }
}

static Layer* poly_layer_create(int pos) {
  Layer *layer;
  PolyLayerData *data;

  layer = layer_create_with_data(GRect(0, 0, 144, 168), sizeof(PolyLayerData));
  data  = layer_get_data(layer);
  data->poly = NULL;
  data->pos  = pos;

  layer_set_update_proc(layer, poly_layer_update_proc);
  
  return layer;
}

static void poly_layer_set_poly_ref(Layer *layer, Poly* poly) {
  ((PolyLayerData*)layer_get_data(layer))->poly = poly;
  layer_mark_dirty(layer);
}

//==============================================================================

static void format_time(struct tm *tick_time, char *time_str, int str_len) {
  char *time_format = "00000000";

  if (clock_is_24h_style()) {
    time_format = "%H%M%m%d";
  } else {
    time_format = "%I%M%m%d";
  }

  strftime(time_str, str_len, time_format, tick_time);
}

static void handle_minute_tick(struct tm* tick_time, TimeUnits units_changed) {
  char *time_str = "00000000";
  format_time(tick_time, time_str, NUM_DIGITS + 1);

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Time changed: %s -> %s", old_time, time_str);

  int i;
  for (i = 0; i < NUM_DIGITS; i++) {
    if (old_time[i] != time_str[i]) {
      poly_layer_set_poly_ref(digit_layers[i], &digit_polys[time_str[i] - 48]);
    }
  }

  strncpy(old_time, time_str, NUM_DIGITS);
}

static void init(void) {
  int i;

  window = window_create();
  window_set_background_color(window, GColorBlack);
  window_stack_push(window, true);

  Layer *root_layer = window_get_root_layer(window);

  tranform_matrices[0] = TRANSFORM_MAT(0);
  tranform_matrices[1] = TRANSFORM_MAT(1);
  tranform_matrices[2] = TRANSFORM_MAT(2);
  tranform_matrices[3] = TRANSFORM_MAT(3);
  tranform_matrices[4] = TRANSFORM_MAT(4);
  tranform_matrices[5] = TRANSFORM_MAT(5);
  tranform_matrices[6] = TRANSFORM_MAT(6);
  tranform_matrices[7] = TRANSFORM_MAT(7);

  for (i = 0; i < 10; i++) {
    make_digit_poly(i);
  }

  for (i = 0; i < NUM_DIGITS; i++) {
    digit_layers[i] = poly_layer_create(i);
    layer_add_child(root_layer, digit_layers[i]);
  }

  tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);
}

static void deinit(void) {
  window_destroy(window);

  for (int i = 0; i < NUM_DIGITS; i++) {
    layer_destroy(digit_layers[i]);
  }
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
