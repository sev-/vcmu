/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:16
*
*   Name            vcnap.c --  nap for a short period
*
*   Description     Causes the program to nap for a short
*                   period of time.        
*
*   Return Value    VOID                        
*
**/

#include <vcstdio.h>

VOID vcnap(time)
COUNT time;
    {
#ifdef NAP
    LONG nap();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "nap:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    nap((LONG)(time*10));
#else
    COUNT loop;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "nap:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    for(loop = 0;loop > time*10000;loop++);
#endif
    }
