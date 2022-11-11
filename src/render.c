#include "../inc/c_plot.h"

void c_plot_internal_render_polar_axis(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    int thick_border = 0;

    int center_x = CP_WINDOW_WIDTH / 2;
    int center_y = CP_WINDOW_HEIGHT / 2;
    for (int i = 40; i < 440; i += 40)
    {
        c_plot_draw_circumference(renderer, CP_WINDOW_WIDTH / 2, CP_WINDOW_HEIGHT / 2, i, (CP_RGBA){100, 100, 100, 255}, thick_border);
    }

    for (float theta = 0; theta < 2 * 3.14159265358979323846; theta += 3.14159265358979323846 / 20)
    {
        int dest_x = (int)(cos(theta) * CP_WINDOW_WIDTH + CP_WINDOW_WIDTH / 2);
        int dest_y = (int)(sin(theta) * CP_WINDOW_HEIGHT + CP_WINDOW_HEIGHT / 2);

        SDL_RenderDrawLine(renderer, center_x, center_y, dest_x, dest_y);
    }
    SDL_RenderDrawLine(renderer, CP_WINDOW_WIDTH / 2, 0, CP_WINDOW_WIDTH / 2, CP_WINDOW_HEIGHT);
    SDL_RenderDrawLine(renderer, 0, CP_WINDOW_HEIGHT / 2, CP_WINDOW_WIDTH, CP_WINDOW_HEIGHT / 2);
}

void c_plot_tree_show(CS_TreeNode *root_node)
{
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return;
    }

    SDL_Window *win = SDL_CreateWindow("C_TREES",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       CP_WINDOW_WIDTH, CP_WINDOW_HEIGHT, 0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, render_flags);
    if (!renderer)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return;
    }

    // animation loop
    int close_requested = 0;
    while (!close_requested)
    {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                close_requested = 1;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        // Render axis
        c_plot_internal_render_polar_axis(renderer);
        // Render Tree
        c_plot_nested_obj_tree_draw_level_based_polar(renderer, root_node, 0, 0, 2 * 3.1415962);

        SDL_RenderPresent(renderer);
    }

    // clean up resources before exiting
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (win)
    {
        SDL_DestroyWindow(win);
    }
    SDL_Quit();
}