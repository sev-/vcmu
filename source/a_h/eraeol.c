/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:48
*
*   Name            eraeol.c  --  Erase end of line
*
*   Description     Erases to the end of line with default
*                   attributes by calling weraeol() or xeraeol()
*                   the proper attribute.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID eraeol()
    {
    VOID xeraeol();
    VOID weraeol();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "eraeol:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if(wdoctrl->wno_opn && !override)
        weraeol(wdoctrl->wcurrent,vc.dflt);
    else
#endif
        xeraeol(normattr);
    }


