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
#   Editor Makefile
#

CFLAGS = -I../include 
LIBS = -lvced -lvcdbms -lvc
files = vceditor.o

vceditor: $(files)
	cc $(CFLAGS) -o vceditor $(files) $(LIBS) 
