/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:11
*
*   Name            lightrl.c  --  display right to left fields 
*
*   Description     This function displays the right to left input
*                   fields
*
*   Return Value    VOID
*
**/

#define VCGET_DEFS

#include <vcstdio.h>

VOID lightrl(gi)
GETITEM *gi;
    {
    COUNT retval;
    TEXT buf[130];
    COUNT prnnum();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "lightrl:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    retval = sprtnum(buf,gi->gtmpfld,gi->gtmppic);
#ifdef WINDOW
    if((gi->gwptr != (WPTR) 0) && !override)
        wxatsay(gi->gwptr,gi->g_row,gi->g_col,buf,gi->gcurattr);
    else
#endif
        xatsay(gi->g_row,gi->g_col,buf,gi->gcurattr);
    if(gi->gstart)
        gi->gatend = retval;
    }


