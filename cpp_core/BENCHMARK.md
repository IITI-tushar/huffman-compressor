# Huffman Compression Benchmarks

Simple benchmarking tool to measure compression/decompression performance.

## Building

```bash
make benchmark
```

This builds the `benchmark` binary. Use `make all` to build both the main huffman tool and the benchmark.

## Running Benchmarks

The benchmark tool accepts alternating mode and file arguments:

```bash
./benchmark [compress|decompress] <file> [compress|decompress] <file> ...
```

### Compression Benchmark

```bash
./benchmark compress test_simple.txt
./benchmark compress test_repetitive.txt
```

Output:
- **Test Name**: Descriptive name of the test
- **Size**: Input file size in bytes
- **Time**: Elapsed time in milliseconds
- **Throughput**: Processing speed in MB/s

### Decompression Benchmark

```bash
./benchmark decompress test_simple.huff
./benchmark decompress test_repetitive.huff
```

### Multiple Tests

Run multiple benchmarks in one command:

```bash
./benchmark compress test_simple.txt compress test_repetitive.txt decompress test_simple.huff decompress test_repetitive.huff
```

## Example Output

```
=== Huffman Compression Benchmark ===

Test Name                      | Size         | Time       | Throughput
                               | (bytes)     | (ms)       | (MB/s)    
----------------------------------------------------------------
Compress: test_simple.txt      | Size:       45 bytes | Time:    0.379 ms | Throughput:     0.11 MB/s
Compress: test_repetitive.txt  | Size:     1500 bytes | Time:    4.534 ms | Throughput:     0.32 MB/s
```

## Notes

- Benchmarks include I/O time (reading input and writing output)
- Small files have overhead; throughput is more meaningful for larger files
- Output files are created with `.bench.huff` (compression) or `.bench.out` (decompression) suffixes
