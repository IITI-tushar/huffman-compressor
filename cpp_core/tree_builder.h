#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

#include "huffman.h"

Min_Heap* createAndBuildMin_Heap(char arr[], int freq[], int unique_size);
struct Node* buildHuffmanTree(char arr[], int freq[], int unique_size);
void printCodesIntoFile(int fd2, struct Node* root, int arr[], int top);
void ReBuildHuffmanTree(int fd1, int size);
void ExtractCodesFromFile(int fd1);

#endif
