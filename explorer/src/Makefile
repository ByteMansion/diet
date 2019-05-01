# define required Macros here

INCLUDE = -I ../include
CC = g++
CFLAGS = -wall -g -std=c++11
LIBS = -lm
OBJS = array.o linkedlist.o string.o tree.o util.o main.o

solution: ${OBJS}
	${CC} ${INCLUDE} ${CFLAGS} ${LIBS} -o $@

.cpp.o:
	${CC} ${CFLAGS} ${INCLUDE} -c $<

clean:
	-rm -f *.o core *.core
