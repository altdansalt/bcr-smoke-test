# rules_foreign_cc `make()` runs `make` and `make install` with PREFIX=<install dir>
# and exports CC/CFLAGS from the Bazel C++ toolchain. Slimmed from
# rules_foreign_cc examples/make_simple/code/Makefile (Apache-2.0).
PREFIX ?= install

AR ?= ar
# rules_foreign_cc exports AR from the Bazel C++ toolchain. On Apple platforms that is
# libtool, which takes `-static -o <out>` instead of `rcs <out>`.
ifeq ($(notdir $(AR)),libtool)
ARCHIVE = $(AR) -static -o
else
ARCHIVE = $(AR) rcs
endif

all: libmul.a

mul.o: mul.c mul.h
	$(CC) $(CFLAGS) -c -o mul.o mul.c

libmul.a: mul.o
	$(ARCHIVE) libmul.a mul.o

install: libmul.a
	mkdir -p $(PREFIX)/lib $(PREFIX)/include
	cp libmul.a $(PREFIX)/lib/
	cp mul.h $(PREFIX)/include/

clean:
	rm -f mul.o libmul.a

.PHONY: all install clean
