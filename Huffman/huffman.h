#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include "tree_node.h"
#include <string>
#include <queue>
#include <vector>
#include <fstream>

// Macro used to compile debug statements
// #define DEBUG

// Maximum of 128 TreeNode pointers
#define MAX_NODE_ARRAY_LENGTH 128

#define ONE  0b1000'0000
#define ZERO 0b0000'0000

/**
 * HeaderField
 * @param byte: Uncompressed character
 * @param frequency
 */

typedef struct HeaderField{
    char byte;
    unsigned int frequency;
}HeaderField;

class Huffman {
    protected:
        // std::string source;
        std::fstream input;
        std::fstream output;
        // TreeNode* node_array[MAX_NODE_ARRAY_LENGTH];
        // int node_array_size;
        std::vector<TreeNode*> node_array;
        std::priority_queue<TreeNode*, std::vector<TreeNode*>, CompareTreeNode> priority_queue;
        TreeNode* root;
        void create_tree();

    public:
        Huffman();
        ~Huffman();

        
        // void create_priority_queue();
        // void insert_into_array(TreeNode* tn);

        void clear(); // TODO
};

#endif // HUFFMAN_H_