/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:27
*
*   Name            statsay.c  --  Say status
*
*   Description     Display a status message 
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

static COUNT status_length = 0;

VOID statsay(msg,nattr)
TEXT *msg;
COUNT nattr;
    {
    COUNT mlen,attr,*statlen,dif;
#ifdef TERMINAL
    COUNT flow = 0;
#endif
    COUNT vcpee();
    VOID xatsay();
    COUNT strlen();
    VOID at();
    VOID clrfld();
    VOID wxatsay();
    VOID wat();
    COUNT wputchr();
    VOID vcflush();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "statsay:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef TERMINAL
    if(vctio == 5)
        flow = vcpee();
#endif
#ifdef WINDOW
    if(msgwdo == (WPTR)0)
        {
#endif
        if(msg)
            {
            if(nattr == -1)
                attr = msgattr;
            else
                attr = nattr;
            xatsay(msgrow,msgcol,msg,attr);
            mlen = strlen(msg);
            }
        else
            mlen = 0;
#ifdef WINDOW
        if(wdoctrl->wno_opn && !override)
            statlen = &(wdoctrl->wcurrent->smerge);
        else
#endif
            statlen = &status_length;
        if(*statlen > mlen)
            {
            at(msgrow,msgcol+mlen);
#ifdef WINDOW
            if(wdoctrl->wno_opn && !override)
                attr=wdoctrl->wcurrent->bg_at;
            else
#endif
                attr=normattr;
            clrfld(*statlen-mlen,attr);
            }
        *statlen = mlen;
#ifdef WINDOW
        }
    else
        {
        if(msg)
            {
            if(nattr == -1)
                attr = msgattr;
            else
                attr = nattr;
            wxatsay(msgwdo,msgrow,msgcol,msg,attr);
            mlen = strlen(msg);
            }
        else
            mlen = 0;
        if(msgwdo->smerge > mlen)
            {
            cur_switch = FALSE;
            wat(msgwdo,msgrow,msgcol+mlen);
            dif = msgwdo->smerge-mlen;
            while(dif--)
                wputchr(msgwdo,msgwdo->fill_ch,msgwdo->bg_at);
            cur_switch = TRUE;
            wplace_cur(wdoctrl->wcurrent);
            }
        msgwdo->smerge = mlen;
        }
#endif
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    }


