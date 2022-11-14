#include "../inc/c_plot.h"

CP_CartesianCoord c_plot_coordinate_polar_to_cartesian(CP_PolarCoord *polar_coord, CP_CartesianCoord *origin_position)
{
    int x = (int)(cos(polar_coord->theta) * polar_coord->r) + origin_position->x;
    int y = -(int)(sin(polar_coord->theta) * polar_coord->r) + origin_position->y;
    CP_CartesianCoord cartesian_coord = {x, y};
    return cartesian_coord;
}