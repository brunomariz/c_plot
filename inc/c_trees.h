#ifndef _C_TREESH_
#define _C_TREESH_

#include "../inc/type_utils.h"

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

void draw_circumference(SDL_Renderer *renderer, int x, int y, int r, RGBA color, int thick_border);
void draw_circumference_polar(SDL_Renderer *renderer, float theta, int r, int R, RGBA color);
void draw_line_polar(SDL_Renderer *renderer, float theta_orig, int r_orig, float theta_dest, int r_dest, RGBA color);
void draw_node_polar(SDL_Renderer *renderer, float theta, int r);
PolarCoord draw_tree_level_based_polar(SDL_Renderer *renderer, Tree tree, int start,
                                       int vertical_level,
                                       float section_low, float section_high);

#endif
