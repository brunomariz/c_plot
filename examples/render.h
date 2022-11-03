#ifndef _RENDERH_
#define _RENDERH_

#include <SDL2/SDL.h>
#include "../inc/c_trees.h"

void render_circles(SDL_Renderer *renderer);
void render_polar_axis(SDL_Renderer *renderer);
void render_exemple_tree(SDL_Renderer *renderer);
void render_tree_adj_list(SDL_Renderer *renderer);
void render_tree_nested_obj(SDL_Renderer *renderer);

#endif
