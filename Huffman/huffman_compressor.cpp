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

}

// Recursive algorithm
void HuffmanCompressor::create_huffman_table() { // WORKS
    if (root != nullptr) {
        create_huffman_table(root, "");

        #ifdef DEBUG
            for (const auto &keyValue : huffman_table) {
                std::cout << keyValue.first << ": " << keyValue.second << std::endl;
            }
            std::cout << std::endl;
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

    /**
     * ==Header creation==
     */
    unsigned char n_symbols = huffman_table.size();
    
    #ifdef DEBUG
        std::cout << "encode()" << std::endl;
        std::cout << "n_symbols: " << (int) n_symbols << std::endl;
    #endif

    output.write(reinterpret_cast<char*>(&n_symbols), sizeof(unsigned char));

    for (const auto &keyValue : huffman_table) {
        char symbol = keyValue.first;
        #ifdef DEBUG
            std::cout << "symbol: " << symbol << std::endl;
        #endif
        output.write(reinterpret_cast<char*>(&symbol), sizeof(char));
        for (int i = 0; i < node_array_size; i++) {
            if (node_array[i]->byte == keyValue.first){
                // FREQUENCY here
                unsigned char frequency = node_array[i]->frequency;

                #ifdef DEBUG
                    std::cout << "frequency: " << (int) frequency << std::endl;
                #endif

                output.write(reinterpret_cast<char*>(&frequency), sizeof(unsigned char));
                break;
            }
        }
    }

    /**
     * ==Data encoding==
     */

    int byte_size = 0;
    unsigned char byte_writed = 0;

    while (input >> byte_readed) {
        std::string code = huffman_table[byte_readed];

        for (int i = 0; i < code.size(); i++) {
            if (byte_size == 8) {
                output.write(reinterpret_cast<char*>(&byte_writed), sizeof(unsigned char));
                byte_size = 0;
                byte_writed = 0;
            }
            
            if (code[i] == '1') {
                byte_writed ^= (ONE >> byte_size);
            }
            byte_size++;
        }
        
    }
    
    input.close();
    output.close();
}


