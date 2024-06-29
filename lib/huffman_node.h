#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H


class HuffmanNode {

    private:
        HuffmanNode* left;
        HuffmanNode* right;
        int frequency;
        char byte;
    
    public:
        HuffmanNode(int frequency, char byte);
        HuffmanNode* getLeft();
        HuffmanNode* getRight();
        int getFrequency();
        char getByte();

        static bool lower(HuffmanNode* n1, HuffmanNode* n2);

        // Overloaded operator >
        bool operator > (HuffmanNode n1);
        // Overloaded operator <
        bool operator < (HuffmanNode n1);
};


#endif