/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 9/2/90 at 22:06:24
*
*   Name            lightchk - light check field
*                                   
*   Description     Draws Check field
*
*   Return Value    VOID
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

VOID lightchk(gi)
GETITEM *gi;
    {
    VOID inpchkpic();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "lightchk:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    inpchkpic(gi);
#ifdef WINDOW
    if((gi->gwptr != (WPTR) 0) && !override)
        wxatsay(gi->gwptr,gi->g_row,gi->g_col,gi->gtmppic,gi->gcurattr);
    else
#endif
        xatsay(gi->g_row,gi->g_col,gi->gtmppic,gi->gcurattr);
    }



