/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:55
*
*   Name            eraterm.c  --  blank terminal screen
*
*   Description     Blanks the terminal screen 
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

VOID eraterm(attr)
COUNT attr;         /* Attribute to use                             */
    {
    FAST COUNT count=1;
    FAST TEXT *cptr;
    COUNT twidth;
    VOID vcmem();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "eraterm:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    cptr = tscreen;
    twidth = vcterm.cols << 1;
    while(count<=vcterm.cols)
        {
        *(cptr++)=' ';
        *(cptr++)=attr;
        count++;
        }
    count = 1;
    while(count < vcterm.rows)
        {
        vcmem(cptr,tscreen,twidth);
        cptr += twidth;
        count++;
        }
    }

#endif


