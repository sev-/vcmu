/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:16
*
*   Name            vcedmvup.c - move up
*                                   
*   Description     Executes cursor up
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedmvup(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    VCEDLINE *cline;        /* Pointer to temporary line            */
    VCEDLINE *vcedgline();  /* Declare functions used               */
    COUNT vcedscroll();     /*    "        "      "                 */
    if(vced->edcrow)                    /* If not at tof            */
        {                               /*                          */
        if(vced->edcline)               /* Is there a current line  */
            {                           /*                          */
            cline = vcedgline(vced->edbuffer,vced->edcline);/* Get  */
            if(cline->lprev != (DBDP)0) /* If previous line         */
                vced->edcline = cline->lprev;   /* Move to prev     */
            }                           /*                          */
        vced->edcrow--;                 /*                          */
        if(vced->edcrow == (vced->edbuffer->bfnlines-1))/* At bottom*/
            vced->edcline = vced->edbuffer->bfbline;/* Assign cur.  */
        if(vced->edcrow < vced->edtrow) /* Have we gone off top     */
            {                           /*                          */
            vcedscroll(vced,vckey.cur_up,vcedval.shiftup);/* Scroll */
            vced->edupval |= VCEDUPDALL;/* Update entire screen     */
            }            
        }                               /*                          */
    return(0);                          /* Return O.K.              */
    }                                   /* ------------------------ */

