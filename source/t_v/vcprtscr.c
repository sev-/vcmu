/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:37
*
*   Name            vcprtscr.c -- Print screen function
* 
*   Description     This is a print screen function it prints the
*                   screen to a file
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID vcprtscr()
    {
    TEXT *wimage, *wmemloc();
    COUNT wrow,wcol;
    COUNT prow=0,pcol=0;
    VOID vcprtchr();
    COUNT vcprtfls();
#ifdef VCDEBUG
    tcdebug = (TEXT *) "vcprtscr:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef TERMINAL
    wimage = tscreen;
#else
    wimage = wscreen;
#endif
    wrow = vcterm.rows;
    wcol = vcterm.cols;
    vcprtchr('\n');
    while( prow < wrow )
        {
        while( pcol < wcol )
            {
            vcprtchr(*wimage);
            wimage++;
            wimage++;
            pcol++;
            }
        vcprtchr('\n');
        pcol=0;
        prow++;
        }
    vcprtfls();
    }


