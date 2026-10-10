# Huffman C++ Core - Quick Start Guide

## ⚡ 30-Second Setup

```bash
cd cpp_core

# 1. Build
make

# 2. Test
echo "Hello World! Hello World!" > test.txt
./huffman compress test.txt test.huff
./huffman decompress test.huff test_out.txt

# 3. Verify
diff test.txt test_out.txt
```

✓ **Done!** You're ready to compress files.

---

## 🎯 Basic Commands

### Compress a File
```bash
./huffman compress input.txt output.huff
```

### Decompress a File
```bash
./huffman decompress input.huff output.txt
```

### Clean Build
```bash
make clean && make
```

---

## 📂 Project Structure

```
cpp_core/
├── README.md                # Full documentation ← Start here!
├── STRUCTURE.md            # Architecture details
├── QUICKSTART.md           # This file
├── Makefile                # Build configuration
│
├── main.cpp                # Entry point
├── globals.cpp             # Global variables
├── huffman.h               # Core data structures
│
├── utilities.h/cpp         # Helper functions (heap, bits)
├── tree_builder.h/cpp      # Huffman tree operations
├── compression.h/cpp       # Encoding logic
├── decompression.h/cpp     # Decoding logic
│
├── huffman                 # Compiled executable (created by make)
└── *.o                     # Object files (created by make)
```

---

## 🚀 Usage Examples

### Example 1: Simple File
```bash
./huffman compress document.txt document.huff
./huffman decompress document.huff restored.txt
```

### Example 2: Test Different Files
```bash
# Text file
./huffman compress README.md README.huff

# Log file
./huffman compress system.log system.log.huff

# Configuration file
./huffman compress config.json config.json.huff
```

### Example 3: Batch Processing
```bash
for file in *.txt; do
  ./huffman compress "$file" "$file.huff"
done
```

---

## ✅ Testing

### Manual Test
```bash
# Create test file
cat > test.txt << 'EOF'
The quick brown fox jumps over the lazy dog.
Huffman compression works by building a binary tree.
EOF

# Compress & decompress
./huffman compress test.txt test.huff
./huffman decompress test.huff test_out.txt

# Verify
diff test.txt test_out.txt && echo "✓ Works!"
```

### Automated Test
```bash
./test_demo.sh
```

---

## 🔍 How It Works

### Compression Algorithm
1. **Read** input file
2. **Count** character frequencies
3. **Build** Huffman tree (greedy algorithm)
4. **Generate** binary codes for each character
5. **Encode** file using these codes
6. **Write** compressed data to output

### Decompression Algorithm
1. **Read** Huffman tree from compressed file
2. **Reconstruct** the tree
3. **Decode** binary data using the tree
4. **Write** original characters to output

### Time Complexity
- **Compression**: O(n log m)
  - n = file size, m = unique characters
- **Decompression**: O(n)
  - n = file size

---

## 📊 Performance

### Compression Ratios

| File Type | Size | Ratio | Notes |
|-----------|------|-------|-------|
| Small text | <1 KB | -200% | Overhead > savings |
| Random | >1 KB | 0-10% | Low redundancy |
| Text | >10 KB | 30-50% | Good compression |
| Repetitive | >100 KB | 50-70% | Excellent |

**Note**: Small files expand due to tree overhead. Better for larger files.

---

## 🛠️ Build Details

### Rebuild Everything
```bash
make clean
make
```

### Verify Build
```bash
./huffman
# Should show: Usage: ./huffman [compress|decompress] [input_file] [output_file]
```

### Compiler Info
```bash
g++ --version
```

Required: **C++17 or later**

---

## 🎯 File Format

```
Compressed File (.huff)
┌─────────────────────────────────────┐
│ 4 bytes: unique_size                │
├─────────────────────────────────────┤
│ [Repeated for each unique char]     │
│   • 1 byte: character               │
│   • 4 bytes: code length            │
│   • 4 bytes: code (decimal)         │
├─────────────────────────────────────┤
│ 4 bytes: original_char_count        │
├─────────────────────────────────────┤
│ Variable: compressed binary data    │
└─────────────────────────────────────┘
```

---

## 💡 Tips

### Compress Efficiently
```bash
# Text files compress best
./huffman compress large_log.txt large_log.huff

# Monitor compression
ls -lh input.txt output.huff
```

### Batch Compression
```bash
# Compress all txt files
for f in *.txt; do
  ./huffman compress "$f" "$f.huff"
  rm "$f"  # Optional: remove original
done
```

### Verify Integrity
```bash
# After decompression, verify match
./huffman decompress backup.huff backup.txt
diff original.txt backup.txt
```

---

## ❓ Troubleshooting

### "Command not found"
```bash
# Make sure you're in cpp_core directory
cd cpp_core
# Or use full path
./huffman compress ...
```

### "File not found"
```bash
# Use full paths if file is elsewhere
./huffman compress /path/to/file.txt /path/to/output.huff
```

### Build fails
```bash
# Check compiler version
g++ --version  # Need C++17 or later

# Clean and retry
make clean && make
```

### Output file is larger than input
```bash
# This is normal for small files!
# The tree overhead is significant for small data
# For example: 45-byte file → 338-byte compressed
# Try with larger files (>1 KB) for better ratios
```

---

## 🔗 More Information

- **Full README**: [README.md](README.md)
- **Architecture**: [STRUCTURE.md](STRUCTURE.md)
- **Main Project**: [../README.md](../README.md)

---

## 📞 Support

| Issue | Solution |
|-------|----------|
| Compilation error | Run `make clean && make` |
| Segmentation fault | Report with file that caused it |
| Wrong output | Check both files: `diff original output` |
| Large output | Normal for small files, try >1KB files |

---

**Happy Compressing!** 🎉

Built with C++17 • Huffman Coding • Educational Purpose
