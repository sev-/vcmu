/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:18
*
*   Name            xeraeol.c  --  Erase end of line
*
*   Description     Erases to the end of line with attributes
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID xeraeol(attr)
COUNT attr;         /* Attribute to use on erase                    */
    {
    VOID weraeol();
    VOID scrollup();
    VOID term_at();
    VOID flipattr();
    VOID dist_str();
    VOID erateol();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xeraeol:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if(wdoctrl->wno_opn && !override)
        weraeol(wdoctrl->wcurrent,attr);
    else
#endif
#ifdef IBM
#ifdef TERMINAL
        if(vctio != 5)
#endif
            scrollup(vcrow,vccol,vcrow,vcterm.cols-1,0,attr);
#ifdef TERMINAL
        else
            {
            term_at(vcrow,vccol);
            flipattr(attr);
            dist_str(vcterm.ce,0);
#ifdef WINDOW
            erateol(attr);
#endif
            }
#endif
#endif
#ifdef TERMONLY
        {
        term_at(vcrow,vccol);
        flipattr(attr);
        dist_str(vcterm.ce,0);
#ifdef WINDOW
        erateol(attr);
#endif
        }
#endif
#ifdef OS2
#ifdef TERMINAL
        if(vctio != 5)
#endif
            scrollup(vcrow,vccol,vcrow,vcterm.cols-1,-1,attr);
#ifdef TERMINAL
        else
            {
            term_at(vcrow,vccol);
            flipattr(attr);
            dist_str(vcterm.ce,0);
#ifdef WINDOW
            erateol(attr);
#endif
            }
#endif
#endif
    }


