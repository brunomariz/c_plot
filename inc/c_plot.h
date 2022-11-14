#ifndef _C_TREESH_
#define _C_TREESH_

#include "../c_structures/inc/c_structures.h"

#include <SDL2/SDL.h>

#define CP_WINDOW_WIDTH (640)
#define CP_WINDOW_HEIGHT (640)

// === Util Types ===
typedef struct
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} CP_RGBA;

typedef struct
{
    float theta;
    int r;
} CP_PolarCoord;

typedef struct
{
    int x;
    int y;
} CP_CartesianCoord;

CP_CartesianCoord c_plot_coordinate_polar_to_cartesian(CP_PolarCoord *polar_coord, CP_CartesianCoord *origin_position);

// ===Drawing===
void c_plot_draw_circumference(SDL_Renderer *renderer, int x, int y, int r, CP_RGBA color, int thick_border);
void c_plot_draw_circumference_polar(SDL_Renderer *renderer, float theta, int r, int R, CP_RGBA color);
void c_plot_draw_line_polar(SDL_Renderer *renderer, float theta_orig, int r_orig, float theta_dest, int r_dest, CP_RGBA color);
void c_plot_draw_node_polar(SDL_Renderer *renderer, float theta, int r);
void c_plot_draw_polar_axis(SDL_Renderer *renderer);
void c_plot_draw_tree(SDL_Renderer *renderer, CS_SList *node_positions, CS_SList *connection_positions);

// === Adjacency List Tree
typedef struct
{
    int *adjacency_list;
    int num_connections;
} CP_AdjListTree;

// Deprecated
CP_PolarCoord c_plot_adj_list_tree_draw_level_based_polar(SDL_Renderer *renderer, CP_AdjListTree tree, int start,
                                                          int vertical_level,
                                                          float section_low, float section_high);

// === Nested Object Tree
typedef struct
{
    CS_SList *connection_positions;
    CS_SList *node_positions;
} CP_TreePositionInfoPolar;

// Deprecated
CP_PolarCoord c_plot_nested_obj_tree_draw_level_based_polar(
    SDL_Renderer *renderer,
    CS_TreeNode *root_node,
    int vertical_level,
    float section_low, float section_high);

CP_TreePositionInfoPolar *c_plot_tree_get_positions_level_based_polar(CS_TreeNode *root_node);

// === Rendering ===
void c_plot_tree_show(CS_TreeNode *root_node);

// === Axis ===

typedef enum
{
    CP_AXIS_TYPE_POLAR,
    CP_AXIS_TYPE_CARTESIAN
} CP_AxisType;

typedef struct
{
    CP_AxisType type;
    float d1_scale; // dimension 1 scale (ex: x scale, theta scale)
    float d2_scale; // dimension 2 scale (ex: y scale, r scale)
    CP_CartesianCoord *origin_position;
} CP_Axis;

CP_Axis *c_plot_axis_create(CP_AxisType type, float d1_scale, float d2_scale, CP_CartesianCoord *origin_position);
void c_plot_draw_axis(SDL_Renderer *renderer, CP_Axis *axis);

#endif
