CXX = g++

RM = rm -f

SRC = main.c \
      utils.C 

OBJS = main.o \
       utils.o

all: makeIMG

makeIMG: $(OBJS)
	$(CXX) -o makeIMG $(OBJS) 

main.o: main.c utils.C utils.H
	$(CXX) -c main.c

utils.o: utils.C utils.H
	$(CXX) -c utils.C
clean: 
	$(RM) $(OBJS) makeIMG errorLog

