#include "tree_node.h"

TreeNode::TreeNode(char byte, unsigned short frequency) {
    this->byte = byte;
    this->frequency = frequency;
    left = right = nullptr;
}

bool TreeNode::isLeaf() {
    return (left == nullptr && right == nullptr);
}