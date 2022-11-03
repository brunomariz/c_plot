#ifndef _C_TREESH_
#define _C_TREESH_

#include <SDL2/SDL.h>

#define CT_WINDOW_WIDTH (640)
#define CT_WINDOW_HEIGHT (480)

// ===Types===
typedef struct
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} CT_RGBA;

typedef struct
{
    int id;
} CT_State;

typedef struct
{
    CT_State *states;
    int *adjacency_list;
    int num_states;
    int num_connections;
} CT_AdjListTree;

typedef struct
{
    float theta;
    int r;
} CT_PolarCoord;

// ===Drawing===
void c_trees_draw_circumference(SDL_Renderer *renderer, int x, int y, int r, CT_RGBA color, int thick_border);
void c_trees_draw_circumference_polar(SDL_Renderer *renderer, float theta, int r, int R, CT_RGBA color);
void c_trees_draw_line_polar(SDL_Renderer *renderer, float theta_orig, int r_orig, float theta_dest, int r_dest, CT_RGBA color);
void c_trees_draw_node_polar(SDL_Renderer *renderer, float theta, int r);
CT_PolarCoord c_trees_draw_tree_level_based_polar_adj_list(SDL_Renderer *renderer, CT_AdjListTree tree, int start,
                                                           int vertical_level,
                                                           float section_low, float section_high);
CT_PolarCoord c_trees_draw_tree_level_based_polar_nested_obj(SDL_Renderer *renderer, CT_AdjListTree tree, int start,
                                                             int vertical_level,
                                                             float section_low, float section_high);

#endif
