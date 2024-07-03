#ifndef HUFFMAN_COMPRESSOR_H
#define HUFFMAN_COMPRESSOR_H

//#include "priority_queue.h"
#include <unordered_map>
#include <string>
#include <queue>
// #include <array>
#include "tree_node.h"

// Macro used to compile debug statements
#define DEBUG

// Maximum of 128 TreeNode pointers
#define MAX_NODE_ARRAY_LENGTH 128

/**
 * Left: 0
 * Right: 1
 */

class HuffmanCompressor {
    private:
        std::string source;
        TreeNode* node_array[MAX_NODE_ARRAY_LENGTH];
        int node_array_size;
        std::priority_queue<TreeNode*, std::vector<TreeNode*>, CompareTreeNode> priority_queue;
        std::unordered_map<char, std::string> huffman_table;
        TreeNode* root;

        void create_huffman_table(TreeNode* node, std::string code);

    public:

        HuffmanCompressor();
        // When the object is destroyed, frees all memory from the heap
        // The user is not responsible of the allocation of the class
        ~HuffmanCompressor();

        // void insert_into_array(TreeNode* ptr);

        void create_tree();
        void create_priority_queue();
        void create_huffman_table();

        /**
         * Step 1: create_priority_queue()
         * Step 2: create_tree()
         * Step 3: create_huffman_table()
         * Step 4: output the encoded file into a compressed one (compressed.huf)
         */
        void encode(std::string source);

        /**
         * Frees all memory from the heap
         */
        void clear();
};


#endif