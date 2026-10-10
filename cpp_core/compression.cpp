#include "compression.h"
#include <unistd.h>

void compressFile(int fd1, int fd2, unsigned char a) {
    char n;
    int h = 0, i;
    while (read(fd1, &n, sizeof(char)) != 0) {
        rear = front;
        while (rear->k != n && rear->p != NULL) {
            rear = rear->p;
        }
        if (rear->k == n) {
            for (i = 0; i < rear->l; i++) {
                if (h < 7) {
                    if (rear->code_arr[i] == 1) {
                        a++;
                        a = a << 1;
                        h++;
                    }
                    else if (rear->code_arr[i] == 0) {
                        a = a << 1;
                        h++;
                    }
                }
                else if (h == 7) {
                    if (rear->code_arr[i] == 1) {
                        a++;
                        h = 0;
                    }
                    else {
                        h = 0;
                    }
                    write(fd2, &a, sizeof(char));
                    a = 0;
                }
            }
        }
    }
    for (i = 0; i < 7 - h; i++) {
        a = a << 1;
    }
    write(fd2, &a, sizeof(char));
}
