/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:12
*
*   Name            vcedmvle.c - move left
*                                   
*   Description     Executes the cursor left function
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedmvleft(vced) 
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    VCEDLINE *cline;        /* Pointer to temporary line            */
    VCEDLINE *vcedgline();  /* Declare functions used               */
    if((vced->edcrow == 0l) &&          /* If current row equ zero  */
        (vced->edcchar == 0l) )         /*  and on first char.      */
        return(0);                      /* Return                   */
    if(vced->edcchar)                   /* If not first             */
        {                               /*                          */
        vced->edcchar--;                /* Dec. char.               */
        if(vced->edcchar < vced->edoffset) /* Need to shift         */
            {                           /*                          */
            vced->edupval |= VCEDUPDALL;/* Update entire screen     */
            if(vced->edcchar < wcols(vced->edwptr)) /* < than screen*/
                vced->edoffset = 0;     /* Peg to first half of scrn*/
            else                        /*                          */
                vced->edoffset = max((vced->edoffset-vcedval.shiftleft),0);
            }                           /*                          */
        }                               /*                          */
    else                                /*                          */
        {                               /*                          */
        if(vced->edcrow)                /* If not a top of file     */
            {                           /*                          */
            vcedmvup(vced);             /* Move up a row            */
            vcedeol(vced);              /* Move to end of line      */
            }                           /*                          */
        }                               /*                          */
    }                                   /* ------------------------ */

