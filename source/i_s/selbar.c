/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:58
*
*   Name            selbar.c --  Select bar
*
*   Description     Puts length of desired attribute a
*                   specified location
*                   
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID selbar(wptr,row,col,attr,width)
WPTR wptr;
COUNT row,attr,width;
    {
    VOID wat();
    COUNT wputattr();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "selbar:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    wat(wptr,row,col);
    wputattr(wptr,attr,width);
    }
#endif


