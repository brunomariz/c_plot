#include "../inc/c_plot.h"

CP_Axis *c_plot_axis_create(CP_AxisType type, float d1_scale, float d2_scale, CP_CartesianCoord *origin_position, int min_spacing_x, int min_spacing_y, int max_spacing_x, int max_spacing_y)
{
    CP_Axis *axis = malloc(sizeof *axis);
    axis->type = type;
    axis->d1_scale = d1_scale;
    axis->d2_scale = d2_scale;
    axis->origin_position = origin_position;
    axis->min_spacing_x = min_spacing_x;
    axis->min_spacing_y = min_spacing_y;
    axis->max_spacing_x = max_spacing_x;
    axis->max_spacing_y = max_spacing_y;
    return axis;
}

void c_plot_internal_draw_ticks_cartesian(SDL_Renderer *renderer, CP_Axis *axis)
{
    const int tick_height = 8;
    const int tick_width = 5;
    SDL_Rect *tick_rect = malloc(sizeof *tick_rect);
    // Draw x ticks
    // calculate spacing so that the ticks dont bunch up
    int spacing_x_ticks = c_plot_util_calculate_spacing(axis->min_spacing_x, axis->max_spacing_x, axis->d1_scale);
    for (int i = axis->origin_position->x; (i < CP_WINDOW_WIDTH) || (2 * abs(axis->origin_position->x) - i > 0); i += spacing_x_ticks)
    {
        // Draw tick to the right of the origin
        CP_CartesianCoord tick_position = {i, axis->origin_position->y};
        tick_rect->h = tick_height;
        tick_rect->w = tick_width;
        tick_rect->x = tick_position.x - tick_width / 2;
        tick_rect->y = tick_position.y - tick_height / 2;
        SDL_RenderFillRect(renderer, tick_rect);
        // Draw tick to the left of the origin
        tick_rect->h = tick_height;
        tick_rect->w = tick_width;
        tick_rect->x = 2 * abs(axis->origin_position->x) - tick_position.x - tick_width / 2;
        tick_rect->y = tick_position.y - tick_height / 2;
        SDL_RenderFillRect(renderer, tick_rect);
    }
    // Draw y ticks
    // calculate spacing so that the ticks dont bunch up
    int spacing_y_ticks = c_plot_util_calculate_spacing(axis->min_spacing_y, axis->max_spacing_y, axis->d2_scale);
    for (int i = axis->origin_position->y; (i < CP_WINDOW_WIDTH) || (2 * axis->origin_position->y - i > 0); i += spacing_y_ticks)
    {
        // Draw tick below origin
        CP_CartesianCoord tick_position = {axis->origin_position->x, i};
        tick_rect->h = tick_width;
        tick_rect->w = tick_height;
        tick_rect->x = tick_position.x - tick_height / 2;
        tick_rect->y = tick_position.y - tick_width / 2;
        SDL_RenderFillRect(renderer, tick_rect);
        // Draw tick above origin
        tick_rect->h = tick_width;
        tick_rect->w = tick_height;
        tick_rect->x = tick_position.x - tick_height / 2;
        tick_rect->y = 2 * axis->origin_position->y - tick_position.y - tick_width / 2;
        SDL_RenderFillRect(renderer, tick_rect);
    }
}

void c_plot_internal_draw_ticks_polar(SDL_Renderer *renderer, CP_Axis *axis)
{
    const int tick_height = 8;
    const int tick_width = 3;

    SDL_Rect *tick_rect = malloc(sizeof *tick_rect);
    int deviation_x_axis = CP_WINDOW_WIDTH / 2 - axis->origin_position->x;
    int slack = 2;
    int limit_tick_r = CP_WINDOW_WIDTH / axis->d2_scale * slack + deviation_x_axis;
    for (int r = 0; r < limit_tick_r; r++)
    {
        CP_PolarCoord position = {0, r};
        CP_CartesianCoord position_cartesian = c_plot_coordinate_polar_to_cartesian(&position, axis);
        tick_rect->h = tick_height;
        tick_rect->w = tick_width;
        tick_rect->x = position_cartesian.x - tick_width / 2;
        tick_rect->y = position_cartesian.y - tick_height / 2;
        SDL_RenderFillRect(renderer, tick_rect);
    }
}

void c_plot_internal_draw_axis_polar(SDL_Renderer *renderer, CP_Axis *axis)
{
    // Draw r axis
    SDL_RenderDrawLine(renderer, axis->origin_position->x, axis->origin_position->y, CP_WINDOW_WIDTH, axis->origin_position->y);

    // Draw ticks
    c_plot_internal_draw_ticks_polar(renderer, axis);
}

void c_plot_internal_draw_axis_cartesian(SDL_Renderer *renderer, CP_Axis *axis)
{
    // Draw x axis
    SDL_RenderDrawLine(renderer, 0, axis->origin_position->y, CP_WINDOW_WIDTH, axis->origin_position->y);
    // Draw y axis
    SDL_RenderDrawLine(renderer, axis->origin_position->x, 0, axis->origin_position->x, CP_WINDOW_HEIGHT);
    // Draw ticks
    c_plot_internal_draw_ticks_cartesian(renderer, axis);
}

void c_plot_axis_draw(SDL_Renderer *renderer, CP_Axis *axis)
{
    if (axis->type == CP_AXIS_TYPE_POLAR)
    {
        c_plot_internal_draw_axis_polar(renderer, axis);
    }
    else if (axis->type == CP_AXIS_TYPE_CARTESIAN)
    {
        c_plot_internal_draw_axis_cartesian(renderer, axis);
    }
}