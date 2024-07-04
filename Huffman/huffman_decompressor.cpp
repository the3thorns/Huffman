#include "huffman_decompressor.h"
#include "tree_node.h"
#include <iostream>
#include <fstream>

void HuffmanDecompressor::decode(std::string source) {

    this->source = source;

    std::fstream input;
    input.open(this->source, std::ios::in | std::ios::binary);


    std::fstream output;
    output.open("Result.txt", std::ios::out);

    unsigned char n_symbols;

    char byte_readed = 0;
    unsigned char frequency = 0;

    
    /**
     * ==Read Header==
     */

    input.read(reinterpret_cast<char*>(&n_symbols), sizeof(unsigned char));

    #ifdef DEBUG
        std::cout << "decode()" << std::endl;
        std::cout << "n_symbols: " << (int) n_symbols << std::endl;
    #endif
    
    #ifdef DEBUG
        std::cout << "for loop" << std::endl; 
    #endif

    for (int i = 0; i < n_symbols; i++) {
        input.read(reinterpret_cast<char*>(&byte_readed), sizeof(char));
        input.read(reinterpret_cast<char*>(&frequency), sizeof(unsigned char));

        #ifdef DEBUG
            std::cout << byte_readed << ": " << (int) frequency << std::endl;
        #endif
        
        TreeNode* tn = new TreeNode(byte_readed, frequency);
        insert_into_array(tn);
        priority_queue.push(tn);
    }

    /**
     * ==Build Tree==
     */

    // ! WRONG: create_priority_queue() crea el vector node_array y añade los nodos a la priority queue
    //create_priority_queue();

    create_tree();

    /**
     * ==Read file and match bits wtih tree==
     */

    TreeNode* aux = root;
    unsigned char byte_size = 8;

    // Left -> 0; Right -> 1

    while (input.read(reinterpret_cast<char*>(&byte_readed), sizeof(char))) {
        for (int i = 0; i < byte_size; i++) {

            #ifdef DEBUG
                std::cout << "byte_readed: " << byte_readed << std::endl;
            #endif

            if ((byte_readed & ONE) == ONE) {
                aux = aux->right;
            } else {
                aux = aux->left;
            }

            #ifdef DEBUG
                std::cout << "And operation: " << (byte_readed & ONE) << std::endl;
                std::cout << "Byte in aux node: " << aux->byte << std::endl;
            #endif 

            if (aux->isLeaf()){
                #ifdef DEBUG
                    std::cout << "Escribe" << std::endl;
                #endif
                output << aux->byte;
                aux = root;
            }
            byte_readed <<= 1;
        }
    }

    input.close();
    output.close();
}