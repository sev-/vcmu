#  
#
#   Vitamin C Multi-User version 1.%R%
#   Copyright (c) 1985-1990
#   Creative Programming Consultants, Inc.
#   P.O. Box 112097
#   Carrollton, Texas  75006
#   (214) 416-6447
#   ALL RIGHTS RESERVED
#   Last Modification: .%L% on %G% at %U%
#
#
#   Edit routines Makefile
#

LDIR = /usr/lib/
LIBNAME = libvc
STD = -I../include -K -O
VCED = -NT VCED_TEXT

#   
#   For computers with one or no memory models
#

all:
	$(MAKE) "V = $(LIBNAME)ed.a" "CFLAGS = $(STD)" vced

#   
#   For computers with memory models
#

models: large medium small

large:
	$(MAKE) "V = L$(LIBNAME)ed.a" "CFLAGS = -Ml $(STD)" svced

medium:
	$(MAKE) "V = M$(LIBNAME)ed.a" "CFLAGS = -Mm $(STD)" svced

small:
	$(MAKE) "V = S$(LIBNAME)ed.a" "CFLAGS = -Ms -i $(STD)" svced

#   
#   For computers with memory models requiring ranlib
#

rmodels: rlarge rmedium rsmall

rlarge:
	$(MAKE) "V = L$(LIBNAME)ed.a" "CFLAGS = -Ml $(STD)" svced
	ranlib L$(LIBNAME)ed.a

rmedium:
	$(MAKE) "V = M$(LIBNAME)ed.a" "CFLAGS = -Mm $(STD)" svced
	ranlib M$(LIBNAME)ed.a

rsmall:
	$(MAKE) "V = S$(LIBNAME)ed.a" "CFLAGS = -Ms -i $(STD)" svced
	ranlib S$(LIBNAME)ed.a

vced:
	$(CC) -c $(CFLAGS) *.c
	-rm -r edit.cmp
	mkdir edit.cmp
	-mv *.o edit.cmp
	cd edit.cmp; ar cr $(V) `lorder *.o | tsort`; mv $(V) ..

svced:
	$(CC) -c $(CFLAGS) $(VCED) *.c
	-rm -r edit.cmp
	mkdir edit.cmp
	-mv *.o edit.cmp
	cd edit.cmp; ar cr $(V) `lorder *.o | tsort`; mv $(V) ..

