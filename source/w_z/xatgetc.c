/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:10
*
*   Name            xatgetc.c  --  Place an entry in input que
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

COUNT xatgetc(row,col,fld,pic,val,msg,help,act,nact,width,ctrl,lst)
COUNT row,col;      /* Row and column for input                     */
TEXT *fld;          /* Pointer to field to place input              */
TEXT *pic;          /* Pointer to picture to use for input          */
PFI val;            /* Pointer to Validation function               */
TEXT *msg;          /* Pointer to status message                    */
TEXT *help;         /* Pointer to help text                         */
COUNT act;          /* Active attribute                             */
COUNT nact;         /* Non Active attribute                         */
COUNT width;        /* Input width to use                           */
COUNT ctrl;         /* Control Byte for get                         */
TEXT *lst;          /* Pointer to list structure                    */
    {
    COUNT xxatcget();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xatgetc:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(ctrl == -1)
        ctrl = datactrl[0];
    return(xxatcget(NULLTEXT,(WPTR) 0,row,col,fld,pic,val,msg,help,
                   act,nact,width,ctrl,lst,NULLFUNC,NULLFUNC,dplist,0));
    }


