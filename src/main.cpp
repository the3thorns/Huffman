#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "../lib/huffman_node.h"

int main(void) {

    // Operator overloading test (Working)

    // HuffmanNode n1(30, 'a');
    // HuffmanNode n2(10, 'b');

    // int mayor;
    // std::string mayor_node = "";

    // if (n2 > n1) {
    //     mayor = n2.getFrequency();
    //     mayor_node = "n2";
    // } else {
    //     mayor = n1.getFrequency();
    //     mayor_node = "n1";
    // }

    // std::cout << "El nodo \"mayor\" es " << mayor_node << ": " << mayor << std::endl;


    std::ifstream file;
    file.open("./test.txt");

    if (file.is_open()) {
        char byte_readed;
        file >> byte_readed;
        while (!file.eof()) {
            std::cout << byte_readed;
            file >> byte_readed;
        }

        // std::cout << "(EOF)" << std::endl;
        file.close();
    }

    return 0;
}