/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:51
*
*   Name            erase.c  --  Erase the screen
*
*   Description     Erases the screen with default attributes 
*                   by calling werase() or xerase() the proper attribute.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID ERASE()
    {
    VOID werase();
    VOID xerase();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "erase:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if(wdoctrl->wno_opn && !override)
        werase(wdoctrl->wcurrent,vc.dflt);
    else
#endif
        xerase(normattr);
    }

