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
#   Unix/Xenix Makefile
#

LDIR = /usr/lib/
LIBNAME = libvc
STD = -I../include -K -O
VCDBMS = -NT VCDBMS_TEXT

#   
#   For computers with one or no memory models
#

all:
	$(MAKE) "V = $(LIBNAME)dbms.a" "CFLAGS = $(STD)" vcdbms

#   
#   For computers with memory models
#

models: large medium small

large:
	$(MAKE) "V = L$(LIBNAME)dbms.a" "CFLAGS = -Ml $(STD)" svcdbms

medium:
	$(MAKE) "V = M$(LIBNAME)dbms.a" "CFLAGS = -Mm $(STD)" svcdbms

small:
	$(MAKE) "V = S$(LIBNAME)dbms.a" "CFLAGS = -Ms -i $(STD)" svcdbms

#   
#   For computers with memory models requiring ranlib
#

rmodels: rlarge rmedium rsmall

rlarge:
	$(MAKE) "V = L$(LIBNAME)dbms.a" "CFLAGS = -Ml $(STD)" svcdbms
	ranlib L$(LIBNAME)dbms.a

rmedium:
	$(MAKE) "V = M$(LIBNAME)dbms.a" "CFLAGS = -Mm $(STD)" svcdbms
	ranlib M$(LIBNAME)dbms.a

rsmall:
	$(MAKE) "V = S$(LIBNAME)dbms.a" "CFLAGS = -Ms -i $(STD)" svcdbms
	ranlib S$(LIBNAME)dbms.a

vcdbms:
	$(CC) -c $(CFLAGS) *.c
	-rm -r dbms.cmp
	mkdir dbms.cmp
	mv *.o dbms.cmp
	cd dbms.cmp; ar cr $(V) `lorder *.o | tsort`; mv $(V) ..

svcdbms:
	$(CC) -c $(CFLAGS) $(VCDBMS) *.c
	-rm -r dbms.cmp
	mkdir dbms.cmp
	-mv *.o dbms.cmp
	cd dbms.cmp; ar cr $(V) `lorder *.o | tsort`; mv $(V) ..

