/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:29
*
*   name            xxatget.c  --  Place an entry in input que
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

#define VCGET_DEFS
#include <vcstdio.h>

COUNT xxatget(tp,wp,row,col,fld,pic,val,msg,help,act,nact)
GETTABLE *tp;       /* Pointer to gettable to use                   */
WPTR wp;            /* Pointer to Window                            */
COUNT row,col;      /* Row and column for input                     */
TEXT *fld;          /* Pointer to field to place input              */
TEXT *pic;          /* Pointer to picture to use for input          */
PFI val;            /* Pointer to Validation function               */
TEXT *msg;          /* Pointer to status message                    */
TEXT *help;         /* Pointer to help text                         */
COUNT act;          /* Active attribute                             */
COUNT nact;         /* Non Active attribute                         */
    {
    COUNT xxatcget();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xxatget:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(xxatcget(tp,wp,row,col,fld,pic,val,msg,help,
                   act,nact,-1,datactrl[0],NULLTEXT,NULLFUNC,
                   NULLFUNC,NULLFUNC,0));
    }


