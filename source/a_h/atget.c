/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:44
*
*   Name            atget.c  --  Place an entry in input que
*
*   Description     This function sets up default values and call
*                   xatget() which enters an entry into a get table to
*                   be read at a later time and displays the entry on
*                   the screen.  Uses default attributes for active
*                   and non-active gets.
*
*   Return Value    Returns -1 if error 
*
**/

#include <vcstdio.h>

COUNT atget(row,col,fld,pic)
COUNT row,col;      /* Row and column for input                     */
TEXT *fld;          /* Pointer to field to place input              */
TEXT *pic;          /* Pointer to picture to use for input          */
    {
    COUNT xatgetc();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "atget:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(xatgetc(row,col,fld,pic,NULLFUNC,NULLTEXT,NULLTEXT,
           -1,-1,-1,-1,NULLTEXT));
    }

