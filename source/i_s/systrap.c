/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:42
*
*   Name            systrap.c -- System keyboard trap
* 
*   Description     This is a default system keyboard trap
*                   it captures the screen refresh, screen print,
*                   and key blocked function.  This function could
*                   be removed with no back side effect.
*
*   Return Value    Returns either 9999 to ignore the character
*                   or the character.     
*
**/

#include <vcstdio.h>

COUNT systrap(ich)
COUNT ich;          /* Input character to evaluate                  */
    {
    VOID bell();
    COUNT keyisblk();
    COUNT refresh();
    VOID vcprtscr();
    COUNT wrefresh();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "systrap:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(ich == spkey.scrn_fresh)
        {
#ifdef WINDOW
        if(wdoctrl->wno_opn)
            wrefresh(TRUE);
        else
#endif
#ifdef TERMINAL
            refresh();
#else
            ; /* wwrt_scrn(); */
#endif
        ich = 9999;
        }
    if(ich == spkey.prt_scrn)
        {
        vcprtscr();
        ich = 9999;
        }
    if(keysblocked)
        {
        if(keyisblk(ich))
            {
            ich = 9999;
            bell();
            }
        }
    return(ich);
    }

