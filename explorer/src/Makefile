# define required Macros here

INCLUDE = -I ../include
CC = g++
CFLAGS = -w -g -std=c++14
LIBS =
OBJS = array.o linkedlist.o string.o tree.o util.o main.o
ROOTDIR = ../../

solution: ${OBJS}
	${CC} ${INCLUDE} ${CFLAGS} ${LIBS} ${OBJS} -o $@
	cp $@ ${ROOTDIR}
	-rm -f *.o

.cpp.o:
	${CC} ${CFLAGS} ${INCLUDE} -c $<

clean:
	-rm -f *.o core *.core solution
