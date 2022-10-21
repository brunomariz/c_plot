#include <SDL2/SDL.h>

void game_loop(SDL_Renderer *renderer,
               void callback(SDL_Renderer *renderer),
               void fixed_time_tallback(SDL_Renderer *renderer),
               int event_handler(SDL_Event event));
