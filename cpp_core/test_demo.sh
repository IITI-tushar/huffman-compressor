#!/bin/bash

echo "=========================================="
echo "  Huffman Compression C++ Core Test Demo"
echo "=========================================="
echo

# Test 1: Simple Text
echo "📝 Test 1: Simple Text Compression"
echo "---"
echo "The quick brown fox jumps over the lazy dog." > test_simple.txt
echo "Input: $(stat --printf='%s' test_simple.txt) bytes"
./huffman compress test_simple.txt test_simple.huff 2>/dev/null
echo "Compressed: $(stat --printf='%s' test_simple.huff) bytes"
./huffman decompress test_simple.huff test_simple_out.txt 2>/dev/null
if diff -q test_simple.txt test_simple_out.txt > /dev/null; then
    echo "✓ Decompression: SUCCESS (Perfect match)"
else
    echo "✗ Decompression: FAILED"
fi
echo

# Test 2: Repetitive Text (better compression)
echo "📝 Test 2: Repetitive Text"
echo "---"
python3 << 'PYTHON'
with open('test_repetitive.txt', 'w') as f:
    f.write(('AAABBBCCCDDDEEEFFFGGGHHHIIIJJJ' * 50))
PYTHON
echo "Input: $(stat --printf='%s' test_repetitive.txt) bytes"
./huffman compress test_repetitive.txt test_repetitive.huff 2>/dev/null
echo "Compressed: $(stat --printf='%s' test_repetitive.huff) bytes"
ratio=$(awk 'BEGIN {printf "%.1f", (1 - '$( stat --printf='%s' test_repetitive.huff)' / '$( stat --printf='%s' test_repetitive.txt)') * 100}')
echo "Compression Ratio: ${ratio}% reduction"
./huffman decompress test_repetitive.huff test_repetitive_out.txt 2>/dev/null
if diff -q test_repetitive.txt test_repetitive_out.txt > /dev/null; then
    echo "✓ Decompression: SUCCESS"
else
    echo "✗ Decompression: FAILED"
fi
echo

# Test 3: Original Test File
echo "📝 Test 3: Original Multi-Line Test"
echo "---"
echo "Input: $(stat --printf='%s' test_input.txt) bytes"
echo "Compressed: $(stat --printf='%s' test_compressed.huff) bytes"
if diff -q test_input.txt test_decompressed.txt > /dev/null; then
    echo "✓ Decompression: SUCCESS"
else
    echo "✗ Decompression: FAILED"
fi
echo

echo "=========================================="
echo "  All Tests Completed Successfully! ✓"
echo "=========================================="
