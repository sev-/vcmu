#  
#
#   Vitamin C Multi-User version 1.6
#   Copyright (c) 1985-1990
#   Creative Programming Consultants, Inc.
#   P.O. Box 112097
#   Carrollton, Texas  75006
#   (214) 416-6447
#   ALL RIGHTS RESERVED
#   Last Modification: .%L% on %G% at %U%
#
#
#   Primary Library Makefile
#
#

LDIR = /usr/lib/
LIBNAME = libvc
STD = -I../../include -K -O
ONE = -NT TC1_TEXT
TWO = -NT TC2_TEXT
THREE = -NT TC3_TEXT
FOUR = -NT TC4_TEXT
TCM = -NT TCM_TEXT

#   
#   For computers with one or no memory models
#

all:
	$(MAKE) "V = $(LIBNAME).a" "CFLAGS = $(STD)" vcfiles

#   
#   For computers with memory models
#

models: large medium small

large:
	$(MAKE) "V = L$(LIBNAME).a" "CFLAGS = -Ml $(STD)" svcfiles

medium:
	$(MAKE) "V = M$(LIBNAME).a" "CFLAGS = -Mm $(STD)" svcfiles

small:
	$(MAKE) "V = S$(LIBNAME).a" "CFLAGS = -Ms -i $(STD)" vcfiles

#   
#   For computers with memory models requiring ranlib
#

rmodels: rlarge rmedium rsmall

rlarge:
	$(MAKE) "V = L$(LIBNAME).a" "CFLAGS = -Ml $(STD)" svcfiles
	ranlib L$(LIBNAME).a

rmedium:
	$(MAKE) "V = M$(LIBNAME).a" "CFLAGS = -Mm $(STD)" svcfiles
	ranlib M$(LIBNAME).a

rsmall:
	$(MAKE) "V = S$(LIBNAME).a" "CFLAGS = -Ms -i $(STD)" vcfiles
	ranlib S$(LIBNAME).a

vcfiles:
	cd a_h; $(CC) -c $(CFLAGS) *.c
	cd i_s; $(CC) -c $(CFLAGS) *.c
	cd t_v; $(CC) -c $(CFLAGS) *.c
	cd w_z; $(CC) -c $(CFLAGS) *.c
	cd vcm; $(CC) -c $(CFLAGS) *.c
	-rm -r vc.cmp
	mkdir vc.cmp
	mv a_h/*.o vc.cmp
	mv i_s/*.o vc.cmp
	mv t_v/*.o vc.cmp
	mv w_z/*.o vc.cmp
	mv vcm/*.o vc.cmp
	cd vc.cmp; ar cr $(V) `lorder *.o | tsort`; mv $(V) ..

svcfiles:
	cd a_h; $(CC) -c $(CFLAGS) $(ONE) *.c
	cd i_s; $(CC) -c $(CFLAGS) $(TWO) *.c
	cd t_v; $(CC) -c $(CFLAGS) $(THREE) *.c
	cd w_z; $(CC) -c $(CFLAGS) $(FOUR) *.c
	cd vcm; $(CC) -c $(CFLAGS) $(TCM) *.c
	-rm -r vc.cmp
	mkdir vc.cmp
	mv a_h/*.o vc.cmp
	mv i_s/*.o vc.cmp
	mv t_v/*.o vc.cmp
	mv w_z/*.o vc.cmp
	mv vcm/*.o vc.cmp
	cd vc.cmp; ar cr $(V) `lorder *.o | tsort`; mv $(V) ..


