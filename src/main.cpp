#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "../Huffman/huffman_compressor.h"


int main(void) {    

    HuffmanCompressor compressor;
    compressor.encode("test.txt");

    return 0;
}

