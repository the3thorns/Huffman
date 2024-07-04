#include "huffman.h"
#include <fstream>
#include <iostream>

Huffman::Huffman(){
    root = nullptr;
    // node_array_size = 0;
}

Huffman::~Huffman() {

}

void Huffman::create_tree() {

    TreeNode* t1;
    TreeNode* t2;
    TreeNode* z;

    while (priority_queue.size() > 1) {
        t1 = priority_queue.top();
        priority_queue.pop();

        t2 = priority_queue.top();
        priority_queue.pop();

        z = new TreeNode(-1, t1->frequency + t2->frequency);
        z->left = t1;
        z->right = t2;

        node_array.push_back(z);
        priority_queue.push(z);
    }

    root = priority_queue.top();
    priority_queue.pop();
}



// void Huffman::insert_into_array(TreeNode* tn) {
//     node_array[node_array_size] = tn;
//     node_array_size++;
// }

void Huffman::clear() {
    // TODO
}