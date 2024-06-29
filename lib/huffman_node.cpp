#include "huffman_node.h"

HuffmanNode::HuffmanNode(int frequency, char byte) {
    this->frequency = frequency;
    this->byte = byte;
    this->left = this->right = nullptr; 
}

HuffmanNode* HuffmanNode::getLeft() {
    return this->left;
}

HuffmanNode* HuffmanNode::getRight() {
    return this->right;
}
 
char HuffmanNode::getByte() {
    return this->byte;
}

int HuffmanNode::getFrequency() {
    return this->frequency;
}

bool HuffmanNode::lower(HuffmanNode* n1, HuffmanNode* n2) {
    return n1->getFrequency() < n2->getFrequency();
}


// Overloaded operator >
bool HuffmanNode::operator > (HuffmanNode n1) {
    return this->frequency > n1.getFrequency();
}
// Overloaded operator <
bool HuffmanNode::operator < (HuffmanNode n1) {
    return this->frequency < n1.getFrequency();
}