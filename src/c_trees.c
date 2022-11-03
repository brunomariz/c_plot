/**
 * c_trees.c - library for rendering trees
 */
#include "../inc/c_trees.h"

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

int get_num_children(CT_Tree tree, int id);

void c_trees_draw_circumference(SDL_Renderer *renderer, int x, int y, int r, CT_RGBA color, int thick_border)
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

void c_trees_draw_circumference_polar(SDL_Renderer *renderer, float theta, int r, int R, CT_RGBA color)
{
    int dest_x = (int)(cos(theta) * r);
    int dest_y = -(int)(sin(theta) * r);
    int thick_border = 1;
    c_trees_draw_circumference(renderer, dest_x + CT_WINDOW_WIDTH / 2, dest_y + CT_WINDOW_HEIGHT / 2, R, color, thick_border);
}

void c_trees_draw_line_polar(SDL_Renderer *renderer, float theta_orig, int r_orig, float theta_dest, int r_dest, CT_RGBA color)
{
    int orig_x = (int)(cos(theta_orig) * r_orig) + CT_WINDOW_WIDTH / 2;
    int orig_y = -(int)(sin(theta_orig) * r_orig) + CT_WINDOW_HEIGHT / 2;
    int dest_x = (int)(cos(theta_dest) * r_dest) + CT_WINDOW_WIDTH / 2;
    int dest_y = -(int)(sin(theta_dest) * r_dest) + CT_WINDOW_HEIGHT / 2;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, orig_x, orig_y, dest_x, dest_y);
}

void c_trees_draw_node_polar(SDL_Renderer *renderer, float theta, int r)
{
    c_trees_draw_circumference_polar(renderer, theta, r, 5, (CT_RGBA){255, 255, 255, 255});
}

CT_PolarCoord c_trees_draw_tree_level_based_polar_adj_list(SDL_Renderer *renderer, CT_Tree tree, int start,
                                                           int vertical_level,
                                                           float section_low, float section_high)
{
    int num_children = get_num_children(tree, start);

    // Calculate node position
    float theta = (section_high - section_low) / 2 + section_low;
    int r = vertical_level * 40;

    if (num_children < 1)
    {
        // Draw node
        c_trees_draw_node_polar(renderer, theta, r);
    }
    else
    {
        int child_horizontal_level = 0;
        // Loop through adjecancy list and look for children of start node,
        // then run draw function on children recursively
        for (int i = 0; i < tree.num_connections; i++)
        {
            int parent_id = tree.adjacency_list[i * 2 + 0];
            int child_id = tree.adjacency_list[i * 2 + 1];
            if (parent_id == start)
            {
                // Calculate child parameters
                int child_vertical_level = vertical_level + 1;
                float child_section_low = section_low + (section_high - section_low) / num_children * child_horizontal_level;
                float child_section_high = section_low + (section_high - section_low) / num_children * (child_horizontal_level + 1);
                // Draw child
                CT_PolarCoord child_coord = c_trees_draw_tree_level_based_polar_adj_list(renderer, tree, child_id, child_vertical_level, child_section_low, child_section_high);
                // Draw connector to child
                c_trees_draw_line_polar(renderer, theta, r, child_coord.theta, child_coord.r, (CT_RGBA){255, 255, 255, 255});

                // Increment horizontal level
                child_horizontal_level++;

                // Draw parent
                c_trees_draw_node_polar(renderer, theta, r);
            }
        }
    }
    return (CT_PolarCoord){theta, r};
}

CT_PolarCoord c_trees_draw_tree_level_based_polar_nested_obj(SDL_Renderer *renderer, CT_Tree tree, int start,
                                                             int vertical_level,
                                                             float section_low, float section_high)
{
}

int get_num_children(CT_Tree tree, int id)
{
    int num_children = 0;
    for (int i = 0; i < tree.num_connections; i++)
    {
        // Test if parent is node with id
        if (tree.adjacency_list[i * 2 + 0] == id)
        {
            num_children++;
        }
    }
    return num_children;
}
