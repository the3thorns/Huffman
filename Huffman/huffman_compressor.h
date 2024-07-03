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
        void encode(std::string source);
};


#endif