#include "../inc/c_plot.h"

void c_plot_internal_circumference_draw(SDL_Renderer *renderer, int x, int y, int r)
{
    int point_x, point_y;
    for (float theta = 0.0; theta < 2 * 3.1415; theta += 1 / (float)r)
    {
        point_x = x + (cos(theta) * r);
        point_y = y + (sin(theta) * r);
        // Draw points
        SDL_RenderDrawPoint(renderer, point_x, point_y);
    }
}

void c_plot_internal_grid_draw_polar(SDL_Renderer *renderer, CP_Axis *axis)
{
    for (int i = axis->d2_scale; i < (CP_WINDOW_WIDTH > CP_WINDOW_HEIGHT ? CP_WINDOW_WIDTH : CP_WINDOW_HEIGHT); i += axis->d2_scale)
    {
        // Draw grid circles
        c_plot_internal_circumference_draw(renderer, axis->origin_position->x, axis->origin_position->y, i);
    }

    for (float theta = 0; theta < 2 * 3.14159265358979323846; theta += 3.14159265358979323846 / axis->d1_scale)
    {
        CP_PolarCoord destination_coord = {theta, (CP_WINDOW_HEIGHT > CP_WINDOW_WIDTH ? CP_WINDOW_HEIGHT : CP_WINDOW_WIDTH)};
        CP_CartesianCoord destination_coord_cartesian = c_plot_coordinate_polar_to_cartesian(&destination_coord, axis);
        // Draw grid lines
        SDL_RenderDrawLine(renderer, axis->origin_position->x, axis->origin_position->y, destination_coord_cartesian.x, destination_coord_cartesian.y);
    }
}

void c_plot_internal_grid_draw_cartesian(SDL_Renderer *renderer, CP_Axis *axis)
{
    for (int i = axis->origin_position->x; i < CP_WINDOW_WIDTH; i += axis->d1_scale)
    {
        // Draw vertical grid line to the right of the origin
        SDL_RenderDrawLine(renderer, i, 0, i, CP_WINDOW_HEIGHT);
        // Draw vertical grid line to the left of the origin
        SDL_RenderDrawLine(renderer, 2 * axis->origin_position->x - i, 0, 2 * axis->origin_position->x - i, CP_WINDOW_HEIGHT);
    }
    for (int i = axis->origin_position->y; i < CP_WINDOW_HEIGHT; i += axis->d2_scale)
    {
        // Draw vertical grid line above the origin
        SDL_RenderDrawLine(renderer, 0, i, CP_WINDOW_WIDTH, i);
        // Draw vertical grid line below origin
        SDL_RenderDrawLine(renderer, 0, 2 * axis->origin_position->y - i, CP_WINDOW_WIDTH, 2 * axis->origin_position->y - i);
    }
}

void c_plot_draw_grid(SDL_Renderer *renderer, CP_Axis *axis)
{
    if (axis->type == CP_AXIS_TYPE_POLAR)
    {
        c_plot_internal_grid_draw_polar(renderer, axis);
    }
    else if (axis->type == CP_AXIS_TYPE_CARTESIAN)
    {
        c_plot_internal_grid_draw_cartesian(renderer, axis);
    }
}
