#ifndef HUFFMAN_COMPRESSOR_H
#define HUFFMAN_COMPRESSOR_H

#include "priority_queue.h"
#include <unordered_map>
#include <string>

class HuffmanCompressor {
    private:
        typedef struct TreeNode {
            char byte;
            int frequency;
            TreeNode* left;
            TreeNode* right;

            TreeNode(char byte, int frequency);
        }TreeNode;

        std::string source;
        PriorityQueue priority_queue;
        TreeNode* root;
        std::unordered_map<char, std::string> conversion_table;

    public:

        void create_tree();
        void create_priority_queue();
        void create_huffman_table();

        /**
         * Step 1: Opens de resoruce
         * Step 2: Builds the priority queue
         * Step 3: Builds the Huffman tree
         * Step 4: Creates the Huffman table
         * Step 5: Encodes the code
         */
        void encode(std::string source);




};

#endif