/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:20
*
*   Name            xeraeos.c  --  eXtended erase end of screen
*
*   Description     Erases from the current row and column (vcrow
*                   vccol) to the end of the screen with attr.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID xeraeos(attr)
COUNT attr;         /* Attribute to use                             */
    {
#ifdef IBM
    FAST COUNT row;
#endif
#ifdef OS2
    FAST COUNT row;
#endif
    VOID erateos();
    VOID weraeos();
    VOID xeraeol();
    VOID scrollup();
    VOID term_at();
    VOID flipattr();
    VOID dist_str();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xeraeos:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if(wdoctrl->wno_opn && !override)
        weraeos(wdoctrl->wcurrent,attr);
    else
        {
#endif
#ifdef IBM
#ifdef TERMINAL
        if(vctio != 5)
            {
#endif
            xeraeol(attr);
            if(vcrow < vcterm.rows-1)
               row = vcrow+1;
            else
                row = vcrow;
            scrollup(row,0,vcterm.rows-1,vcterm.cols-1,0,attr);
#ifdef TERMINAL
            }
        else
            {
            term_at(vcrow,vccol);
            flipattr(attr);
            dist_str(vcterm.cd,0);
#ifdef WINDOW
            erateos(attr);
#endif
            }
#endif
#endif
#ifdef TERMONLY
        term_at(vcrow,vccol);
        flipattr(attr);
        dist_str(vcterm.cd,0);
#ifdef WINDOW
        erateos(attr);
#endif
#endif
#ifdef OS2
#ifdef TERMINAL
        if(vctio != 5)
            {
#endif
            xeraeol(attr);
            if(vcrow < vcterm.rows-1)
               row = vcrow+1;
            else
                row = vcrow;
            scrollup(row,0,vcterm.rows-1,vcterm.cols-1,-1,attr);
#ifdef TERMINAL
            }
        else
            {
            term_at(vcrow,vccol);
            flipattr(attr);
            dist_str(vcterm.cd,0);
#ifdef WINDOW
            erateos(attr);
#endif
            }
#endif
#endif
#ifdef WINDOW
        }
#endif
    }


