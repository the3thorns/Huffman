#include "huffman_decompressor.h"
#include "tree_node.h"
#include <iostream>
#include <fstream>

void HuffmanDecompressor::decode(std::string input, std::string output) {

    this->input.open(input, std::ios::in | std::ios::binary);

    this->output.open(output, std::ios::out);

    if (this->input.is_open() && this->output.is_open()) {
        read_header();

        // #ifdef DEBUG
        //     std::cout << std::endl;
        //     // check_tree_codes();
        // #endif

        read_data();
    }

    this->input.close();
    this->output.close();
}

void HuffmanDecompressor::read_header() {
    unsigned char n_symbols;
    HeaderField field;
    TreeNode* tn;
    input.read(reinterpret_cast<char*>(&n_symbols), sizeof(unsigned char));

    for (int i = 0; i < n_symbols; i++) {
        input.read(reinterpret_cast<char*>(&field), sizeof(HeaderField));
        tn = new TreeNode(field.byte, field.frequency);
        node_array.push_back(tn);
        priority_queue.push(tn);

        #ifdef DEBUG
            std::cout << field.byte << ": " << (int) field.frequency << std::endl;
        #endif
    }

    input.read(reinterpret_cast<char*>(&effective_bits), sizeof(unsigned int));

    create_tree();
}

void HuffmanDecompressor::read_data() {

    TreeNode* aux = root;
    char byte_readed;
    char byte_position = 0;

    #ifdef DEBUG
        int writed = 0;
    #endif

    // Left -> 0; Right -> 1

    while (input.read(reinterpret_cast<char*>(&byte_readed), sizeof(char)) && effective_bits > 0) {
        while (byte_position < 8) {
            if ((byte_readed & ONE) == ONE) {
                aux = aux->right;
            } else {
                aux = aux->left;
            }

            if (aux->isLeaf()) {
                #ifdef DEBUG
                    std::cout << "Byte writed: " << aux->byte << std::endl;
                    writed++;
                #endif
                output.put(aux->byte);
                aux = root;
            }
            byte_readed <<= 1;

            byte_position++;
            effective_bits--;
        }
        byte_position = 0;
    }

    #ifdef DEBUG
        std::cout << "Bytes writed: " << writed << std::endl;
        std::cout << "Effective bits: " << effective_bits << std::endl;
        std::cout << "Byte position: " << (int) byte_position << std::endl;
    #endif
}

// void HuffmanDecompressor::check_tree_codes() {
//     if (root != nullptr) {
//         check_tree_codes(root, "");
//     }
// }

// void HuffmanDecompressor::check_tree_codes(TreeNode* tn, std::string code) {
//     if (tn->isLeaf()) {
//         std::cout << tn->byte << ": " << code << std::endl;
//         return;
//     }

//     check_tree_codes(tn->left, code + '0');
//     check_tree_codes(tn->right, code + '1');
// }