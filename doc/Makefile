# Define required macros here

OBJS = main.o array.o linkedlist.o string.o tree.o util.o
CFLAGS = -Wall -g -cpp11
CC = g++
INCLUDE = -I "./explorer/include"
LIBS = -lm

solution: ${OBJS}
	$(CC) ${CFLAGS} ${INCLUDE} -o $@ ${OBJS} ${LIBS}

clean:
	-rm -f *.o core *.core

.cpp.o:
	${CC} ${CFLAGS} ${INCLUDE} -c $<

 
