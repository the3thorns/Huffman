#ifndef HUFFMAN_DECOMPRESSOR_H_
#define HUFFMAN_DECOMPRESSOR_H_

#include <string>
#include <unordered_map>
#include <string>
#include <queue>
#include <array>
#include "huffman.h"
#include "tree_node.h"

#define MAX_NODE_ARRAY_LENGTH 128

class HuffmanDecompressor : Huffman { 
    private:
        unsigned int effective_bits;
    public:
        /**
         * Reads the header and rebuilds the Huffman Tree
         */
        void decode(std::string input, std::string output);

        void read_header();
        void read_data();
        // void check_tree_codes();
        // void check_tree_codes(TreeNode* tn, std::string code);
};

#endif // HUFFMAN_DECOMPRESSOR_H_