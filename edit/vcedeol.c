/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:35
*
*   Name            vcedeol.c - end of line
*                                   
*   Description     Executes end of line
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedeol(vced) 
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    VCEDLINE *cline;        /* Pointer to temporary line            */
    COUNT oldoffset;        /* Old offset value                     */
    VCEDLINE *vcedgline();  /* Declare functions used               */
    COUNT vcedllen();       /*    "        "      "                 */
    if(vced->edcline)                   /* If a current line        */
        {                               /*                          */
        vced->edcchar = min((vcedllen(vced,vced->edcline)),
                           (vced->edbuffer->bflinelen-2));
        oldoffset = vced->edoffset;     /* Save old value           */
        vced->edoffset = max((vced->edcchar-wcols(vced->edwptr)+1),0);
        if(vced->edoffset != oldoffset) /* If screen needs shifting */
            vced->edupval |= VCEDUPDALL;/* Update entire screen     */
        }                               /*                          */
    else                                /*                          */
        vced->edcchar = 0;              /* First of line            */
    }                                   /* ------------------------ */

