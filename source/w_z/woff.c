/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:50
*
*   Name            woff.c  --  Turns refresh off
*
*   Description     Sets a global variable that turns refresh off
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID woff()
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "woff:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    wdoctrl->wfreeze = 1;
    }

#endif


