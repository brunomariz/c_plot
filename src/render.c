#include "../inc/c_plot.h"

void c_plot_draw_circle(SDL_Renderer *renderer, int x, int y)
{
    const int circle_radius = 5;

    SDL_Rect rect;
    int rect_side = 2 * circle_radius / 1.414213562 - 1;
    rect.h = rect_side;
    rect.w = rect_side;
    rect.x = x - rect_side / 2;
    rect.y = y - rect_side / 2;
    SDL_RenderFillRect(renderer, &rect);

    for (float theta = 0; theta < 2 * 3.1415926; theta += 0.5 / circle_radius)
    {
        for (int r = circle_radius / 1.414213562; r < circle_radius + 1; r++)
        {
            int point_x = x + (cos(theta) * r);
            int point_y = y + (sin(theta) * r);
            SDL_RenderDrawPoint(renderer, point_x, point_y);
        }
    }
}

void c_plot_draw_tree(SDL_Renderer *renderer, CP_Axis *axis, CS_SList *node_positions, CS_SList *connection_positions)
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
        CP_CartesianCoord origin_cartesian = c_plot_coordinate_polar_to_cartesian(origin_position, axis);
        CP_CartesianCoord destination_cartesian = c_plot_coordinate_polar_to_cartesian(destination_position, axis);

        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawLine(renderer, origin_cartesian.x, origin_cartesian.y, destination_cartesian.x, destination_cartesian.y);

        // Update list item
        connection_list_item = connection_list_item->next;
    }
    // Draw nodes
    CS_SListItem *node_list_item = node_positions->head;
    for (size_t i = 0; i < node_positions->length; i++)
    {
        // Parse node data
        CP_PolarCoord *node_position = node_list_item->data;
        CP_CartesianCoord node_position_cartesian = c_plot_coordinate_polar_to_cartesian(node_position, axis);
        // Draw node
        c_plot_draw_circle(renderer, node_position_cartesian.x, node_position_cartesian.y);

        // Update list item
        node_list_item = node_list_item->next;
    }
}
