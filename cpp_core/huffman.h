#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <vector>

#define MAX 100

struct Node {
    char character;
    int freq;
    Node *l, *r;
    Node(char c, int f)
        : character(c)
        , freq(f)
        , l(nullptr)
        , r(nullptr)
    {
    }
};

struct Min_Heap {
    int size;
    std::vector<Node*> array;
    Min_Heap(int s)
        : size(s)
        , array(s)
    {
    }
};

typedef struct code {
    char k;
    int l;
    int code_arr[MAX];
    struct code* p;
} code;

typedef struct Tree {
    char g;
    int len;
    int dec;
    struct Tree* f;
    struct Tree* r;
} Tree;

extern struct code* codeData;
extern struct code* front;
extern struct code* rear;
extern struct Tree* tree;
extern struct Tree* tree_temp;
extern struct Tree* t;
extern int k;
extern Min_Heap* minHeapGlobal;

#endif
