# C++ Huffman Core - Modular Architecture

## 📁 File Organization

The C++ core has been refactored into a clean, modular structure for better maintainability and code organization.

```
cpp_core/
├── huffman.h              # Central header with core data structures
├── globals.cpp            # Global variable definitions
│
├── utilities.h            # Utility function declarations
├── utilities.cpp          # Heap operations, bit conversion helpers
│
├── tree_builder.h         # Huffman tree construction declarations
├── tree_builder.cpp       # Tree building, code generation, reconstruction
│
├── compression.h          # Compression function declarations
├── compression.cpp        # File encoding with Huffman codes
│
├── decompression.h        # Decompression function declarations
├── decompression.cpp      # File decoding with Huffman tree
│
├── main.cpp               # Entry point and CLI interface
│
├── Makefile               # Build configuration
└── STRUCTURE.md           # This file
```

## 📚 File Descriptions

### `huffman.h` (Data Structures)
**Purpose**: Defines all core data structures and global variables.

**Contains**:
- `Node` struct - Huffman tree node (character, frequency, left/right pointers)
- `Min_Heap` struct - Min-heap container for node management
- `code` struct - Stores generated Huffman codes
- `Tree` struct - Reconstructed tree for decompression
- Global variable declarations (extern)

### `globals.cpp` (Global State)
**Purpose**: Defines all global variables in one place.

**Defines**:
- `codeData`, `front`, `rear` - Linked list of generated codes
- `tree`, `tree_temp`, `t` - Tree nodes for decompression
- `k` - Code counter
- `minHeapGlobal` - Global min-heap reference

### `utilities.h` & `utilities.cpp` (Helper Functions)
**Purpose**: Low-level utility functions for heap and bit operations.

**Functions**:
- `Heapify()` - Maintains min-heap property
- `isSizeOne()` - Checks if heap has one element
- `extractMinFromMin_Heap()` - Extracts minimum frequency node
- `newNode()` - Creates new Huffman tree node
- `insertIntoMin_Heap()` - Adds node to min-heap
- `isLeaf()` - Checks if node is a leaf
- `isroot()` - Checks if tree node is a root
- `convertBinaryToDecimal()` - Converts binary array to decimal
- `convertDecimalToBinary()` - Converts decimal to binary array

### `tree_builder.h` & `tree_builder.cpp` (Huffman Tree)
**Purpose**: Builds and reconstructs Huffman trees.

**Functions**:
- `createAndBuildMin_Heap()` - Creates and heapifies character frequency array
- `buildHuffmanTree()` - Constructs Huffman tree using greedy algorithm
- `printCodesIntoFile()` - Generates codes and writes tree to output file
- `ReBuildHuffmanTree()` - Reconstructs tree from compressed file
- `ExtractCodesFromFile()` - Reads tree data from compressed file

### `compression.h` & `compression.cpp` (Encoding)
**Purpose**: Encodes the input file using generated Huffman codes.

**Functions**:
- `compressFile()` - Reads input, applies codes, writes compressed bits to output

### `decompression.h` & `decompression.cpp` (Decoding)
**Purpose**: Decodes compressed file back to original using reconstructed tree.

**Functions**:
- `decompressFile()` - Reads compressed bits, traverses tree, writes original characters

### `main.cpp` (Entry Point)
**Purpose**: Command-line interface and orchestration.

**Features**:
- Parses command-line arguments
- Opens input/output files
- Coordinates compression/decompression workflow
- Handles frequency table creation
- Error reporting

### `Makefile` (Build Configuration)
**Purpose**: Automated compilation and dependency management.

**Targets**:
- `make` - Builds the huffman executable
- `make clean` - Removes compiled objects and executable

## 🔄 Workflow

### Compression Flow
```
main.cpp
  ↓
[Build frequency table from input]
  ↓
utilities::createAndBuildMin_Heap()
  ↓
tree_builder::buildHuffmanTree()
  ↓
tree_builder::printCodesIntoFile()
  ↓
compression::compressFile()
  ↓
Output: .huff file with tree + compressed data
```

### Decompression Flow
```
main.cpp
  ↓
tree_builder::ReBuildHuffmanTree()
  ↓
decompression::decompressFile()
  ↓
Output: .txt file with original content
```

## 🏗️ Architecture Benefits

✅ **Modularity** - Each file has a single responsibility
✅ **Maintainability** - Easy to locate and fix bugs
✅ **Extensibility** - Add new features without touching existing code
✅ **Testability** - Each module can be tested independently
✅ **Reusability** - Modules can be used in other projects
✅ **Build Efficiency** - Only changed files are recompiled

## 📦 Dependencies

### Internal Dependencies
```
main.cpp
  ├─→ huffman.h (data structures)
  ├─→ utilities.h (helper functions)
  ├─→ tree_builder.h (tree operations)
  ├─→ compression.h (encoding)
  └─→ decompression.h (decoding)

tree_builder.cpp
  ├─→ huffman.h (global vars)
  └─→ utilities.h (Heapify, convertBinaryToDecimal)

compression.cpp & decompression.cpp
  └─→ huffman.h (data structures)
```

### External Dependencies
- `<iostream>` - I/O operations
- `<fcntl.h>`, `<unistd.h>` - File operations
- `<cstdlib>`, `<cstring>` - Standard C operations
- `<vector>` - Dynamic array for heap
- `<algorithm>` - std::swap

## 🔨 Compilation

```bash
# Build everything
make

# Clean build artifacts
make clean

# Rebuild from scratch
make clean && make

# Manual compilation (if needed)
g++ -std=c++17 -Wall -Wextra -O2 -c main.cpp
g++ -std=c++17 -Wall -Wextra -O2 -c globals.cpp
# ... etc for all .cpp files
g++ -std=c++17 -o huffman *.o
```

## 📊 Complexity Analysis

- **Time Complexity (Compression)**: O(n log m) where n = file size, m = unique chars
- **Time Complexity (Decompression)**: O(n) where n = file size
- **Space Complexity**: O(m) for the Huffman tree

## ✨ Future Enhancements

- [ ] Add parallel file processing for large files
- [ ] Implement Arithmetic Coding as alternative
- [ ] Add compression statistics output
- [ ] Support for directory compression
- [ ] Memory-mapped file I/O for huge files

---

**Modular, Clean, Extensible** 💜
