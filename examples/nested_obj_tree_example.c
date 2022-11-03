#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "../inc/c_trees.h"
#include "render.h"

int event_handler(SDL_Event event);

int main(void)
{
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("C_TREES",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       CT_WINDOW_WIDTH, CT_WINDOW_HEIGHT, 0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // animation loop
    int close_requested = 0;
    while (!close_requested)
    {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            close_requested = event_handler(event);
        }

        // Call render function
        render_tree_nested_obj(rend);

        SDL_RenderPresent(rend);
    }

    // clean up resources before exiting
    if (rend)
    {
        SDL_DestroyRenderer(rend);
    }
    if (win)
    {
        SDL_DestroyWindow(win);
    }
    SDL_Quit();
}

int event_handler(SDL_Event event)
{
    int close_requested = 0;
    if (event.type == SDL_QUIT)
    {
        close_requested = 1;
    }
    return close_requested;
}