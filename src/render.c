#include "../inc/c_plot.h"

void c_plot_draw_circumference(SDL_Renderer *renderer, int x, int y, int r, CP_RGBA color, int thick_border)
{
    SDL_RenderDrawPoint(renderer, x, y);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int point_x, point_y,
        inner_point_1_x, inner_point_1_y,
        inner_point_2_x, inner_point_2_y,
        inner_point_3_x, inner_point_3_y,
        inner_point_4_x, inner_point_4_y;
    for (float theta = 0.0; theta < 2 * 3.1415; theta += 0.001)
    {
        point_x = x + (cos(theta) * r);
        point_y = y + (sin(theta) * r);
        // Draw main points
        SDL_RenderDrawPoint(renderer, point_x, point_y);

        if (thick_border)
        {
            // Draw inner points
            inner_point_1_x = x + (cos(theta) * (r - 1));
            inner_point_1_y = y + (sin(theta) * (r - 1));
            inner_point_2_x = x + (cos(theta) * (r - 2));
            inner_point_2_y = y + (sin(theta) * (r - 2));
            inner_point_3_x = x + (cos(theta) * (r - 3));
            inner_point_3_y = y + (sin(theta) * (r - 3));
            inner_point_4_x = x + (cos(theta) * (r - 4));
            inner_point_4_y = y + (sin(theta) * (r - 4));
            SDL_RenderDrawPoint(renderer, inner_point_1_x, inner_point_1_y);
            SDL_RenderDrawPoint(renderer, inner_point_2_x, inner_point_2_y);
            SDL_RenderDrawPoint(renderer, inner_point_3_x, inner_point_3_y);
            SDL_RenderDrawPoint(renderer, inner_point_4_x, inner_point_4_y);
        }
    }
}

void c_plot_draw_circumference_polar(SDL_Renderer *renderer, float theta, int r, int R, CP_RGBA color)
{
    int dest_x = (int)(cos(theta) * r);
    int dest_y = -(int)(sin(theta) * r);
    int thick_border = 1;
    c_plot_draw_circumference(renderer, dest_x + CP_WINDOW_WIDTH / 2, dest_y + CP_WINDOW_HEIGHT / 2, R, color, thick_border);
}

void c_plot_draw_line_polar(SDL_Renderer *renderer, float theta_orig, int r_orig, float theta_dest, int r_dest, CP_RGBA color)
{
    int orig_x = (int)(cos(theta_orig) * r_orig) + CP_WINDOW_WIDTH / 2;
    int orig_y = -(int)(sin(theta_orig) * r_orig) + CP_WINDOW_HEIGHT / 2;
    int dest_x = (int)(cos(theta_dest) * r_dest) + CP_WINDOW_WIDTH / 2;
    int dest_y = -(int)(sin(theta_dest) * r_dest) + CP_WINDOW_HEIGHT / 2;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, orig_x, orig_y, dest_x, dest_y);
}

void c_plot_draw_node_polar(SDL_Renderer *renderer, float theta, int r)
{
    c_plot_draw_circumference_polar(renderer, theta, r, 5, (CP_RGBA){255, 255, 255, 255});
}

void c_plot_internal_draw_polar_axis(SDL_Renderer *renderer)
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

void c_plot_internal_draw_tree(SDL_Renderer *renderer, CS_SList *node_positions, CS_SList *connection_positions)
{
    // Draw connections
    CS_SListItem *connection_list_item = connection_positions->head;
    for (size_t i = 0; i < connection_positions->length; i++)
    {
        // Parse connection data
        CP_PolarCoord **connection_position_data = connection_list_item->data;
        CP_PolarCoord *origin_position = connection_position_data[0];
        CP_PolarCoord *destination_position = connection_position_data[1];
        // Draw connection
        c_plot_draw_line_polar(renderer, origin_position->theta, origin_position->r, destination_position->theta, destination_position->r, (CP_RGBA){255, 255, 255, 255});
        // Update list item
        connection_list_item = connection_list_item->next;
    }
    // Draw nodes
    CS_SListItem *node_list_item = node_positions->head;
    for (size_t i = 0; i < node_positions->length; i++)
    {
        // Parse node data
        CP_PolarCoord *node_position = node_list_item->data;
        // Draw node
        c_plot_draw_node_polar(renderer, node_position->theta, node_position->r);
        // Update list item
        node_list_item = node_list_item->next;
    }
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

    // Get trees position info
    CP_TreePositionInfoPolar *position_info = c_plot_nested_obj_tree_get_positions_level_based_polar(root_node);

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
        c_plot_internal_draw_polar_axis(renderer);
        // Render Tree
        c_plot_internal_draw_tree(renderer, position_info->node_positions, position_info->connection_positions);

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