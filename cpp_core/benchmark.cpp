#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <chrono>
#include <filesystem>
#include <sys/stat.h>

#include "huffman.h"
#include "utilities.h"
#include "tree_builder.h"
#include "compression.h"
#include "decompression.h"

namespace fs = std::filesystem;

struct BenchmarkResult {
    std::string test_name;
    long file_size;
    double time_ms;
    double throughput_mbps;
};

void print_result(const BenchmarkResult& result) {
    printf("%-30s | Size: %8ld bytes | Time: %8.3f ms | Throughput: %8.2f MB/s\n",
           result.test_name.c_str(), result.file_size, result.time_ms, result.throughput_mbps);
}

long get_file_size(const char* filename) {
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

BenchmarkResult benchmark_compression(const char* input_file, const char* output_file) {
    BenchmarkResult result;
    result.test_name = std::string("Compress: ") + fs::path(input_file).filename().string();

    long input_size = get_file_size(input_file);
    result.file_size = input_size;

    int fd1 = open(input_file, O_RDONLY);
    if (fd1 == -1) {
        std::cerr << "Failed to open input file: " << input_file << std::endl;
        return result;
    }

    // Count frequencies
    char arr[256];
    int freq[256] = {0};
    char c;
    int unique_size = 0;

    while (read(fd1, &c, sizeof(char)) != 0) {
        freq[(unsigned char)c]++;
    }

    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            arr[unique_size] = (char)i;
            unique_size++;
        }
    }

    // Build tree and start compression timing
    minHeapGlobal = createAndBuildMin_Heap(arr, freq, unique_size);
    struct Node* root = buildHuffmanTree(arr, freq, unique_size);

    int fd2 = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 == -1) {
        std::cerr << "Failed to open output file: " << output_file << std::endl;
        close(fd1);
        return result;
    }

    auto start = std::chrono::high_resolution_clock::now();

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

    auto end = std::chrono::high_resolution_clock::now();
    result.time_ms = std::chrono::duration<double, std::milli>(end - start).count();
    result.throughput_mbps = (input_size / 1024.0 / 1024.0) / (result.time_ms / 1000.0);

    close(fd1);
    close(fd2);

    return result;
}

BenchmarkResult benchmark_decompression(const char* input_file, const char* output_file) {
    BenchmarkResult result;
    result.test_name = std::string("Decompress: ") + fs::path(input_file).filename().string();

    long input_size = get_file_size(input_file);
    result.file_size = input_size;

    int fd1 = open(input_file, O_RDONLY);
    if (fd1 == -1) {
        std::cerr << "Failed to open input file: " << input_file << std::endl;
        return result;
    }

    int unique_size = 0;
    read(fd1, &unique_size, sizeof(int));

    ReBuildHuffmanTree(fd1, unique_size);

    int original_size = 0;
    read(fd1, &original_size, sizeof(int));

    int fd2 = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 == -1) {
        std::cerr << "Failed to open output file: " << output_file << std::endl;
        close(fd1);
        return result;
    }

    auto start = std::chrono::high_resolution_clock::now();
    decompressFile(fd1, fd2, original_size);
    auto end = std::chrono::high_resolution_clock::now();

    result.time_ms = std::chrono::duration<double, std::milli>(end - start).count();
    result.throughput_mbps = (input_size / 1024.0 / 1024.0) / (result.time_ms / 1000.0);

    close(fd1);
    close(fd2);

    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./benchmark [compress|decompress] <test_file> [compress|decompress] <test_file> ...\n";
        std::cerr << "Example: ./benchmark compress test_input.txt\n";
        std::cerr << "Example: ./benchmark decompress test_simple.huff\n";
        return 1;
    }

    printf("\n=== Huffman Compression Benchmark ===\n\n");
    printf("%-30s | Size         | Time       | Throughput\n", "Test Name");
    printf("%-30s | %-11s | %-10s | %-10s\n", "", "(bytes)", "(ms)", "(MB/s)");
    printf("%-30s-%-11s-%-10s-%-10s\n", std::string(30, '-').c_str(),
           std::string(11, '-').c_str(), std::string(10, '-').c_str(), std::string(10, '-').c_str());

    for (int i = 1; i < argc; i += 2) {
        if (i + 1 >= argc) break;

        std::string mode = argv[i];
        const char* test_file = argv[i + 1];

        if (mode == "compress") {
            std::string output = std::string(test_file) + ".bench.huff";
            BenchmarkResult result = benchmark_compression(test_file, output.c_str());
            print_result(result);
        } else if (mode == "decompress") {
            std::string output = std::string(test_file) + ".bench.out";
            BenchmarkResult result = benchmark_decompression(test_file, output.c_str());
            print_result(result);
        }
    }

    printf("\n");
    return 0;
}
