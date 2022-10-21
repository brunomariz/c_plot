#include "../inc/type_utils.h"

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

void draw_circumference(SDL_Renderer *renderer, int x, int y, int r, RGBA color);
void draw_circumference_polar(SDL_Renderer *renderer, float theta, int r, RGBA color);
