prefix=/usr
BINDIR=${prefix}/bin
LIBDIR=${prefix}/lib
INCDIR=${prefix}/include

HDRS=matt.h
SRC=matt.c
OBJS=matt.o
TARG=libmatt.so

CC=clang
.if make(release)
CFLAGS=-I./ -fpic -Weverything -Wno-unused-parameter -std=c99 -O0 -D_FORTIFY_SOURCE=2 -fstack-protector-all
.else
CFLAGS=-I./ -fpic -Weverything -Wno-unused-parameter -std=c99 -ggdb3 -O0 -fstack-protector-all -D_FORTIFY_SOURCE=2
.endif
LDFLAGS=-fpic -s -Wl,-z,now -Wl,-z,relro 
release: all

install: all
	sudo cp -f ./libmatt.so ${LIBDIR}
	sudo chmod 755 ${LIBDIR}/libmatt.so
	sudo cp -f ./matt.h ${INCDIR}
	sudo chmod 755 ${INCDIR}/matt.h

all: ${TARG}
 
${TARG}: ${OBJS}
		$(CC) ${LDFLAGS} -shared -o ${.TARGET} ${.ALLSRC}

${OBJS}: ${SRC}
		$(CC) ${.ALLSRC} $(CFLAGS) -c -o ${.TARGET}

${SRC}: ${HDRS}

clean:
		rm -f *.o core core.* *.core
