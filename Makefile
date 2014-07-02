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
<<<<<<< HEAD
CFLAGS='-I./ -fpic -Weverything -Wno-unused-parameter -std=c99 -O0 -D_FORTIFY_SOURCE=2 -fstack-protector-all'
=======
CFLAGS=-I./ -fpic -Weverything -Wno-unused-parameter -std=c99 -O0 -D_FORTIFY_SOURCE=2 -fstack-protector-all
>>>>>>> d213c89b1b672d6a4d714f3d9c9a25adaa7354c7
.else
CFLAGS='-I./ -fpic -Weverything -Wno-unused-parameter -std=c99 -ggdb3 -O0 -fstack-protector-all -D_FORTIFY_SOURCE=2'
.endif
<<<<<<< HEAD
LDFLAGS=-fpic -v #-s
# -Wl,-z,now -Wl,-z,relro 
=======
LDFLAGS=-fpic -s -Wl,-z,now -Wl,-z,relro 
>>>>>>> d213c89b1b672d6a4d714f3d9c9a25adaa7354c7
release: all

install: all
	sudo cp -f ./libmatt.so ${LIBDIR}
	sudo chmod 755 ${LIBDIR}/libmatt.so
	sudo cp -f ./matt.h ${INCDIR}
	sudo chmod 755 ${INCDIR}/matt.h

all: ${TARG}
 
${TARG}: ${OBJS}
<<<<<<< HEAD
		$(CC) ${LDFLAGS} --shared -o ${.TARGET} ${.ALLSRC}
=======
		$(CC) ${LDFLAGS} -shared -o ${.TARGET} ${.ALLSRC}
>>>>>>> d213c89b1b672d6a4d714f3d9c9a25adaa7354c7

${OBJS}: ${SRC}
		$(CC) ${.ALLSRC} $(CFLAGS) -c -o ${.TARGET}

${SRC}: ${HDRS}

clean:
		rm -f *.o core core.* *.core
