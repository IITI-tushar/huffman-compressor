#include "tree_builder.h"
#include "utilities.h"
#include <unistd.h>
#include <cstdlib>

Min_Heap* createAndBuildMin_Heap(char arr[], int freq[], int unique_size) {
    int i;
    Min_Heap* minHeapNew = new struct Min_Heap(unique_size);
    for (i = 0; i < unique_size; ++i) {
        minHeapNew->array[i] = new Node(arr[i], freq[i]);
    }
    int n = minHeapNew->size - 1;
    for (i = (n - 1) / 2; i >= 0; --i) {
        Heapify(minHeapNew, i);
    }
    return minHeapNew;
}

struct Node* buildHuffmanTree(char arr[], int freq[], int unique_size) {
    struct Node *l, *r, *top;
    while (!isSizeOne(minHeapGlobal)) {
        l = extractMinFromMin_Heap(minHeapGlobal);
        r = extractMinFromMin_Heap(minHeapGlobal);
        top = newNode('$', l->freq + r->freq);
        top->l = l;
        top->r = r;
        insertIntoMin_Heap(minHeapGlobal, top);
    }
    return extractMinFromMin_Heap(minHeapGlobal);
}

void printCodesIntoFile(int fd2, struct Node* root, int arr[], int top) {
    int i;
    if (root->l) {
        arr[top] = 0;
        printCodesIntoFile(fd2, root->l, arr, top + 1);
    }
    if (root->r) {
        arr[top] = 1;
        printCodesIntoFile(fd2, root->r, arr, top + 1);
    }
    if (isLeaf(root)) {
        codeData = (struct code*)malloc(sizeof(struct code));
        tree = (Tree*)malloc(sizeof(Tree));
        codeData->p = NULL;
        codeData->k = root->character;
        tree->g = root->character;
        write(fd2, &tree->g, sizeof(char));
        for (i = 0; i < top; i++) {
            codeData->code_arr[i] = arr[i];
        }
        tree->len = top;
        write(fd2, &tree->len, sizeof(int));
        tree->dec = convertBinaryToDecimal(codeData->code_arr, top);
        write(fd2, &tree->dec, sizeof(int));
        codeData->l = top;
        codeData->p = NULL;
        if (k == 0) {
            front = rear = codeData;
            k++;
        }
        else {
            rear->p = codeData;
            rear = rear->p;
        }
    }
}

void ExtractCodesFromFile(int fd1) {
    read(fd1, &t->g, sizeof(char));
    read(fd1, &t->len, sizeof(int));
    read(fd1, &t->dec, sizeof(int));
}

void ReBuildHuffmanTree(int fd1, int size) {
    int i = 0, j, l;
    tree = (Tree*)malloc(sizeof(Tree));
    tree_temp = tree;
    tree->f = NULL;
    tree->r = NULL;
    t = (Tree*)malloc(sizeof(Tree));
    t->f = NULL;
    t->r = NULL;
    for (l = 0; l < size; l++) {
        tree_temp = tree;
        ExtractCodesFromFile(fd1);
        int bin[MAX], bin_con[MAX];
        for (i = 0; i < MAX; i++) {
            bin[i] = bin_con[i] = 0;
        }
        convertDecimalToBinary(bin, t->dec, t->len);
        for (i = 0; i < t->len; i++) {
            bin_con[i] = bin[i];
        }
        for (j = 0; j < t->len; j++) {
            if (bin_con[j] == 0) {
                if (tree_temp->f == NULL) {
                    tree_temp->f = (Tree*)malloc(sizeof(Tree));
                }
                tree_temp = tree_temp->f;
            }
            else if (bin_con[j] == 1) {
                if (tree_temp->r == NULL) {
                    tree_temp->r = (Tree*)malloc(sizeof(Tree));
                }
                tree_temp = tree_temp->r;
            }
        }
        tree_temp->g = t->g;
        tree_temp->len = t->len;
        tree_temp->dec = t->dec;
        tree_temp->f = NULL;
        tree_temp->r = NULL;
        tree_temp = tree;
    }
}
