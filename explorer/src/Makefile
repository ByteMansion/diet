# Define required macros here

OBJS = array.o linkedlist.o string.o tree.o util.o main.o
CFLAGS = -Wall -g -std=c++11
CC = clang++
INCLUDE = -I ../include
LIBS = -lm

.o.cpp:
	${CC} ${CFLAGS} ${INCLUDE} -c $<

solution: ${OBJS}
	${CC} ${CFLAGS} ${INCLUDE} -o $@ ${OBJS} ${LIBS}

clean:
	-rm -f *.o core *.core


