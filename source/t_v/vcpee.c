/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:24
*
*   Name            vcpee.c  --  Start buffer
*
*   Description     This starts terminal buffering
*                   
*   Return Value    Returns 0 if buffer already started and
*                   True(1) if you started buffer.  Saves the
*                   status of the cursor in curon so can be 
*                   reset.
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

TEXT *tbufstart = NULLTEXT;
COUNT vcbufsize = SCRNBUFSIZ;

COUNT vcpee()
    {
    TEXT *vcalloc();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcpee:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(bufon)
        return(0);
    if(tbufstart == NULLTEXT)
        {
        while((termbuf = vcalloc(vcbufsize,sizeof(TEXT),vcdebug)) == NULLTEXT)
            vcbufsize = vcbufsize / 2;
        tbufptr = termbuf;
        tbufend = termbuf + vcbufsize - 6;
        tbufstart = tbufptr;
        }
    else
        tbufptr = tbufstart;
    bufon++;
    return(1);
    }
#endif


