#ifndef _C_TREESH_
#define _C_TREESH_

#include "../c_structures/inc/c_structures.h"

#include <SDL2/SDL.h>

#define CP_WINDOW_WIDTH (640)
#define CP_WINDOW_HEIGHT (640)

// === Types ===
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

typedef struct
{
    CS_SList *connection_positions;
    CS_SList *node_positions;
} CP_TreePositionInfoPolar;

// == Coordinates ===
CP_CartesianCoord c_plot_coordinate_polar_to_cartesian(CP_PolarCoord *polar_coord, CP_Axis *axis);

// === Drawing ===
void c_plot_draw_circle(SDL_Renderer *renderer, int x, int y);
void c_plot_draw_tree(SDL_Renderer *renderer, CP_Axis *axis, CS_SList *node_positions, CS_SList *connection_positions);
void c_plot_draw_grid(SDL_Renderer *renderer, CP_Axis *axis);

// === Nested Object Tree ===
CP_TreePositionInfoPolar *c_plot_tree_get_positions_level_based_polar(CS_TreeNode *root_node);

// === Displaying ===
void c_plot_tree_show(CS_TreeNode *root_node);

// === Axis ===
CP_Axis *c_plot_axis_create(CP_AxisType type, float d1_scale, float d2_scale, CP_CartesianCoord *origin_position);
void c_plot_draw_axis(SDL_Renderer *renderer, CP_Axis *axis);

#endif
