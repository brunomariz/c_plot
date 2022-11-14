#include "../inc/c_plot.h"

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

int c_plot_internal_get_num_children(CP_AdjListTree tree, int id)
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

CP_PolarCoord c_plot_adj_list_tree_draw_level_based_polar(SDL_Renderer *renderer, CP_AdjListTree tree, int start,
                                                          int vertical_level,
                                                          float section_low, float section_high)
{
    int num_children = c_plot_internal_get_num_children(tree, start);

    // Calculate node position
    float theta = (section_high - section_low) / 2 + section_low;
    int r = vertical_level * 40;

    if (num_children < 1)
    {
        // Draw node
        c_plot_draw_node_polar(renderer, theta, r);
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
                CP_PolarCoord child_coord = c_plot_adj_list_tree_draw_level_based_polar(renderer, tree, child_id, child_vertical_level, child_section_low, child_section_high);
                // Draw connector to child
                c_plot_draw_line_polar(renderer, theta, r, child_coord.theta, child_coord.r, (CP_RGBA){255, 255, 255, 255});

                // Increment horizontal level
                child_horizontal_level++;

                // Draw parent
                c_plot_draw_node_polar(renderer, theta, r);
            }
        }
    }
    return (CP_PolarCoord){theta, r};
}

CP_PolarCoord c_plot_nested_obj_tree_draw_level_based_polar(SDL_Renderer *renderer,
                                                            CS_TreeNode *root_node,
                                                            int vertical_level,
                                                            float section_low, float section_high)
{
    int num_children = root_node->children->length;

    // Calculate node position
    float theta = (section_high - section_low) / 2 + section_low;
    int r = vertical_level * 40;

    if (num_children < 1)
    {
        // Draw node
        c_plot_draw_node_polar(renderer, theta, r);
    }
    else
    {
        int child_horizontal_level = 0;
        // Loop through children list and run draw function on children recursively
        CS_SListItem *child = root_node->children->head;
        for (int i = 0; i < num_children; i++)
        {
            CS_TreeNode *child_node = child->data;

            // Calculate child parameters
            int child_vertical_level = vertical_level + 1;
            float child_section_low = section_low + (section_high - section_low) / num_children * child_horizontal_level;
            float child_section_high = section_low + (section_high - section_low) / num_children * (child_horizontal_level + 1);

            // Draw child
            CP_PolarCoord child_coord = c_plot_nested_obj_tree_draw_level_based_polar(renderer, child_node, child_vertical_level, child_section_low, child_section_high);
            // Draw connector to child
            c_plot_draw_line_polar(renderer, theta, r, child_coord.theta, child_coord.r, (CP_RGBA){255, 255, 255, 255});
            // Draw parent
            c_plot_draw_node_polar(renderer, theta, r);

            // Increment horizontal level
            child_horizontal_level++;
            // Update child
            child = child->next;
        }
    }
    return (CP_PolarCoord){theta, r};
}
