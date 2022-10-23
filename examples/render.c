#include "render.h"

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

RGBA white = {255, 255, 255, 255};
RGBA red = {255, 0, 0, 255};

void render_circles(SDL_Renderer *renderer)
{
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    // SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    int thick_border = 1;
    draw_circumference(renderer, 50, 50, 100, white, thick_border);
    draw_circumference(renderer, 200, 200, 50, white, thick_border);
    draw_circumference(renderer, 300, 400, 20, white, thick_border);
    draw_circumference(renderer, 400, 50, 10, white, thick_border);
    draw_circumference(renderer, 500, 10, 20, white, thick_border);
}

void render_polar_axis(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    int thick_border = 0;

    int center_x = WINDOW_WIDTH / 2;
    int center_y = WINDOW_HEIGHT / 2;
    for (int i = 40; i < 440; i += 40)
    {
        draw_circumference(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, i, (RGBA){100, 100, 100, 255}, thick_border);
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

void render_exemple_tree(SDL_Renderer *renderer)
{
    const float pi = 3.141592653589793;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // Draw nodes
    draw_circumference_polar(renderer, 0, 0, 5, white);
    draw_circumference_polar(renderer, 2 * pi / 3, 40, 5, white);
    draw_circumference_polar(renderer, 4 * pi / 3, 40, 5, white);
    draw_circumference_polar(renderer, 6 * pi / 3, 40, 5, white);
    draw_circumference_polar(renderer, pi, 80, 5, white);
    // Draw connectors
    draw_line_polar(renderer, 0, 0, 2 * pi / 3, 40, white);
    draw_line_polar(renderer, 0, 0, 4 * pi / 3, 40, white);
    draw_line_polar(renderer, 0, 0, 6 * pi / 3, 40, white);
    draw_line_polar(renderer, 2 * pi / 3, 40, pi, 80, white);
}

void render_tree(SDL_Renderer *renderer, Tree tree)
{
    draw_tree_level_based_polar(renderer, tree, 1, 0, 0, 2 * 3.1415926);
}

void render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    render_polar_axis(renderer);

    // Render tree based on input
    State state1 = {1};
    State state2 = {2};
    State state3 = {3};
    State state4 = {4};
    State state5 = {5};
    State state6 = {6};
    State state7 = {7};
    State state8 = {8};
    State state9 = {9};
    State states[8] = {
        state1,
        state2,
        state3,
        state4,
        state5,
        state6,
        state7,
        state8,
        state9,
    };
    int adjacency_list[8][2] = {
        {1, 2},
        {1, 3},
        {1, 4},
        {2, 5},
        {2, 6},
        {3, 7},
        {3, 8},
        {8, 9},
    };
    Tree tree = {states, adjacency_list, 8, 9};
    render_tree(renderer, tree);

    // Mock render tree, doesnt really depend on input
    // render_exemple_tree(renderer);

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