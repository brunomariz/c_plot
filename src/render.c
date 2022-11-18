#include "../inc/c_plot.h"

void c_plot_circle_draw(SDL_Renderer *renderer, int x, int y)
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

void c_plot_tree_draw(SDL_Renderer *renderer, CP_Axis *axis, CS_SList *node_positions, CS_SList *connection_positions)
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
        c_plot_circle_draw(renderer, node_position_cartesian.x, node_position_cartesian.y);

        // Update list item
        node_list_item = node_list_item->next;
    }
}

void c_plot_function_draw(SDL_Renderer *renderer, CP_Axis *axis, CP_Function *function)
{
    // int x1, y1, x2, y2;
    // for (size_t i = 0; i < function->num_points - 1; i++)
    // {
    //     x1 = function->x[i] * axis->d1_scale + axis->origin_position->x;
    //     x2 = function->x[i + 1] * axis->d1_scale + axis->origin_position->x;
    //     y1 = function->y[i] * axis->d1_scale + axis->origin_position->y;
    //     y1 = function->y[i + 1] * axis->d1_scale + axis->origin_position->y;
    // }
    SDL_Point *points = malloc(sizeof(SDL_Point) * function->num_points);
    for (size_t i = 0; i < function->num_points; i++)
    {
        points[i].x = function->x[i] * axis->d1_scale + axis->origin_position->x;
        points[i].y = -function->y[i] * axis->d2_scale + axis->origin_position->y;
    }
    // points[function->num_points - 1] = (SDL_Point){function->x[function->num_points - 1], function->y[function->num_points - 1]};
    // SDL_Point *points = malloc(sizeof(SDL_Point) * 3);
    // points[0] = (SDL_Point){10, 20};
    // points[1] = (SDL_Point){100, 200};
    // points[2] = (SDL_Point){200, 300};
    SDL_RenderDrawLines(renderer, points, function->num_points);
}