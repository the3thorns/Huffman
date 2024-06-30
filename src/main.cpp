#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "../lib/huffman_node.h"


typedef struct MinHeapElement{
            char byte;
            int frequency;

            MinHeapElement(char byte, int frequency) {
                this->byte = byte;
                this->frequency = frequency;
            }
} MinHeapElement;


class SimpleMinHeap {
    private:

        std::vector<MinHeapElement> vector; // En cuanto se crea la clase el vector se crea automáticamente

        int getLeftChildIndex(int i) {
            return 2 * i + 1;
        }

        int getRightChildIndex(int i) {
            return 2 * i + 2;
        }

        bool hasLeftChild(int i) {
            return getLeftChildIndex(i) < vector.size();
        }

        bool hasRightChild(int i) {
            return getRightChildIndex(i) < vector.size();
        }

        bool isLeaf(int i) {
            return i > vector.size() / 2;
        }

        void swap (int i, int j) {
            MinHeapElement swapped = vector[i];
            vector[i] = vector[j];
            vector[j] = swapped;
        }

        void shiftDown(int i) {
            int min_index; // Minimum index

            while (hasLeftChild(i)) {
                min_index = getLeftChildIndex(i);
                int right_index = getRightChildIndex(i);
                if (hasRightChild(i) && vector[right_index].frequency < vector[min_index].frequency) {
                    min_index = right_index;
                }

                if (vector[min_index].frequency < vector[i].frequency) {
                    swap(min_index, i);
                    i = min_index;
                } else {
                    break;
                }
            }
        }

    public:

        int size() {
            return vector.size();
        }

        /**
         * insert adds a new element into the unheapified element
         * @param byte The byte to insert
         * 
         * If the function finds the byte in the vector, increases its frequency and returns
         * Else: pushes the new byte as a MinHeapElement with frequency 1
         */
        void insert(char byte) {
            // Check if the byte is in the vector
            for (int i = 0; i < vector.size(); i++) {
                if (vector[i].byte == byte) {
                    vector[i].frequency++;
                    return;
                }
            }

            MinHeapElement added_element(byte, 1);

            vector.push_back(added_element);
        }

        /**
         * This function creates a heap in order to create a priority queue
         */

        void heapify() {
            for (int i = vector.size() / 2 - 1; i >= 0; i--) {
                shiftDown(i);
            }
        }

        MinHeapElement pop() {
            swap(0, vector.size() - 1);
            MinHeapElement element = vector[vector.size() -1];
            vector.pop_back();
            shiftDown(0);
            return element;
        }
        
};


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

    // Lectura de fichero byte a byte (Working)

    std::ifstream file;
    file.open("./test.txt");
    SimpleMinHeap minHeap;

    if (file.is_open()) {
        char byte_readed;
        file >> byte_readed;
        while (!file.eof()) {
            // Insert into heap
            minHeap.insert(byte_readed);
            file >> byte_readed;
        }
        file.close();
    }

    while (minHeap.size() != 0) {
        minHeap.heapify();
        MinHeapElement elem = minHeap.pop();
        std::cout << elem.byte << ": " << elem.frequency << std::endl;
    }

    

    return 0;
}

// Min Heap functionalities
/**
 * The min heap consists of a vector (The min Heap) and three functions: "insert", "swap" (private), "heapify"
 */

