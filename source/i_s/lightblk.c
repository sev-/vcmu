/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:04
*
*   Name            lightblk.c - light block field
*                                   
*   Description     Draws block field
*
*   Return Value    VOID
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

VOID lightblk(gi)
GETITEM *gi;
    {
    COUNT attr;
    COUNT bdr;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "lightblk:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(*gi->gtmpfld == '1')
        attr = gi->gattrag;
    else
        attr = gi->gattrnag;
    if(gi->gcontrol & FLDBORDER)
        {
        bdr = (gi->gcontrol & FLDBOLD) ? 0 : 1;
#ifdef WINDOW
        if((gi->gwptr != (WPTR) 0) && !override)
            wbox(gi->gwptr,gi->g_row-1,gi->g_col-1,gi->g_row+1,
                    gi->g_col+gi->g_length+1,bdr,gi->gcurattr);
        else
#endif
            box(gi->g_row-1,gi->g_col-1,gi->g_row+1,
                    gi->g_col+gi->g_length+1,bdr,gi->gcurattr);
        }
#ifdef WINDOW
    if((gi->gwptr != (WPTR) 0) && !override)
        wxatsay(gi->gwptr,gi->g_row,gi->g_col,gi->gtmppic,attr);
    else
#endif
        xatsay(gi->g_row,gi->g_col,gi->gtmppic,attr);
    }



