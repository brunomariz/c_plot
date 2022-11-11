#include "../inc/c_plot.h"

int main(void)
{
    CS_TreeNode *node1 = c_structures_tree_node_create(1, NULL);
    CS_TreeNode *node2 = c_structures_tree_node_create(2, NULL);
    CS_TreeNode *node3 = c_structures_tree_node_create(3, NULL);
    CS_TreeNode *node4 = c_structures_tree_node_create(4, NULL);
    CS_TreeNode *node5 = c_structures_tree_node_create(5, NULL);
    CS_TreeNode *node6 = c_structures_tree_node_create(6, NULL);
    c_structures_tree_node_add_child(node1, node2);
    c_structures_tree_node_add_child(node1, node3);
    c_structures_tree_node_add_child(node3, node4);
    c_structures_tree_node_add_child(node3, node5);
    c_structures_tree_node_add_child(node5, node6);

    c_plot_tree_show(node1);

    return 0;
}