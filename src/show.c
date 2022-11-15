#include "../inc/c_plot.h"

void c_plot_internal_show_loop(CP_Axis *axis, void callback(SDL_Renderer *renderer, CP_Axis *axis, void *args), void *args)
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

    // === Animation loop ===

    // State structs
    typedef struct mouse_info
    {
        char mouse_down;
        CP_CartesianCoord previous_mouse_position;
        CP_CartesianCoord current_mouse_position;
    } CP_IMouseInfo;
    CP_IMouseInfo mouse_info = {0, (CP_CartesianCoord){axis->origin_position->x, axis->origin_position->y}, (CP_CartesianCoord){axis->origin_position->x, axis->origin_position->y}};

    char close_requested = 0;
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
            if (event.type == SDL_MOUSEWHEEL)
            {
                if (event.wheel.y > 0)
                {
                    // Scroll up
                    axis->d2_scale *= 1.1;
                }
                else if (event.wheel.y < 0)
                {
                    // Scroll down
                    axis->d2_scale /= 1.1;
                    if (axis->d2_scale < 1)
                    {
                        axis->d2_scale = 1;
                    }
                }

                if (event.wheel.x > 0)
                {
                    // Scroll right
                }
                else if (event.wheel.x < 0)
                {
                    // Scroll left
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    mouse_info.mouse_down = 1;
                }
            }
            if (event.type == SDL_MOUSEBUTTONUP)
            {
                mouse_info.mouse_down = 0;
            }
            if (event.type == SDL_MOUSEMOTION)
            {
                mouse_info.current_mouse_position.x = event.motion.x;
                mouse_info.current_mouse_position.y = event.motion.y;
                if (mouse_info.mouse_down)
                {
                    axis->origin_position->x += mouse_info.current_mouse_position.x - mouse_info.previous_mouse_position.x;
                    axis->origin_position->y += mouse_info.current_mouse_position.y - mouse_info.previous_mouse_position.y;
                }
                mouse_info.previous_mouse_position = mouse_info.current_mouse_position;
            }
        }

        callback(renderer, axis, args);

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

typedef struct
{
    CP_TreePositionInfoPolar *position_info;
} CP_InternalTreeCallbackArgs;

void c_plot_internal_tree_show_callback(SDL_Renderer *renderer, CP_Axis *axis, void *args)
{
    CP_InternalTreeCallbackArgs *cast_args = args;

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    // Render grid
    SDL_SetRenderDrawColor(renderer, 255 * 0.80, 255 * 0.80, 255 * 0.80, 150);
    c_plot_draw_grid(renderer, axis);
    // Render axis
    SDL_SetRenderDrawColor(renderer, 255 * 0.75, 255 * 0.75, 255 * 0.75, 255);
    c_plot_draw_axis(renderer, axis);
    // Render Tree
    c_plot_draw_tree(renderer, axis, cast_args->position_info->node_positions, cast_args->position_info->connection_positions);
}

void c_plot_tree_show(CS_TreeNode *root_node)
{
    CP_Axis *axis = c_plot_axis_create(CP_AXIS_TYPE_POLAR, 4, 40, &(CP_CartesianCoord){CP_WINDOW_WIDTH / 2, CP_WINDOW_HEIGHT / 2});

    CP_TreePositionInfoPolar *position_info = c_plot_tree_get_positions_level_based_polar(root_node);

    CP_InternalTreeCallbackArgs *args = malloc(sizeof *args);
    args->position_info = position_info;
    c_plot_internal_show_loop(axis, c_plot_internal_tree_show_callback, args);
}