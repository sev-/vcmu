/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:09
*
*   name            xatget.c  --  Place an entry in input que
*
*   Description     This function enters an entry into a get table to 
*                   be read at a later time and displays the entry on
*                   the screen.  If -1 for attributes uses default for 
*                   active and non active gets. If window is open uses  
*                   colors from window.
*
*   Return Value    Returns -1 if error 
*
**/

#include <vcstdio.h>

COUNT xatget(row,col,fld,pic,val,msg,help,act,nact)
COUNT row,col;      /* Row and column for input                     */
TEXT *fld;          /* Pointer to field to place input              */
TEXT *pic;          /* Pointer to picture to use for input          */
PFI val;            /* Pointer to Validation function               */
TEXT *msg;          /* Pointer to status message                    */
TEXT *help;         /* Pointer to help text                         */
COUNT act;          /* Active attribute                             */
COUNT nact;         /* Non Active attribute                         */
    {
    COUNT xatgetc();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xatget:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(xatgetc(row,col,fld,pic,val,msg,help,act,nact,-1,-1,
                  NULLTEXT));
    }


