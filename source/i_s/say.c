/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:48
*
*   Name            say.c  --  display string 
*
*   Description     This function displays a NULL terminated string
*                   at the current location (vcrow,vccol) using
*                   default say attribute.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID say(str)
PFAST TEXT *str;    /* String to display                            */
    {
    VOID atsay();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "say:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if(wdoctrl->wno_opn && !override)
        atsay(wdoctrl->wcurrent->r_pos,wdoctrl->wcurrent->c_pos,str);
    else
#endif
        atsay(vcrow,vccol,str);
    }


