#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <string>

#include "huffman.h"
#include "utilities.h"
#include "tree_builder.h"
#include "compression.h"
#include "decompression.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: ./huffman [compress|decompress] [input_file] [output_file]\n";
        return 1;
    }

    string mode = argv[1];
    int fd1 = open(argv[2], O_RDONLY);
    int fd2 = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd1 == -1 || fd2 == -1) {
        perror("File Open Failed");
        exit(1);
    }

    if (mode == "compress") {
        char arr[256];
        int freq[256] = {0};
        char c;
        int unique_size = 0;

        lseek(fd1, 0, SEEK_SET);
        while (read(fd1, &c, sizeof(char)) != 0) {
            freq[(unsigned char)c]++;
        }

        for (int i = 0; i < 256; i++) {
            if (freq[i] > 0) {
                arr[unique_size] = (char)i;
                unique_size++;
            }
        }

        minHeapGlobal = createAndBuildMin_Heap(arr, freq, unique_size);
        struct Node* root = buildHuffmanTree(arr, freq, unique_size);

        write(fd2, &unique_size, sizeof(int));

        int codesArr[MAX] = {0};
        printCodesIntoFile(fd2, root, codesArr, 0);

        int original_char_count = 0;
        lseek(fd1, 0, SEEK_SET);
        while (read(fd1, (char*)&c, sizeof(char)) != 0) {
            original_char_count++;
        }
        write(fd2, &original_char_count, sizeof(int));

        lseek(fd1, 0, SEEK_SET);
        compressFile(fd1, fd2, 0);

        cerr << "Compression successful.\n";
    }
    else if (mode == "decompress") {
        lseek(fd1, 0, SEEK_END);
        int fileSize = lseek(fd1, 0, SEEK_CUR);
        lseek(fd1, 0, SEEK_SET);

        int unique_size = 0;
        read(fd1, &unique_size, sizeof(int));

        ReBuildHuffmanTree(fd1, unique_size);

        int original_size = 0;
        read(fd1, &original_size, sizeof(int));

        decompressFile(fd1, fd2, original_size);

        cerr << "Decompression successful.\n";
    }
    else {
        cerr << "Invalid mode. Use 'compress' or 'decompress'.\n";
        return 1;
    }

    close(fd1);
    close(fd2);
    return 0;
}
