# raven - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c raven.c util.c
OBJ = ${SRC:.c=.o}

all: options raven

options:
	@echo raven build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

raven: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f raven ${OBJ} raven-${VERSION}.tar.gz

dist: clean
	mkdir -p raven-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		raven.1 drw.h util.h ${SRC} transient.c raven-${VERSION}
	tar -cf raven-${VERSION}.tar raven-${VERSION}
	gzip raven-${VERSION}.tar
	rm -rf raven-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f raven ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/raven
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < raven.1 > ${DESTDIR}${MANPREFIX}/man1/raven.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/raven.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/raven\
		${DESTDIR}${MANPREFIX}/man1/raven.1

.PHONY: all options clean dist install uninstall
