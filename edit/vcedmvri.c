/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:14
*
*   Name            vcedmvri.c - move right
*                                   
*   Description     Executes cursor right key
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedmvright(vced) 
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    VCEDLINE *cline;        /* Pointer to temporary line            */
    COUNT cols;             /* Number of columns                    */
    VCEDLINE *vcedgline();  /* Declare functions used               */
    COUNT wcols();          /*    "        "      "                 */
    if(vced->edcchar >= (vced->edbuffer->bflinelen-2))/* If at eol  */
        {                               /*                          */
        vcedmvdown(vced);               /* Move to next line        */
        vcedtol(vced);                  /* Move to top of line      */
        }                               /*                          */
    else                                /* Not at eol               */
        {                               /*                          */
        vced->edcchar++;                /* Inc. char.               */
        cols = wcols(vced->edwptr);     /* Get number of columns    */
        if((vced->edcchar-vced->edoffset) >=    /* If next char off */
            (cols+vced->edlmar))        /* the screen               */
            {                           /*                          */
            vced->edupval |= VCEDUPDALL;/* Update entire screen     */
            vced->edoffset = min((vced->edoffset + vcedval.shiftleft)
                                ,(vced->edbuffer->bflinelen-1-cols));
            }                           /* Adjust screen            */
        }                               /*                          */
    }                                   /* ------------------------ */

