/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:29
*
*   Name            vcedprtc.c - print character
*                                   
*   Description     Prints a character to screen
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedprtchar(vced,dbdp,start)
VCED *vced;                 /* Pointer to edit structure            */
DBDP dbdp;                  /* Pointer to line                      */
COUNT start;                /* Character number                     */
    {                       /* ------------------------------------ */
    VCEDLINE *lptr;         /* Pointer to current line              */
    COUNT length = 0;       /* Length of current line               */
    COUNT width;            /* Width of window                      */
    COUNT depth;            /* Depth of current window              */
    WPTR wptr;              /* Current window                       */
    TEXT *ptr;              /* Actual text of current line          */
    VCEDLINE *vcedgline();  /*    "        "      "                 */
    wptr = vced->edwptr;                /* Window to use            */
    width = wcols(wptr);                /* Get width                */
    lptr = vcedgline(vced->edbuffer,vced->edcline);/* Get cur line  */
    start = max(start,vced->edoffset);  /* Update max               */
    wat(wptr,(COUNT)(vced->edcrow-vced->edtrow),
                vced->edlmar+start-vced->edoffset);
    ptr = lptr->ltext;                  /* Point to first char      */
    ptr += start;                       /* Point to start char      */
    wputchr(wptr,*ptr,wptr->say_at);    /* Print character          */
    }                                   /* ------------------------ */

