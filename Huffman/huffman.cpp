#include "huffman.h"
#include <fstream>
#include <iostream>

Huffman::Huffman(){
    root = nullptr;
    node_array_size = 0;
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

        // insert_into_array(z);
        priority_queue.push(z);
    }

    root = priority_queue.top();
    priority_queue.pop();
}

void Huffman::create_priority_queue() {

    std::ifstream source_file;
    char byte_readed;
    int i;

    source_file.open(source);

    while (source_file >> byte_readed) {
        bool found = false;
        for (i = 0; i < node_array_size; i++) {
            if (node_array[i]->byte == byte_readed) {
                node_array[i]->frequency++;
                found = true;
                break;
            }
        }

        // Adds new node
        if (!found) {
            TreeNode* ptn = new TreeNode(byte_readed, 1);
            node_array[node_array_size] = ptn;
            node_array_size++;
        }
    }
    source_file.close();

    // Add elements in priority queue

    for (int i = 0; i < node_array_size; i++) {
        #ifdef DEBUG
            std::cout << node_array[i]->byte << ": " << node_array[i]->frequency << std::endl;
        #endif
        priority_queue.push(node_array[i]);
    }

    #ifdef DEBUG
        std::cout << std::endl;
    #endif
}

void Huffman::insert_into_array(TreeNode* tn) {
    node_array[node_array_size] = tn;
    node_array_size++;
}

void Huffman::clear() {
    // TODO
}