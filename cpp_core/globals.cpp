#include "huffman.h"

struct code* codeData = nullptr;
struct code* front = nullptr;
struct code* rear = nullptr;
struct Tree* tree = nullptr;
struct Tree* tree_temp = nullptr;
struct Tree* t = nullptr;
int k = 0;
Min_Heap* minHeapGlobal = nullptr;
