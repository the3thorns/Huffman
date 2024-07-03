#ifndef HUFFMAN_DECOMPRESSOR_H_
#define HUFFMAN_DECOMPRESSOR_H_

#include <string>
#include <unordered_map>
#include <string>
#include <queue>
#include <array>
#include "tree_node.h"

#define MAX_NODE_ARRAY_LENGTH 128

class HuffmanDecompressor {
    private:
        std::string source;
        TreeNode* node_array[MAX_NODE_ARRAY_LENGTH];
        int node_array_size;
        std::priority_queue<TreeNode*, std::vector<TreeNode*>, CompareTreeNode> priority_queue;
};

#endif // HUFFMAN_DECOMPRESSOR_H_