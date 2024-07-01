#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>

typedef struct PQElement {
    char byte;
    int frequency;

    PQElement(char byte, int frequency);
};

class PriorityQueue {
    private:
        std::vector<PQElement> min_heap;

        int getLeftChildIndex(int i);
        int getRightChildIndex(int i);
        bool hasLeftChild(int i);
        bool hasRightChild(int i);

        void swap(int i, int j);
        void shiftDown(int i);
    
    public:
        int size();
        void insert(char byte); // Prior to heapify process
        void heapify();
        PQElement pop(); // Pops and REMOVES extracted element element
};



#endif