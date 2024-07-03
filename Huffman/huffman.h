#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include "tree_node.h"
#include <string>
#include <queue>

// Macro used to compile debug statements
#define DEBUG

// Maximum of 128 TreeNode pointers
#define MAX_NODE_ARRAY_LENGTH 128

class Huffman {
    protected:
        std::string source;
        TreeNode* node_array[MAX_NODE_ARRAY_LENGTH];
        int node_array_size;
        std::priority_queue<TreeNode*, std::vector<TreeNode*>, CompareTreeNode> priority_queue;
        TreeNode* root;

    public:
        Huffman();
        ~Huffman();

        void create_tree();
        void create_priority_queue();
        void insert_into_array(TreeNode* tn);

        void clear(); // TODO
};

#endif // HUFFMAN_H_