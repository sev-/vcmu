/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:11
*
*   Name            vcedmvdo.c - move down
*                                   
*   Description     Executes the move down or cursor down function
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedmvdown(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    VCEDLINE *cline;        /* Pointer to temporary line            */
    VCEDLINE *vcedgline();  /* Declare functions used               */
    COUNT vcedscroll();     /*    "        "      "                 */
    if(vced->edcline)                   /* If not past eof          */
        {                               /*                          */
        cline = vcedgline(vced->edbuffer,vced->edcline);/* Get line */
        if(cline->lnext != (DBDP)0)     /* If next line             */
            vced->edcline = cline->lnext;   /* Move to next         */
        else                            /*                          */
            vced->edcline = (DBDP) 0;   /* Make current line zero   */
        }                               /*                          */
    vced->edcrow++;                     /* Increment row number     */
    if(vced->edcrow >= (vced->edtrow + wrows(vced->edwptr)))
        {                               /*                          */
        vcedscroll(vced,vckey.cur_down,vcedval.shiftup); /* Scroll  */
        vced->edupval = VCEDUPDALL;     /* Update entire screen     */
        }                               /*                          */
    }                                   /* ------------------------ */

