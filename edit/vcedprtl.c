/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:31
*
*   Name            vcedprtl.c - print line
*                                   
*   Description     Low level prints one line from starting
*                   location
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedprtline(vced,dbdp,start)
VCED *vced;                 /* Pointer to edit structure            */
DBDP dbdp;                  /* Pointer to line to refresh           */
COUNT start;                /* Starting location                    */
    {                       /* ------------------------------------ */
    VCEDLINE *lptr;         /* Pointer to current line              */
    COUNT attr = -1;        /* Attribute to use for erase           */
    COUNT from = -1;        /* Start block mark attribute           */
    COUNT to = 0;           /* End block mark attribute             */
    COUNT row,col,bd;
    COUNT twidth;
    FAST TEXT *sptr;
#ifdef TERMINAL
    COUNT flow = FALSE;     /* Did we stop screen output            */
#endif
    WPTR wptr;              /* Current window                       */
    VCEDLINE *vcedgline();  /* Declare functions used               */
    wptr = vced->edwptr;                /* Window to use            */
    lptr = vcedgline(vced->edbuffer,vced->edcline);/* Get cur line  */
    start = max(start,vced->edoffset);  /* Update max               */
#ifdef TERMINAL
    flow = vcpee();                     /* Turn off updates         */
#endif
    cur_switch = FALSE;                 /* Turn off cursor updates  */
    row = (COUNT)(vced->edcrow-vced->edtrow);
    woff();                             /* Turn window off          */
    wat(wptr,row,vced->edlmar+start-vced->edoffset);/* Address cur. */
    weraeol(wptr,attr);                 /* Erase to end of line     */
    vceddisp(vced,wptr,lptr,start,from,to); /* Display line         */
    start -= vced->edoffset;
    bd=(wptr->wctrl & BORDER ? 1: 0);
    twidth = vcterm.cols << 1;
    row += wptr->upper_r+bd-wptr->cur_r;
    col = wptr->upper_c+bd-wptr->cur_c;
    sptr = wscreen+(row*twidth)+((col+start) << 1);
    wdoctrl->wfreeze = FALSE;
    wstack(wptr);
    vca_put(row,col+start,sptr,wcols(wptr)-start);
    cur_switch = TRUE;                  /* Turn cursor updates on   */
#ifdef TERMINAL
    if(flow)                            /* If we stopped scr output */
        vcflush();                      /* Flush output             */
#endif
    }                                   /* ------------------------ */

