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
CC=qcl
CFLAGS = -I../include -O -AL
LIBS = ..\source\lvc.lib

all: vcdemo testattr vcmdemo vccolor vcsample cookdemo

vcdemo testattr vcmdemo vccolor vcsample cookdemo: $$@.c
	$(CC) $(CFLAGS) -o $@ $@.c $(LIBS)


