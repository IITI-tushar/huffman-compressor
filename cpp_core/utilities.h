#ifndef UTILITIES_H
#define UTILITIES_H

#include "huffman.h"

void Heapify(Min_Heap* minHeap, int idx);
bool isSizeOne(Min_Heap* minHeap);
struct Node* extractMinFromMin_Heap(Min_Heap* minHeap);
struct Node* newNode(char c, int freq);
void insertIntoMin_Heap(Min_Heap* minHeap, struct Node* top);
bool isLeaf(struct Node* root);
bool isroot(struct Tree* tree);
int convertBinaryToDecimal(int arr[], int n);
void convertDecimalToBinary(int arr[], int dec, int len);

#endif
