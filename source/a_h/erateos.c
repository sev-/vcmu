/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:54
*
*   Name            erateos.c  --  erase end of terminal screen
*
*   Description     Erases from the current row and column (vcrow
*                   vccol) to the end of the terminal screen with attr.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

VOID erateos(attr)
COUNT attr;         /* Attribute to use on blanked area             */
    {
    TEXT *sptr,*ptr;
    COUNT twidth,count=1;
    VOID erateol();
    VOID vcmem();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "erateos:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    twidth = vcterm.cols << 1;
    erateol(attr);
    if(vcrow < vcterm.rows-1)
        {
        ptr = sptr = tscreen+((vcrow+1)*twidth);
        while(count<=vcterm.cols)
            {
            *(sptr++)=' ';
            *(sptr++)=attr;
            count++;
            }
        count = vcrow+2;
        while(count < vcterm.rows)
            {
            vcmem(sptr,ptr,twidth);
            sptr += twidth;
            count++;
            }
        }
    }

#endif


