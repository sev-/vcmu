/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:08
*
*   Name            lighvcho.c - light choice field
*                                   
*   Description     Draws choice field
*
*   Return Value    VOID
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

VOID lighvcho(gi)
GETITEM *gi;
    {
    COUNT fldnbr;
    TEXT **fldptr;
    COUNT bdr;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "lighvcho:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    fldptr = (TEXT **)gi->gselset;
    fldnbr = (COUNT)(*gi->gtmpfld - '0');/* Find current field value*/
    while((*fldptr != NULLTEXT ) && fldnbr--)
        fldptr++;
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
    if(*fldptr != NULLTEXT)
        {
#ifdef WINDOW
        if((gi->gwptr != (WPTR) 0) && !override)
            wxatsay(gi->gwptr,gi->g_row,gi->g_col,*fldptr,gi->gcurattr);
        else
#endif
            xatsay(gi->g_row,gi->g_col,*fldptr,gi->gcurattr);
        }
    }



