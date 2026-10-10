# Full-Stack Text Compressor (Huffman Coding)

A complete full-stack web application that compresses and decompresses text files using a lossless **Huffman Coding** algorithm. Built with C++ for the core algorithm, Node.js/Express for the REST API backend, SQLite for persistent analytics, and a modern responsive frontend.

## 🚀 Features

- **C++ Core Engine**: Implements greedy Huffman tree building, bit-level encoding/decoding, and binary file stream manipulation
- **REST API Backend**: Express.js server that safely executes C++ binaries as child processes using multer for secure file transfers
- **Persistent Analytics**: SQLite database tracks file metadata and calculates compression ratios over time
- **Lossless Restoration**: Guarantees 100% data integrity during decompression
- **Modern UI**: Clean, responsive interface with real-time compression history

## 🛠️ Tech Stack

| Layer | Technology |
|-------|-----------|
| **Algorithm/Core** | C++17 |
| **Backend** | Node.js, Express.js |
| **Database** | SQLite3 |
| **Frontend** | HTML5, CSS3, Vanilla JavaScript |

## 📁 Project Structure

```
huffman_compression/
├── README.md                 # Project documentation
├── cpp_core/
│   └── huffman.cpp          # C++ Huffman algorithm implementation
├── backend/
│   ├── package.json         # Node.js dependencies
│   ├── database.js          # SQLite database setup
│   ├── server.js            # Express API server
│   ├── uploads/             # Temporary file storage
│   └── history.db           # SQLite database (created on first run)
└── frontend/
    ├── index.html           # HTML interface
    ├── style.css            # Modern UI styling
    └── app.js               # Frontend logic & API integration
```

## ⚙️ How to Run

### Prerequisites
- **C++ Compiler** (g++ with C++17 support)
- **Node.js** (v14 or higher)
- **npm** (comes with Node.js)

### Step 1: Compile the C++ Core

```bash
cd cpp_core
g++ -std=c++17 huffman.cpp -o huffman
cd ..
```

Verify compilation:
```bash
./cpp_core/huffman
```

You should see:
```
Usage: ./huffman [compress|decompress] [input_file] [output_file]
```

### Step 2: Setup the Node.js Backend

```bash
cd backend
npm install
node server.js
```

You should see:
```
Backend running on http://localhost:3000
```

### Step 3: Open the Frontend

Open `frontend/index.html` in your web browser (or use a local server):

```bash
# Using Python (if available)
cd frontend
python -m http.server 8000

# Then visit: http://localhost:8000
```

Or simply double-click `frontend/index.html` to open it in your default browser.

## 🎯 How It Works

### Compression Flow
1. User uploads a `.txt` file via the web interface
2. Backend receives the file and invokes the C++ executable
3. C++ program:
   - Reads the input file
   - Builds a frequency table of characters
   - Constructs a Huffman tree using a min-heap
   - Generates binary codes for each character
   - Encodes the input using these codes
   - Writes compressed data to a `.huff` file
4. File is downloaded to user's machine
5. Metadata is stored in SQLite for analytics

### Decompression Flow
1. User uploads a `.huff` file
2. Backend invokes the C++ executable in decompress mode
3. C++ program:
   - Reads the Huffman tree structure from the compressed file
   - Rebuilds the tree
   - Decodes binary data back to original characters
   - Writes decompressed data to a `.txt` file
4. Original file is fully restored with 0% data loss

## 📊 Example Usage

### Compressing a Text File
```
Original File: document.txt (5 KB)
Compressed File: processed_document.txt.huff (2 KB)
Compression Ratio: 60% reduction
```

### Decompressing a Huffman File
```
Compressed File: processed_document.txt.huff (2 KB)
Restored File: processed_document.txt.huff.txt (5 KB)
Data Loss: 0% (perfect restoration)
```

## 🔍 Algorithm Details

### Huffman Coding
1. **Frequency Analysis**: Count occurrences of each character
2. **Min-Heap Construction**: Create a min-heap of all characters by frequency
3. **Tree Building**: Repeatedly extract two minimum frequency nodes and create a parent node with combined frequency
4. **Code Generation**: Traverse tree from root to leaves; left = 0, right = 1
5. **Encoding**: Replace characters with their binary codes
6. **Decoding**: Traverse tree using binary codes to reconstruct original text

### Time Complexity
- Compression: **O(n log m)** where n = file size, m = unique characters
- Decompression: **O(n)** where n = file size

### Space Complexity
- **O(m)** for the Huffman tree where m = unique characters

## 📈 Database Schema

```sql
CREATE TABLE compression_history (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    filename TEXT,
    action TEXT,
    original_size INTEGER,
    final_size INTEGER,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);
```

## 🐛 Troubleshooting

### "Backend running on http://localhost:3000" but frontend shows error
- Ensure backend server is running (`node server.js` in the backend folder)
- Check that port 3000 is not in use

### C++ compilation fails
```bash
# Try with explicit C++17 flag
g++ -std=c++17 huffman.cpp -o huffman

# Or upgrade your compiler
sudo apt-get update && sudo apt-get install build-essential
```

### "Connection error" message on frontend
- Verify backend is running
- Check browser console (F12 → Console) for CORS errors
- Ensure `http://localhost:3000` is accessible

### Files not being processed
- Check that `cpp_core/huffman` executable exists and is executable
- Verify file permissions: `chmod +x cpp_core/huffman`

## 📝 Notes

- Maximum file size is limited by available RAM (algorithm loads entire file into memory)
- Works best with text files (`.txt`, `.csv`, `.json`, etc.)
- Binary files may not compress well due to lower character redundancy
- Compression ratio varies based on text repetition and entropy

## 🎓 Educational Value

This project demonstrates:
- **Data Structures**: Binary trees, min-heaps, linked lists
- **Algorithms**: Greedy algorithms, tree traversal, bit manipulation
- **Systems Programming**: File I/O, binary encoding, memory management
- **Full-Stack Development**: Backend APIs, database integration, frontend state management
- **Process Management**: Executing external binaries from Node.js

## 📄 License

This project is provided as-is for educational purposes.

---

**Built with 💜 for learning Data Structures & Algorithms**
