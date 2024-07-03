#include "huffman_compressor.h"
#include "tree_node.h"
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>


/**
 * HUFFMAN COMPRESSOR
 */

HuffmanCompressor::HuffmanCompressor() {
    root = nullptr;
    node_array_size = 0;
}

HuffmanCompressor::~HuffmanCompressor() {
    clear();
}

void HuffmanCompressor::create_tree() { // WORKS
    
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

void HuffmanCompressor::create_priority_queue() {

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

// Recursive algorithm
void HuffmanCompressor::create_huffman_table() { // WORKS
    if (root != nullptr){
        create_huffman_table(root, "");

        #ifdef DEBUG
            for (const auto &keyValue : huffman_table) {
                std::cout << keyValue.first << ": " << keyValue.second << std::endl;
            }
        #endif
    }
}

void HuffmanCompressor::create_huffman_table(TreeNode* node, std::string code) { // WORKS
    if (node->isLeaf()) {
        huffman_table[node->byte] = code;
        return;
    }

    create_huffman_table(node->left, code + "0");
    create_huffman_table(node->right, code + "1");
}

void HuffmanCompressor::encode(std::string source) {
    // TODO
    // clear();
    this->source = source;
    create_priority_queue();
    create_tree();
    create_huffman_table();

    // Open resoruces

    std::ifstream input;
    input.open(source);

    std::fstream output;
    output.open("Encoded.huf", std::ios::out | std::ios::binary);

    char byte_readed;
    unsigned char byte_writed = 0;
    int byte_size = 0;

    /**
     * ==Header creation==
     */
    unsigned char n_symbols = huffman_table.size();
    output.write(reinterpret_cast<char*>(&n_symbols), sizeof(unsigned char));

    for (const auto &keyValue : huffman_table) {
        char symbol = keyValue.first;
        output.write(&symbol, sizeof(char));
        for (int i = 0; i < node_array_size; i++) {
            if (node_array[i]->byte == keyValue.first){
                unsigned short frequency = node_array[i]->frequency;
                output.write(reinterpret_cast<char*>(&frequency), sizeof(unsigned short));
                break;
            }
        }
    }

    /**
     * ==Data encoding==
     */

    while (input >> byte_readed) {
        std::string code = huffman_table[byte_readed];
        for (int i = 0; i < code.size(); i++) {
            if (byte_size == 0) {
                output << byte_writed;
                byte_writed = 0;
                byte_size = 0;
            }
            if (code[i] == 1){
                byte_writed++;
            }
            byte_writed << 1;
            byte_size--;
        }
    }
    input.close();
    output.close();

    // TODO: Remove clear when the algorithm is tested
    clear();
}

void HuffmanCompressor::clear() { // WORKS
    // Free memory of vector and set array_size = 0
    for (int i = 0; i < node_array_size; i++){
        delete node_array[i];
    }
    node_array_size = 0;

    // Check if (for some unexpected behaiviour) the priority_queue is full of items
    while (priority_queue.size() != 0) {
        priority_queue.pop();
    }
    source.clear();
    huffman_table.clear();
    root = nullptr;
}

