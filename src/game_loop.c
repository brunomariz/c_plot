#include "../inc/game_loop.h"

#include "../inc/c_trees.h"

void game_loop(SDL_Renderer *renderer, void callback(SDL_Renderer *renderer), void fixedTimeCallback(SDL_Renderer *renderer), int event_handler(SDL_Event event))
{
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
        callback(renderer);

        SDL_RenderPresent(renderer);

        // wait 1/60th of a second
        // SDL_Delay(1000 / 60);
        printf("%d\n", 1000 / (1000 / 60));
        fflush(stdout);
    }
}