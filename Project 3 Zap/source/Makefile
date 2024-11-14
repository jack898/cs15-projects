###
### Makefile for Zap project
### Zap is a program to compress and decompress ASCII text files.
###
### Author:  Jack Burton jburto05
### Date: 11/11/2023


MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

zap: HuffmanCoder.o HuffmanTreeNode.o BinaryIO.o main.o ZapUtil.o
	$(CXX) $(LDFLAGS) -o zap HuffmanCoder.o HuffmanTreeNode.o BinaryIO.o \
	main.o ZapUtil.o

HuffmanCoder.o: HuffmanCoder.h HuffmanTreeNode.o BinaryIO.o ZapUtil.o
	$(CXX) $(CXXFLAGS) -c HuffmanCoder.cpp

unit_test: unit_test_driver.o HuffmanCoder.o ZapUtil.o HuffmanTreeNode.o \
	BinaryIO.o
	$(CXX) $(CXXFLAGS) $^

main.o: HuffmanCoder.o HuffmanTreeNode.o BinaryIO.o ZapUtil.o
	$(CXX) $(CXXFLAGS) -c main.cpp;

# remove object code to allow recompiling (not wildcard * because don't want
# to remove provided .o files)
clean: 
	rm HuffmanCoder.o
