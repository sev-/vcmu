/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:27
*
*   Name            xxatcget.c  --  Place an entry in input que
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
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT xxatcget(tblptr,wptr,row,col,fld,pic,val,msg,help,
                  act,nact,width,control,lst,pre,post,pl,id)
GETTABLE *tblptr;   /* Pointer to gettable to use                   */
WPTR wptr;          /* Pointer to Window                            */
COUNT row,col;      /* Row and column for input                     */
TEXT *fld;          /* Pointer to field to place input              */
TEXT *pic;          /* Pointer to picture to use for input          */
PFI val;            /* Pointer to Validation function               */
TEXT *msg;          /* Pointer to status message                    */
TEXT *help;         /* Pointer to help text                         */
COUNT act;          /* Active attribute                             */
COUNT nact;         /* Non Active attribute                         */
COUNT width;        /* Input width to use                           */
COUNT control;      /* Control Byte for get                         */
TEXT *lst;          /* Pointer to list structure                    */
PFI pre;            /* Pointer to pre-function                      */
PFI post;           /* Pointer to post-function                     */
PFI pl;             /* Pointer to pick list function                */
COUNT id;           /* Item id number                               */
    {
    COUNT datatype;
    COUNT opt;
    COUNT security;
    COUNT ctrl = 0;
    GETITEM *vcxxtfld();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xxatcget:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(control == -1)
        {
        opt = -1;
        ctrl = 0;
        }
    else
        {
        security = control & 127;
        control = control & ~127;
        datatype = (control >> 11) & 15;
        opt = control & ~(DTYPE15);
        if(pic != NULLTEXT)
            ctrl = gettype(pic);
        ctrl = ctrl << 7;
        ctrl |= (datatype << 11);
        ctrl |= security;
        }
    if(vcxxtfld(tblptr,wptr,row,col,fld,pic,opt,ctrl,NULLTEXT,
                val,msg,help,act,nact,width,lst,pre,post,
                pl,id,(COUNT *)0,NULLTEXT) == (GETITEM *)0)
        return(-1);
    else
        return(0);    
    }



