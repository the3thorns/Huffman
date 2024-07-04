#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "../Huffman/huffman_compressor.h"
#include "../Huffman/huffman_decompressor.h"


int main(void) {    

    HuffmanCompressor compressor;
    compressor.encode("test.txt", "Encoded.huf");

    HuffmanDecompressor decompressor;
    decompressor.decode("Encoded.huf", "Result.txt");

    return 0;
}

