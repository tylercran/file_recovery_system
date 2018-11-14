# Early attempt at makefile, working but could be better. 

#c files use gcc
CC       = gcc
#c++ files use g++
CXX      = g++
#will compile with debug flag, will later likely need lpthread and such
CPPFLAGS = -g -std=c++11


#defile source files
CSRC = $(wildcard *.C) 

cSRC  = $(wildcard *.c)


#define object files needed, might want to define these manually during
#development
OBJS = $(CSRC:.C=.o) \
       $(cSRC:.c=.o)

#define targes
all: main

main:   $(OBJS) 
	$(CXX) -o $@ $^ 

clean:
	rm -f $(OBJS) main
