/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:49
*
*   Name            atsay.c  --  At location display string
*
*   Description     This function displays a NULL terminated string
*                   at location row,col using default say attribute.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID atsay(row,col,fld)
COUNT row,col;  /* Row and column to display string                 */
TEXT *fld;      /* String to display                                */
    {
    VOID xatsay();
    FAST COUNT start;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "atsay:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if(wdoctrl->wno_opn && !override)
        start=wdoctrl->wcurrent->say_at;
    else
#endif
        start=attrsay;
    xatsay(row,col,fld,start);
    }


