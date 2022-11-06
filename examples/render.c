#include "render.h"

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

CT_RGBA white = {255, 255, 255, 255};
CT_RGBA red = {255, 0, 0, 255};

void render_circles(SDL_Renderer *renderer)
{
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    // SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    int thick_border = 1;
    c_trees_draw_circumference(renderer, 50, 50, 100, white, thick_border);
    c_trees_draw_circumference(renderer, 200, 200, 50, white, thick_border);
    c_trees_draw_circumference(renderer, 300, 400, 20, white, thick_border);
    c_trees_draw_circumference(renderer, 400, 50, 10, white, thick_border);
    c_trees_draw_circumference(renderer, 500, 10, 20, white, thick_border);
}

void render_polar_axis(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    int thick_border = 0;

    int center_x = CT_WINDOW_WIDTH / 2;
    int center_y = CT_WINDOW_HEIGHT / 2;
    for (int i = 40; i < 440; i += 40)
    {
        c_trees_draw_circumference(renderer, CT_WINDOW_WIDTH / 2, CT_WINDOW_HEIGHT / 2, i, (CT_RGBA){100, 100, 100, 255}, thick_border);
    }

    for (float theta = 0; theta < 2 * 3.14159265358979323846; theta += 3.14159265358979323846 / 20)
    {
        int dest_x = (int)(cos(theta) * CT_WINDOW_WIDTH + CT_WINDOW_WIDTH / 2);
        int dest_y = (int)(sin(theta) * CT_WINDOW_HEIGHT + CT_WINDOW_HEIGHT / 2);

        SDL_RenderDrawLine(renderer, center_x, center_y, dest_x, dest_y);
    }
    SDL_RenderDrawLine(renderer, CT_WINDOW_WIDTH / 2, 0, CT_WINDOW_WIDTH / 2, CT_WINDOW_HEIGHT);
    SDL_RenderDrawLine(renderer, 0, CT_WINDOW_HEIGHT / 2, CT_WINDOW_WIDTH, CT_WINDOW_HEIGHT / 2);
}

void render_exemple_tree(SDL_Renderer *renderer)
{
    const float pi = 3.141592653589793;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // Draw nodes
    c_trees_draw_circumference_polar(renderer, 0, 0, 5, white);
    c_trees_draw_circumference_polar(renderer, 2 * pi / 3, 40, 5, white);
    c_trees_draw_circumference_polar(renderer, 4 * pi / 3, 40, 5, white);
    c_trees_draw_circumference_polar(renderer, 6 * pi / 3, 40, 5, white);
    c_trees_draw_circumference_polar(renderer, pi, 80, 5, white);
    // Draw connectors
    c_trees_draw_line_polar(renderer, 0, 0, 2 * pi / 3, 40, white);
    c_trees_draw_line_polar(renderer, 0, 0, 4 * pi / 3, 40, white);
    c_trees_draw_line_polar(renderer, 0, 0, 6 * pi / 3, 40, white);
    c_trees_draw_line_polar(renderer, 2 * pi / 3, 40, pi, 80, white);
}

void render_tree_adj_list(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    render_polar_axis(renderer);

    // Render tree based on input
    CT_State state1 = {1};
    CT_State state2 = {2};
    CT_State state3 = {3};
    CT_State state4 = {4};
    CT_State state5 = {5};
    CT_State state6 = {6};
    CT_State state7 = {7};
    CT_State state8 = {8};
    CT_State state9 = {9};
    CT_State states[9] = {
        state1,
        state2,
        state3,
        state4,
        state5,
        state6,
        state7,
        state8,
        state9,
    };
    int adjacency_list[8][2] = {
        {1, 2},
        {1, 3},
        {1, 4},
        {2, 5},
        {2, 6},
        {3, 7},
        {3, 8},
        {8, 9},
    };
    CT_AdjListTree tree = {states, (int *)adjacency_list, 9, 8};
    // Render the tree
    c_trees_draw_tree_level_based_polar_adj_list(renderer, tree, 1, 0, 0, 2 * 3.1415926);

    // Render random circles
    // for (float theta = 0; theta < 2 * 3.1415; theta += 0.3)
    // {
    //     for (int r = 40; r < 440; r += 40)
    //     {
    //         if (rand() % 3 == 0)
    //         {
    //             int dest_x = (int)(cos(theta) * r);
    //             int dest_y = (int)(sin(theta) * r);
    //             c_trees_draw_circumference(renderer, dest_x + CT_WINDOW_WIDTH / 2, dest_y + CT_WINDOW_HEIGHT / 2, 15, (CT_RGBA){255, 0, 0, 255});
    //         }
    //     }
    // }
}

void render_tree_nested_obj(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    render_polar_axis(renderer);

    CS_TreeNode *node1 = c_structures_tree_node_create(1, NULL);
    CS_TreeNode *node2 = c_structures_tree_node_create(2, NULL);
    CS_TreeNode *node3 = c_structures_tree_node_create(3, NULL);
    CS_TreeNode *node4 = c_structures_tree_node_create(4, NULL);
    CS_TreeNode *node5 = c_structures_tree_node_create(5, NULL);
    CS_TreeNode *node6 = c_structures_tree_node_create(6, NULL);
    c_structures_tree_node_add_child(node1, node2);
    c_structures_tree_node_add_child(node1, node3);
    c_structures_tree_node_add_child(node2, node4);
    c_structures_tree_node_add_child(node2, node5);
    c_structures_tree_node_add_child(node3, node4);
    c_structures_tree_node_add_child(node3, node5);

    c_trees_draw_tree_level_based_polar_nested_obj(renderer, node1, 0, 0, 2 * 3.1415962);
}

void render_tree_nested_obj_random(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    render_polar_axis(renderer);

    CS_TreeNode *node1 = c_structures_tree_node_create(1, NULL);
    CS_SList *nodes_list = c_structures_s_list_create();
    c_structures_s_list_append(nodes_list, node1);
    for (size_t i = 1; i < 50; i++)
    {
        CS_TreeNode *node = c_structures_tree_node_create(i, NULL);
        int random_parent_index = rand() % i;
        CS_SListItem *random_parent_item = c_structures_s_list_get_item(nodes_list, random_parent_index);
        CS_TreeNode *random_parent_node = random_parent_item->data;
        c_structures_tree_node_add_child(random_parent_node, node);
        c_structures_s_list_append(nodes_list, node);
    }

    SDL_Delay(500);
    c_trees_draw_tree_level_based_polar_nested_obj(renderer, node1, 0, 0, 2 * 3.1415962);
}
