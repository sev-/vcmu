/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:21
*
*   Name            xerase.c  --  Erase screen with attribute
*
*   Description     erases the screen with attribute {attribute}
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID xerase(attr)
COUNT attr;         /* Attribute to use                             */
    {
    VOID werase();
    VOID scrollup();
    VOID flipattr();
    VOID dist_str();
    VOID eraterm();
    VOID at();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xerase:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if(wdoctrl->wno_opn && !override)
        werase(wdoctrl->wcurrent,attr);
    else
        {
#endif
#ifdef IBM
#ifdef TERMINAL
        if(vctio != 5)
#endif
            scrollup(0,0,vcterm.rows-1,vcterm.cols-1,0,attr);
#ifdef TERMINAL
        else
            {
            flipattr(attr);
            dist_str(vcterm.cl,0);
#ifdef WINDOW
            eraterm(attr);
#endif
            }
#endif
#endif
#ifdef TERMONLY
        flipattr(attr);
        dist_str(vcterm.cl,0);
#ifdef WINDOW
        eraterm(attr);
#endif
#endif
#ifdef WINDOW
        }
#endif
#ifdef OS2
#ifdef TERMINAL
        if(vctio != 5)
#endif
            scrollup(0,0,vcterm.rows-1,vcterm.cols-1,-1,attr);
#ifdef TERMINAL
        else
            {
            flipattr(attr);
            dist_str(vcterm.cl,0);
#ifdef WINDOW
            eraterm(attr);
#endif
            }
#endif
#endif
    at(0,0);
    }



