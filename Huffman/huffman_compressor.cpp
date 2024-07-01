#include "huffman_compressor.h"
#include "priority_queue.h"
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

HuffmanCompressor::TreeNode::TreeNode(char byte, int frequency) {
    this->byte = byte;
    this->frequency = frequency;
}



void HuffmanCompressor::create_tree() {
    // First iteration
    TreeNode* z = new TreeNode(-1, 0);
    PQElement a = priority_queue.pop();
    PQElement b = priority_queue.pop();

    z->frequency = a.frequency + b.frequency;

    z->left = new TreeNode(a.byte, a.frequency);
    z->right = new TreeNode(b.byte, b.frequency);

    root = z;

    // Other iterations
    while (priority_queue.size() != 0) {
        z = new TreeNode(-1, 0);
        a = priority_queue.pop();
        z->right = root;
        z->left = new TreeNode(a.byte, a.frequency);
        z->frequency = a.frequency + root->frequency;
        root = z;
    }
}

void HuffmanCompressor::create_priority_queue() {
    std::fstream file;
    file.open(source, std::ios::in);

    if (file.is_open()) {
        char byte_readed;
        file >> byte_readed;
        while(!file.eof()) {
            priority_queue.insert(byte_readed);
            file >> byte_readed;
        }
        file.close();
    }

    priority_queue.heapify();
}

void HuffmanCompressor::create_huffman_table() {
    std::string encoding = "";

    // Traverse tree, and get Huffman codes

    TreeNode* aux = root;

    while (aux->left != nullptr) {
        conversion_table[aux->left->byte] = encoding + "0";

        if (aux->right->byte != -1) {
            conversion_table[aux->right->byte] = encoding + "1";
        }

        encoding+="1";
        aux = aux->right;
    }
}

void HuffmanCompressor::encode(std::string source) {
    this->source = source;
    create_priority_queue();
    create_tree();
    create_huffman_table();

    std::fstream file;
    file.open(source);

    
}