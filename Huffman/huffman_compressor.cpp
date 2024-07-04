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

void HuffmanCompressor::create_priority_queue(std::string input) {

    std::ifstream source_file;
    char byte_readed;
    int i;

    source_file.open(input);

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

    #ifdef DEBUG
        std::cout << "create_priority_queue()" << std::endl;
    #endif

    for (int i = 0; i < node_array_size; i++) {
        #ifdef DEBUG
            std::cout << node_array[i]->byte << ": " << (int) node_array[i]->frequency << std::endl;
        #endif
        priority_queue.push(node_array[i]);
    }

    #ifdef DEBUG
        std::cout << std::endl;
    #endif
}

void HuffmanCompressor::create_huffman_table(TreeNode* node, std::string code) { // WORKS
    if (node->isLeaf()) {
        huffman_table[node->byte] = code;
        return;
    }

    create_huffman_table(node->left, code + "0");
    create_huffman_table(node->right, code + "1");
}

void HuffmanCompressor::encode(std::string input, std::string output) {

    create_priority_queue(input);
    create_tree();
    create_huffman_table();

    // Open resoruces

    // std::ifstream input;
    this->input.open(input, std::ios::in);

    // std::fstream output;
    this->output.open(output, std::ios::out | std::ios::binary);

    if (this->input.is_open() && this->output.is_open()) {
        // Write Header
        write_header();
        // Write Data
        write_data();
    }
    

    // char byte_readed;

    /**
     * ==Header creation==
     */

    // unsigned char n_symbols = huffman_table.size();
    
    // #ifdef DEBUG
    //     std::cout << "encode()" << std::endl;
    //     std::cout << "n_symbols: " << (int) n_symbols << std::endl;
    // #endif

    // output.write(reinterpret_cast<char*>(&n_symbols), sizeof(unsigned char));

    // for (const auto &keyValue : huffman_table) {
    //     char symbol = keyValue.first;
    //     #ifdef DEBUG
    //         std::cout << "symbol: " << symbol << std::endl;
    //     #endif
    //     output.write(reinterpret_cast<char*>(&symbol), sizeof(char));
    //     for (int i = 0; i < node_array_size; i++) {
    //         if (node_array[i]->byte == keyValue.first){
    //             // FREQUENCY here
    //             unsigned char frequency = node_array[i]->frequency;

    //             #ifdef DEBUG
    //                 std::cout << "frequency: " << (int) frequency << std::endl;
    //             #endif

    //             output.write(reinterpret_cast<char*>(&frequency), sizeof(unsigned char));
    //             break;
    //         }
    //     }
    // }

    /**
     * ==Data encoding==
     */

    // int byte_size = 0;
    // unsigned char byte_writed = 0;

    // while (input >> byte_readed) {
    //     std::string code = huffman_table[byte_readed];

    //     for (int i = 0; i < code.size(); i++) {
    //         if (byte_size == 8) {
    //             output.write(reinterpret_cast<char*>(&byte_writed), sizeof(unsigned char));
    //             byte_size = 0;
    //             byte_writed = 0;
    //         }
            
    //         if (code[i] == '1') {
    //             byte_writed ^= (ONE >> byte_size);
    //         }
    //         byte_size++;
    //     }
        
    // }
    
    this->input.close();
    this->output.close();
}

void HuffmanCompressor::write_header() {

    HeaderField field;
    unsigned char n_symbol = huffman_table.size();
    output.write(reinterpret_cast<char*>(&n_symbol), sizeof(unsigned char));
    
    unsigned int effective_bits = 0;

    for (const auto &keyValue : huffman_table) {
        for (int i = 0; i < node_array_size;i++) {
            if (node_array[i]->byte == keyValue.first) {
                effective_bits += node_array[i]->frequency * keyValue.second.size();
                field.frequency = node_array[i]->frequency;
                break;
            }
        }
        field.byte = keyValue.first;
        output.write(reinterpret_cast<char*>(&field), sizeof(HeaderField));
    }

    output.write(reinterpret_cast<char*>(&effective_bits), sizeof(unsigned int));

    #ifdef DEBUG
        std::cout << "write_header()" << std::endl;
        std::cout << "Effective bits: " << effective_bits << std::endl;
    #endif
}

void HuffmanCompressor::write_data() {
    char byte_readed;
    int byte_size = 0;
    unsigned char byte_writed = 0;

    #ifdef DEBUG
        int numberOf = 0;
        int writed = 0;
    #endif

    input.get(byte_readed);
    while (!input.eof()) {

        std::string code = huffman_table[byte_readed];
        #ifdef DEBUG
            numberOf++;
            std::cout << "Byte readed: " << byte_readed << std::endl;
        #endif
        for (int i = 0; i < code.size(); i++) {
            if (byte_size == 8) {
                output.write(reinterpret_cast<char*>(&byte_writed), sizeof(unsigned char));
                byte_size = 0;
                byte_writed = 0;
                #ifdef DEBUG
                    writed++;
                #endif
            }
            
            if (code[i] == '1') {
                byte_writed ^= (ONE >> byte_size);
            }
            byte_size++;
        }
        input.get(byte_readed);
    }

    if (input.eof() && byte_size > 0) {
        output.write(reinterpret_cast<char*>(&byte_writed), sizeof(unsigned char));
        #ifdef DEBUG
            writed++;
        #endif
    }

    #ifdef DEBUG
        std::cout << "Number of bytes readed: " << numberOf << std::endl;
        std::cout << "Number of bytes writed: " << writed << std::endl;
    #endif
}


