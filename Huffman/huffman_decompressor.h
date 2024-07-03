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
    public:
        /**
         * Reads the header and rebuilds the Huffman Tree
         */
        void decode(std::string source);
};

#endif // HUFFMAN_DECOMPRESSOR_H_