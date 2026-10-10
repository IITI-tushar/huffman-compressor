CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = huffman
BENCHMARK = benchmark
OBJS = main.o globals.o utilities.o tree_builder.o compression.o decompression.o
BENCH_OBJS = benchmark.o globals.o utilities.o tree_builder.o compression.o decompression.o

all: $(TARGET) $(BENCHMARK)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BENCHMARK): $(BENCH_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp huffman.h utilities.h tree_builder.h compression.h decompression.h
	$(CXX) $(CXXFLAGS) -c main.cpp

globals.o: globals.cpp huffman.h
	$(CXX) $(CXXFLAGS) -c globals.cpp

utilities.o: utilities.cpp utilities.h huffman.h
	$(CXX) $(CXXFLAGS) -c utilities.cpp

tree_builder.o: tree_builder.cpp tree_builder.h huffman.h utilities.h
	$(CXX) $(CXXFLAGS) -c tree_builder.cpp

compression.o: compression.cpp compression.h huffman.h
	$(CXX) $(CXXFLAGS) -c compression.cpp

decompression.o: decompression.cpp decompression.h huffman.h utilities.h
	$(CXX) $(CXXFLAGS) -c decompression.cpp

benchmark.o: benchmark.cpp huffman.h utilities.h tree_builder.h compression.h decompression.h
	$(CXX) $(CXXFLAGS) -c benchmark.cpp

clean:
	rm -f $(OBJS) $(BENCH_OBJS) $(TARGET) $(BENCHMARK)

.PHONY: all clean
