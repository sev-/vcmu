/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:51
*
*   Name            sayseg.c  --  Display portion of field
*
*   Description     Display segment or part of a field
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID sayseg(wptr,r,c,fld,beg,width,attr)
WPTR wptr;          /* Window to display field                      */
COUNT r,c;          /* Row and column to use                        */
TEXT *fld;          /* Field to display                             */
COUNT beg;          /* Beginning location                           */
COUNT width;        /* Width to display                             */
COUNT attr;         /* Attribute to use                             */
    {
    COUNT oldr,oldc,oldcsw;
    TEXT tmp[160];
    COUNT cnt=0;
    VOID wxatsay();
    VOID wat();
    VOID xatsay();
    VOID at();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "sayseg:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if(wdoctrl->wno_opn && !override)
        {
        oldr = wdoctrl->wcurrent->r_pos;
        oldc = wdoctrl->wcurrent->c_pos;
        }
    else
        {
        oldr=vcrow;
        oldc=vccol;
        }
#else
    oldr=vcrow;
    oldc=vccol;
#endif
    oldcsw=cur_switch;
    cur_switch=FALSE;
    while( width-- && fld[beg] )
        tmp[cnt++] = fld[beg++];
    tmp[cnt] = '\0';
#ifdef WINDOW
    if((wptr != (WPTR) 0) && (wptr != wdoctrl->wcurrent))
        {
        wxatsay(wptr,r,c,tmp,attr);
        if(r == oldr)
            wat(wptr,oldr,oldc);
        }
    else
        {
#endif
        xatsay(r,c,tmp,attr);
        if(r == oldr)
            at(oldr,oldc);
#ifdef WINDOW
        }
#endif
    cur_switch=oldcsw;
    }


