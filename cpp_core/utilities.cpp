#include "utilities.h"
#include <algorithm>

void Heapify(Min_Heap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        std::swap(minHeap->array[idx], minHeap->array[smallest]);
        Heapify(minHeap, smallest);
    }
}

bool isSizeOne(Min_Heap* minHeap) {
    return minHeap->size == 1;
}

struct Node* extractMinFromMin_Heap(Min_Heap* minHeap) {
    struct Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    Heapify(minHeap, 0);
    return temp;
}

struct Node* newNode(char c, int freq) {
    return new Node(c, freq);
}

void insertIntoMin_Heap(Min_Heap* minHeap, struct Node* top) {
    minHeap->size++;
    minHeap->array.resize(minHeap->size);
    int i = minHeap->size - 1;
    minHeap->array[i] = top;

    while (i > 0 && minHeap->array[(i - 1) / 2]->freq > minHeap->array[i]->freq) {
        std::swap(minHeap->array[i], minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

bool isLeaf(struct Node* root) {
    return !root->l && !root->r;
}

bool isroot(struct Tree* tree) {
    return !tree->f && !tree->r;
}

int convertBinaryToDecimal(int arr[], int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        res = res * 2 + arr[i];
    }
    return res;
}

void convertDecimalToBinary(int arr[], int dec, int len) {
    for (int i = len - 1; i >= 0; i--) {
        arr[i] = dec % 2;
        dec /= 2;
    }
}
