/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:28
*
*   Name            vceddlin.c - delete line
*                                   
*   Description     Low level delete line function
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

VOID vceddline(edbuf,prev,curr,next)
VCEDBUF *edbuf;             /* Edit buffer                          */
DBDP prev;                  /* Previous line                        */
DBDP curr;                  /* Line to delete                       */
DBDP next;                  /* Next line                            */
    {                       /* ------------------------------------ */
    VCEDLINE *lptr;         /* Pointer to line to delete            */
    VCEDLINE *vcedgline();  /* Declare functions used               */
    COUNT vcedrline();      /*    "        "       "                */
    if(prev != (DBDP)0)                 /* If a previous line       */
        {                               /*                          */
        lptr = vcedgline(edbuf,prev);   /* Get previous line        */
        lptr->lnext = next;             /* Assign next value        */
        vcedrline(edbuf,lptr,prev);     /* Save Value               */
        }                               /*                          */
    if(next != (DBDP)0)                 /* If a next line           */
        {                               /*                          */
        lptr = vcedgline(edbuf,next);   /* Get next line            */
        lptr->lprev = prev;             /* Assign prev value        */
        vcedrline(edbuf,lptr,next);     /* Save Value               */
        }                               /*                          */
    if(curr == edbuf->bffline)          /* If the first line        */
        edbuf->bffline = next;          /* Assign new first line    */
    if(curr == edbuf->bfbline)          /* If the bottom line       */
        edbuf->bfbline = prev;          /* Assign new bottom        */
    lptr = vcedgline(edbuf,curr);       /* Get current line         */
#ifdef VCEDFULL
    vcedunline(edbuf,lptr,prev,curr,next,VCEDUNDEL); /* Tell undo   */
#endif
    vcedzline(edbuf,lptr,curr);         /* Free current line        */
    edbuf->bfnlines--;                  /* Decrement number of lines*/
    }                                   /* ------------------------ */

