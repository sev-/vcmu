/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:09
*
*   Name            get.c  --  Place an entry in input que
*
*   Description     This function sets up default values and call
*                   xatget() which enters an entry into a get table to
*                   be read at a later time and displays the entry on
*                   the screen.  Uses default attributes for active
*                   and non-active gets and vcrow, vccol for the
*                   location.
*
*   Return Value    Returns -1 if error 
*
**/

#include <vcstdio.h>

COUNT get(fld,pic)
TEXT *fld;          /* Pointer to field to place input              */
TEXT *pic;          /* Pointer to picture to use for input          */
    {
    COUNT xatgetc();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "get:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if(wdoctrl->wno_opn && !override)
        return(xatgetc(wdoctrl->wcurrent->r_pos,
               wdoctrl->wcurrent->c_pos,fld,pic,NULLFUNC,
               NULLTEXT,NULLTEXT,-1,-1,-1,-1,NULLTEXT));
    else
#endif
        return(xatgetc(vcrow,vccol,fld,pic,NULLFUNC,
                   NULLTEXT,NULLTEXT,-1,-1,-1,-1,NULLTEXT));
    }


