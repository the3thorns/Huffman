#ifndef HUFFMAN_COMPRESSOR_H
#define HUFFMAN_COMPRESSOR_H

//#include "priority_queue.h"
#include <unordered_map>
#include <string>
#include <queue>
// #include <array>
#include "huffman.h"
#include "tree_node.h"

/**
 * Left: 0
 * Right: 1
 */

/**
 * TODO Optimizar gestión de memoria en node_array
 */

class HuffmanCompressor : public Huffman {
    private:
        std::unordered_map<char, std::string> huffman_table;
        int frequency_array[MAX_NODE_ARRAY_LENGTH];
        void create_huffman_table(TreeNode* node, std::string code);

    public:

        HuffmanCompressor();
        // When the object is destroyed, frees all memory from the heap
        // The user is not responsible of the allocation of the class
        ~HuffmanCompressor();

        // void insert_into_array(TreeNode* ptr);

        void create_huffman_table();

        /**
         * Step 1: create_priority_queue()
         * Step 2: create_tree()
         * Step 3: create_huffman_table()
         * Step 4: output the encoded file into a compressed one (compressed.huf)
         */
        void create_priority_queue(std::string input);
        void encode(std::string input, std::string output);
        void write_header();
        void write_data();
};


#endif