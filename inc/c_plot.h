#ifndef _C_TREESH_
#define _C_TREESH_

#include "../c_structures/inc/c_structures.h"

#include <SDL2/SDL.h>

#define CT_WINDOW_WIDTH (640)
#define CT_WINDOW_HEIGHT (480)

// === Util Types ===
typedef struct
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} CT_RGBA;

typedef struct
{
    float theta;
    int r;
} CT_PolarCoord;

// ===Drawing===
void c_plot_draw_circumference(SDL_Renderer *renderer, int x, int y, int r, CT_RGBA color, int thick_border);
void c_plot_draw_circumference_polar(SDL_Renderer *renderer, float theta, int r, int R, CT_RGBA color);
void c_plot_draw_line_polar(SDL_Renderer *renderer, float theta_orig, int r_orig, float theta_dest, int r_dest, CT_RGBA color);
void c_plot_draw_node_polar(SDL_Renderer *renderer, float theta, int r);

// === Adjacency List Tree
typedef struct
{
    int *adjacency_list;
    int num_connections;
} CT_AdjListTree;

CT_PolarCoord c_plot_draw_tree_level_based_polar_adj_list(SDL_Renderer *renderer, CT_AdjListTree tree, int start,
                                                          int vertical_level,
                                                          float section_low, float section_high);

// === Nested Object Tree
CT_PolarCoord c_plot_draw_tree_level_based_polar_nested_obj(SDL_Renderer *renderer, CS_TreeNode *root_node,
                                                            int vertical_level,
                                                            float section_low, float section_high);

// === Rendering ===
void c_plot_tree_show(CS_TreeNode *root_node);

#endif
