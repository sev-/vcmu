/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:35
*
*   Name            dflthlp.c  --  Set pointer to help text
*
*   Description     Set the global variable to point to the current
*                   help text and returns a pointer to the old help
*                   text.
*
*   Return Value    Return pointer to old help text
*
**/

#include <vcstdio.h>

TEXT *dflthlp(str)
PFAST TEXT *str;    /* Pointer to new help text                     */
    {
    FAST TEXT *oldhlp;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "dflthlp:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    oldhlp = hlptxt;
    hlptxt = str;
    return(oldhlp);
    }


