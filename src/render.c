#include "../inc/c_plot.h"

void c_plot_draw_circle(SDL_Renderer *renderer, int x, int y)
{
    SDL_RenderDrawPoint(renderer, x, y);
    const int r = 5;
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

void c_plot_draw_circumference_polar(SDL_Renderer *renderer, float theta, int r, int R, CP_RGBA color)
{
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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
