/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:52:00
*
*   Name            vcedtos.c - top of screen
*                                   
*   Description     Move to the top of the screen
*
*   Return Value    Return O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedtos(vced) 
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    vced->edcchar = 0;                  /* Set to first of line     */
    if(vced->edoffset)                  /* Is screen offset         */
        {                               /*                          */
        vced->edoffset = 0;             /* Point to beginning       */
        vced->edupval |= VCEDUPDALL;    /* Update entire screen     */
        }                               /*                          */
    vced->edcline = vced->edtline;      /* Go to top line           */
    vced->edcrow = vced->edtrow;        /* Set current row number   */
    return(0);                          /* Return O.K.              */
    }                                   /* ------------------------ */


