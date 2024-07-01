#include "priority_queue.h"

PQElement::PQElement(char byte, int frequency) {
    this->byte = byte;
    this->frequency = frequency;
}

// Private functions

int PriorityQueue::getLeftChildIndex(int i) {
    return 2 * i + 1;
}

int PriorityQueue::getRightChildIndex(int i) {
    return 2 * i + 2;
}

bool PriorityQueue::hasLeftChild(int i) {
    return getLeftChildIndex(i) < min_heap.size();
}

bool PriorityQueue::hasRightChild(int i) {
    return getRightChildIndex(i) < min_heap.size();
}

void PriorityQueue::swap(int i, int j) {
    PQElement swapped = min_heap[i];
    min_heap[i] = min_heap[j];
    min_heap[j] = swapped;
}

void PriorityQueue::shiftDown(int i) {
    int min_index; // Minimum index

    while (hasLeftChild(i)) {
        min_index = getLeftChildIndex(i);
        int right_index = getRightChildIndex(i);
        if (hasRightChild(i) && min_heap[right_index].frequency < min_heap[min_index].frequency) {
            min_index = right_index;
        }

        if (min_heap[min_index].frequency < min_heap[i].frequency) {
            swap(min_index, i);
            i = min_index;
        } else {
            break;
        }
    }
}


// Public functions

int PriorityQueue::size() {
    return min_heap.size();
}

void PriorityQueue::insert(char byte) {
    // Check if the byte is in the vector
    for (int i = 0; i < min_heap.size(); i++) {
        if (min_heap[i].byte == byte) {
            min_heap[i].frequency++;
            return;
        }
    }

    PQElement added_element(byte, 1);

    min_heap.push_back(added_element);
}

void PriorityQueue::heapify() {
    for (int i = min_heap.size() / 2 - 1; i >= 0; i--) {
        shiftDown(i);
    }
}

PQElement PriorityQueue::pop() {
    swap(0, min_heap.size() - 1);
    PQElement element = min_heap[min_heap.size() -1];
    min_heap.pop_back();
    shiftDown(0);
    return element;
}

