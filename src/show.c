#include "../inc/c_plot.h"

void c_plot_tree_show(CS_TreeNode *root_node)
{
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return;
    }

    SDL_Window *win = SDL_CreateWindow("C_PLOT",
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
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // Get trees position info
    CP_TreePositionInfoPolar *position_info = c_plot_tree_get_positions_level_based_polar(root_node);
    // CP_Axis *axis = c_plot_axis_create(CP_AXIS_TYPE_POLAR, 2 * 3.1415926, 40);
    CP_Axis *axis = c_plot_axis_create(CP_AXIS_TYPE_POLAR, 4, 80, &(CP_CartesianCoord){CP_WINDOW_WIDTH / 2, CP_WINDOW_HEIGHT / 2});
    // animation loop
    int close_requested = 0;
    int grow = 1;
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

        // axis->origin_position->x = cos((float)axis->d2_scale / 5.0) * 20 + CP_WINDOW_WIDTH / 2;
        // axis->origin_position->y = sin((float)axis->d2_scale / 5.0) * 20 + CP_WINDOW_HEIGHT / 2;
        if (axis->d2_scale > 100)
            grow = -1;
        if (axis->d2_scale < 60)
            grow = 1;
        axis->d2_scale += grow * 0.7;
        // axis->d1_scale += grow;

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        // Render grid
        SDL_SetRenderDrawColor(renderer, 255 * 0.90, 255 * 0.90, 255 * 0.90, 150);
        c_plot_draw_grid(renderer, axis);
        // Render axis
        SDL_SetRenderDrawColor(renderer, 255 * 0.75, 255 * 0.75, 255 * 0.75, 255);
        c_plot_draw_axis(renderer, axis);
        // Render Tree
        c_plot_draw_tree(renderer, axis, position_info->node_positions, position_info->connection_positions);

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