/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:15
*
*   Name            wdokey.c  --  set window adjust key
*
*   Description     Sets the window adjust key used in xgetone than allows
*                   the user to real time adjust the window. This function
*                   only sets a global integer.
*
*   Return Value    Returns old wdokey
*
**/

#include <vcstdio.h>

#ifdef WINDOW

COUNT wdokey(ascii)
PFAST COUNT ascii;  /* New window adjust key                        */
    {
    FAST COUNT oldkey;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wdokey:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    oldkey = spkey.wakey;
    spkey.wakey = ascii;
    return(oldkey);
    }

#endif
