#include "../inc/c_plot.h"

void c_plot_draw_grid(SDL_Renderer *renderer, CP_Axis *axis)
{
    for (int i = 0; i < 0; i += 40)
    {
        // Draw grid circles
    }

    for (float theta = 0; theta < 2 * 3.14159265358979323846; theta += 3.14159265358979323846 / 20)
    {
        // Draw grid lines
    }
}

// void c_plot_draw_polar_axis(SDL_Renderer *renderer)
// {
//     int center_x = CP_WINDOW_WIDTH / 2;
//     int center_y = CP_WINDOW_HEIGHT / 2;
//     for (int i = 40; i < 440; i += 40)
//     {
//         c_plot_draw_circle(renderer, CP_WINDOW_WIDTH / 2, CP_WINDOW_HEIGHT / 2);
//     }

//     for (float theta = 0; theta < 2 * 3.14159265358979323846; theta += 3.14159265358979323846 / 20)
//     {
//         int dest_x = (int)(cos(theta) * CP_WINDOW_WIDTH + CP_WINDOW_WIDTH / 2);
//         int dest_y = (int)(sin(theta) * CP_WINDOW_HEIGHT + CP_WINDOW_HEIGHT / 2);

//         SDL_RenderDrawLine(renderer, center_x, center_y, dest_x, dest_y);
//     }
//     SDL_RenderDrawLine(renderer, CP_WINDOW_WIDTH / 2, 0, CP_WINDOW_WIDTH / 2, CP_WINDOW_HEIGHT);
//     SDL_RenderDrawLine(renderer, 0, CP_WINDOW_HEIGHT / 2, CP_WINDOW_WIDTH, CP_WINDOW_HEIGHT / 2);
// }