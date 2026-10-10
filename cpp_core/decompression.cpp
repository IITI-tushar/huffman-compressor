#include "decompression.h"
#include "utilities.h"
#include <unistd.h>

void decompressFile(int fd1, int fd2, int f) {
    int inp[8], i, l = 0;
    unsigned char p;
    read(fd1, &p, sizeof(char));
    convertDecimalToBinary(inp, p, 8);
    tree_temp = tree;
    for (i = 0; i < 8 && l < f; i++) {
        if (!isroot(tree_temp)) {
            if (i != 7) {
                if (inp[i] == 0) {
                    tree_temp = tree_temp->f;
                }
                if (inp[i] == 1) {
                    tree_temp = tree_temp->r;
                }
            }
            else {
                if (inp[i] == 0) {
                    tree_temp = tree_temp->f;
                }
                if (inp[i] == 1) {
                    tree_temp = tree_temp->r;
                }
                if (read(fd1, &p, sizeof(char)) != 0) {
                    convertDecimalToBinary(inp, p, 8);
                    i = -1;
                }
                else {
                    break;
                }
            }
        }
        else {
            l++;
            write(fd2, &tree_temp->g, sizeof(char));
            tree_temp = tree;
            i--;
        }
    }
}
