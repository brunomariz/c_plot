/**
 * c_trees.c - library for rendering trees
 */
#include "../inc/c_trees.h"

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

void draw_circumference(SDL_Renderer *renderer, int x, int y, int r, RGBA color)
{
    SDL_RenderDrawPoint(renderer, x, y);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int point_x, point_y;
    for (float theta = 0.0; theta < 2 * 3.1415; theta += 0.001)
    {
        point_x = x + (cos(theta) * r);
        point_y = y + (sin(theta) * r);
        // Draw main points
        SDL_RenderDrawPoint(renderer, point_x, point_y);
        SDL_RenderDrawPoint(renderer, point_x + 1, point_y);
        SDL_RenderDrawPoint(renderer, point_x - 1, point_y);
        SDL_RenderDrawPoint(renderer, point_x, point_y + 1);
        SDL_RenderDrawPoint(renderer, point_x, point_y - 1);
    }
}

void draw_circumference_polar(SDL_Renderer *renderer, float theta, int r, RGBA color)
{
    int dest_x = (int)(cos(theta) * r);
    int dest_y = -(int)(sin(theta) * r);
    draw_circumference(renderer, dest_x + WINDOW_WIDTH / 2, dest_y + WINDOW_HEIGHT / 2, 15, color);
}
