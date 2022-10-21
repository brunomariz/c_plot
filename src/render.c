#include "../inc/render.h"

#include "../inc/c_trees.h"

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

void render_circles(SDL_Renderer *renderer)
{
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    // SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    draw_circumference(renderer, 50, 50, 100, (RGBA){255, 255, 255, 255});
    draw_circumference(renderer, 200, 200, 50, (RGBA){255, 255, 255, 255});
    draw_circumference(renderer, 300, 400, 20, (RGBA){255, 255, 255, 255});
    draw_circumference(renderer, 400, 50, 10, (RGBA){255, 255, 255, 255});
    draw_circumference(renderer, 500, 10, 20, (RGBA){255, 255, 255, 255});
}

void render_polar_axis(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    int center_x = WINDOW_WIDTH / 2;
    int center_y = WINDOW_HEIGHT / 2;
    for (int i = 40; i < 440; i += 40)
    {
        draw_circumference(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, i, (RGBA){255, 255, 255, 255});
    }

    for (float theta = 0; theta < 2 * 3.14159265358979323846; theta += 3.14159265358979323846 / 20)
    {
        int dest_x = (int)(cos(theta) * WINDOW_WIDTH + WINDOW_WIDTH / 2);
        int dest_y = (int)(sin(theta) * WINDOW_HEIGHT + WINDOW_HEIGHT / 2);

        SDL_RenderDrawLine(renderer, center_x, center_y, dest_x, dest_y);
    }
    SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
    SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);
}

void render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    RGBA white = {255, 255, 255, 255};
    RGBA red = {255, 0, 0, 255};

    render_polar_axis(renderer);

    draw_circumference_polar(renderer, 3.141592 / 20, 120, white);

    // Render random circles
    // for (float theta = 0; theta < 2 * 3.1415; theta += 0.3)
    // {
    //     for (int r = 40; r < 440; r += 40)
    //     {
    //         if (rand() % 3 == 0)
    //         {
    //             int dest_x = (int)(cos(theta) * r);
    //             int dest_y = (int)(sin(theta) * r);
    //             draw_circumference(renderer, dest_x + WINDOW_WIDTH / 2, dest_y + WINDOW_HEIGHT / 2, 15, (RGBA){255, 0, 0, 255});
    //         }
    //     }
    // }
}