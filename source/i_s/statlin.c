/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:26
*
*   Name            statlin.c  --  Set status line
*
*   Description     This function sets the global variable for the
*                   location of the status line and returns the
*                   old location in a COUNT with row in the high
*                   byte and column in the low byte.
*
*   Return Value    Returns old status row and column
*
**/

#include <vcstdio.h>

COUNT statlin(wptr,row,col,attr)
WPTR wptr;          /* Window for status line                       */
PFAST COUNT row,col;/* Location for status line                     */
COUNT attr;         /* Attribute for status line                    */
    {
    COUNT oldloc;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "statlin:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    oldloc = (msgrow*0x100)+msgcol;
    msgrow = row;
    msgcol = col;
    if(wptr != (WPTR) 0)
        msgwdo = wptr;
    if(attr != -1)
        msgattr = attr;
    return(oldloc);
    }


