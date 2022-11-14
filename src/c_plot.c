/**
 * c_plot.c - library for rendering trees
 */
#include "../inc/c_plot.h"

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

CP_PolarCoord *c_plot_internal_node_position_create(float theta, int r)
{
    CP_PolarCoord *position = malloc(sizeof(*position));
    position->theta = theta;
    position->r = r;
    return position;
}

CP_PolarCoord **c_plot_internal_connection_position_create(float origin_theta, int origin_r,
                                                           float destination_theta, int destination_r)
{
    CP_PolarCoord *origin_position = malloc(sizeof *origin_position);
    origin_position->theta = origin_theta;
    origin_position->r = origin_r;
    CP_PolarCoord *destination_position = malloc(sizeof *destination_position);
    destination_position->theta = destination_theta;
    destination_position->r = destination_r;
    CP_PolarCoord **connection_postions = malloc(sizeof **connection_postions);
    connection_postions[0] = origin_position;
    connection_postions[1] = destination_position;
    return connection_postions;
}

CP_TreePositionInfoPolar *c_plot_tree_get_positions_level_based_polar(CS_TreeNode *root_node)
{

    // Define stack item type
    typedef struct
    {
        CS_TreeNode *node;
        CP_PolarCoord *parent_position;
        float section_high;
        float section_low;
        int vertical_level;
    } CP_InternalStackItemData;

    // Create return struct
    CP_TreePositionInfoPolar *position_info = malloc(sizeof *position_info);
    position_info->node_positions = c_structures_s_list_create();
    position_info->connection_positions = c_structures_s_list_create();

    // Create initial item
    CP_InternalStackItemData *current_stack_item_data = malloc(sizeof *current_stack_item_data);
    current_stack_item_data->node = root_node;
    current_stack_item_data->section_high = 2 * 3.1415926;
    current_stack_item_data->section_low = 0;
    current_stack_item_data->vertical_level = 0;
    current_stack_item_data->parent_position = NULL;

    // Create stack
    CS_SList *stack = c_structures_stack_create();
    c_structures_stack_push(stack, current_stack_item_data);

    // Initialize variables
    while (stack->length > 0)
    {
        // Get next item on stack
        current_stack_item_data = c_structures_stack_pop(stack)->data;

        // Add current node position
        float current_node_theta = (current_stack_item_data->section_high - current_stack_item_data->section_low) / 2 + current_stack_item_data->section_low;
        // int current_node_r = current_stack_item_data->vertical_level * 40;
        int current_node_r = current_stack_item_data->vertical_level;
        c_structures_s_list_append(position_info->node_positions, c_plot_internal_node_position_create(current_node_theta, current_node_r));
        // Add connection to parent
        if (current_stack_item_data->parent_position != NULL)
            c_structures_s_list_append(position_info->connection_positions, c_plot_internal_connection_position_create(current_node_theta, current_node_r, current_stack_item_data->parent_position->theta, current_stack_item_data->parent_position->r));

        // Add children to stack
        CS_SListItem *child_list_item = current_stack_item_data->node->children->head;
        for (size_t i = 0; i < current_stack_item_data->node->children->length; i++)
        {

            // Create child data
            CP_InternalStackItemData *new_stack_item_data = malloc(sizeof *new_stack_item_data);
            new_stack_item_data->node = (CS_TreeNode *)child_list_item->data;
            new_stack_item_data->section_high = current_stack_item_data->section_low + (current_stack_item_data->section_high - current_stack_item_data->section_low) / current_stack_item_data->node->children->length * (i + 1);
            new_stack_item_data->section_low = current_stack_item_data->section_low + (current_stack_item_data->section_high - current_stack_item_data->section_low) / current_stack_item_data->node->children->length * i;
            new_stack_item_data->vertical_level = current_stack_item_data->vertical_level + 1;
            new_stack_item_data->parent_position = malloc(sizeof(CP_PolarCoord *));
            new_stack_item_data->parent_position->theta = current_node_theta;
            new_stack_item_data->parent_position->r = current_node_r;

            // Add child item to stack
            c_structures_stack_push(stack, new_stack_item_data);

            // Update child node
            child_list_item = child_list_item->next;
        }
    }

    return position_info;
}
