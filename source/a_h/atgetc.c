/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:47
*
*   Name            atgetc.c  --  Place an entry in input que
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

COUNT atgetc(row,col,fld,pic,wid,ctrl,lst)
COUNT row,col;      /* Row and column for input                     */
TEXT *fld;          /* Pointer to field to place input              */
TEXT *pic;          /* Pointer to picture to use for input          */
COUNT wid;          /* Maximum display width                        */
COUNT ctrl;         /* Control Byte for get                         */
TEXT *lst;          /* Pointer to list structure                    */
    {
    COUNT xatgetc();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "atgetc:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(xatgetc(row,col,fld,pic,NULLFUNC,NULLTEXT,NULLTEXT,
           -1,-1,wid,ctrl,lst));
    }


