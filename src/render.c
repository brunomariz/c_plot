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
    CP_PolarCoord destination_polar = {theta, r};
    CP_Axis *centralized_axis = c_plot_axis_create(CP_AXIS_TYPE_POLAR, 1, 1, &(CP_CartesianCoord){CP_WINDOW_WIDTH / 2, CP_WINDOW_HEIGHT / 2});
    CP_CartesianCoord destination_cartesian = c_plot_coordinate_polar_to_cartesian(&destination_polar, centralized_axis);
    int thick_border = 1;
    c_plot_draw_circumference(renderer, destination_cartesian.x, destination_cartesian.y, R, color, thick_border);
}

void c_plot_draw_line_polar(SDL_Renderer *renderer, float theta_orig, int r_orig, float theta_dest, int r_dest, CP_RGBA color)
{
    CP_Axis *centralized_axis = c_plot_axis_create(CP_AXIS_TYPE_POLAR, 1, 1, &(CP_CartesianCoord){CP_WINDOW_WIDTH / 2, CP_WINDOW_HEIGHT / 2});
    CP_PolarCoord origin_polar = {theta_orig, r_orig};
    CP_CartesianCoord origin_cartesian = c_plot_coordinate_polar_to_cartesian(&origin_polar,
                                                                              centralized_axis);
    CP_PolarCoord destination_polar = {theta_dest, r_dest};
    CP_CartesianCoord destination_cartesian = c_plot_coordinate_polar_to_cartesian(&destination_polar,
                                                                                   centralized_axis);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, origin_cartesian.x, origin_cartesian.y, destination_cartesian.x, destination_cartesian.y);
}

void c_plot_draw_node_polar(SDL_Renderer *renderer, float theta, int r)
{
    c_plot_draw_circumference_polar(renderer, theta, r, 5, (CP_RGBA){0, 0, 0, 100});
}

void c_plot_draw_polar_axis(SDL_Renderer *renderer)
{
    int thick_border = 0;

    int center_x = CP_WINDOW_WIDTH / 2;
    int center_y = CP_WINDOW_HEIGHT / 2;
    for (int i = 40; i < 440; i += 40)
    {
        c_plot_draw_circumference(renderer, CP_WINDOW_WIDTH / 2, CP_WINDOW_HEIGHT / 2, i, (CP_RGBA){220, 220, 230, 255}, thick_border);
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
        // c_plot_draw_line_polar(renderer, origin_position->theta, origin_position->r * axis->d2_scale, destination_position->theta, destination_position->r * axis->d2_scale, (CP_RGBA){0, 0, 0, 255});
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
        // c_plot_draw_node_polar(renderer, node_position->theta, node_position->r * axis->d2_scale);
        c_plot_draw_circumference(renderer, node_position_cartesian.x, node_position_cartesian.y, 5, (CP_RGBA){0, 0, 0, 255}, 1);

        // Update list item
        node_list_item = node_list_item->next;
    }
}
