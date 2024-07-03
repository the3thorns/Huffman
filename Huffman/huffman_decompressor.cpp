#include "huffman_decompressor.h"
#include <iostream>
#include <fstream>

void HuffmanDecompressor::decode(std::string source) {

    this->source = source;

    std::fstream input;
    input.open(source, std::ios::in | std::ios::binary);


    std::ofstream output;
    output.open("decompressed.txt");

    unsigned char n_symbols;

    unsigned char byte_readed;
    unsigned short frequency;

    
    /**
     * ==Read Header==
     */

    input.read(reinterpret_cast<char*>(&n_symbols), sizeof(char));
    
    for (int i = 0; i < n_symbols; i++) {
        input.read(reinterpret_cast<char*>(&byte_readed), sizeof(char));
        input.read(reinterpret_cast<char*>(&frequency), sizeof(unsigned short));
        
        TreeNode* tn = new TreeNode(byte_readed, frequency);
        insert_into_array(tn);
    }

    /**
     * ==Build Tree==
     */

    create_priority_queue();
    create_tree();

    /**
     * ==Read file and match bits wtih tree==
     */

    TreeNode* aux = root;
    // Left -> 0; Right -> 1

    

}