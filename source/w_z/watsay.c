/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:20:52
*
*   Name            watsay  --  Window at location print
*
*   Description     This allows you to print to any window without 
*                   selecting the window or changing wcurrent.  
*                   This uses the default say attribute for the 
*                   window.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID watsay(wptr,row,col,fld)
PFAST WPTR wptr;    /* Pointer to window to display on              */
COUNT row,col;      /* Location to display string                   */
TEXT *fld;          /* Pointer to field to display                  */
    {
    FAST COUNT start;
    VOID wxatsay();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "watsay:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(wdoctrl->wno_opn && !override)
        start=wptr->say_at;
    else
        start=attrsay;
    wxatsay(wptr,row,col,fld,start);
    }

#endif

