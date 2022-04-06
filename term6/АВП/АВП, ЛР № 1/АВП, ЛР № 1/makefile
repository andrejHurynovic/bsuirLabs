#	Makefile
CC = g++
VERSION = -std=c++20

#Project Name
PROJECT_NAME := labwork1
OUTPATH = build

OUTPATH := $(abspath $(OUTPATH))
BASEDIR := $(abspath ./)

HEADER = matrix/matrix.hpp
CFLAGS = -IHEADER -Rpass=loop-vectorize -mavx2 -DNDEBUG -O3

start:
	$(CC) $(VERSION) $(CFLAGS) main.cpp -o $(OUTPATH)/main
	$(OUTPATH)/main
