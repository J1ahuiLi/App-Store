CC		= g++

CFLAGS		= -g -std=c++14

all: bst.cc hash.cc heap.cc main.cc prime.cc bst.h defn.h defnx.h hash.h heap.h prime.h
	$(CC) $(CFLAGS) -o AppStore bst.cc hash.cc heap.cc main.cc prime.cc
