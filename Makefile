prefix=/usr/local
BINDIR=${prefix}/bin
LIBDIR=${prefix}/lib
INCDIR=${prefix}/include

HDRS=matt.h
SRC=matt.c
OBJS=matt.o
TARG=libmatt.so

CC=clang
CFLAGS=-I./ -fpic -Weverything -Wno-unused-parameter -std=c99 -ggdb3 -O0 -v
LDFLAGS=-s

install: all
	sudo cp -f ./libmatt.so ${LIBDIR}
	sudo chmod 755 ${LIBDIR}/libmatt.so
	sudo cp -f ./matt.h ${INCDIR}
	sudo chmod 755 ${INCDIR}/matt.h


all: ${TARG}
 
${TARG}: ${OBJS}
		$(CC) -shared -fpic -o ${.TARGET} ${.ALLSRC}

${OBJS}: ${SRC}
		$(CC) ${.ALLSRC} $(CFLAGS) -c -o ${.TARGET}

${SRC}: ${HDRS}

clean:
		rm -f *.o core core.* *.core
