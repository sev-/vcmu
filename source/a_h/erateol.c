/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:52
*
*   Name            erateol.c  --  Erase end of line
*
*   Description     Erases to the end of line of terminal screen
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

VOID erateol(attr)
COUNT attr;         /* Attribute to use on erased area              */
    {
    TEXT *sptr;
    COUNT twidth,count;
    twidth = vcterm.cols << 1;
    sptr = tscreen+(vcrow*twidth)+(vccol << 1);
    count=vccol;
    while(count < vcterm.cols)
        {
        *(sptr++)=' ';
        *(sptr++)=attr;
        count++;
        }
    }

#endif


