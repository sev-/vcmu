/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:53
*
*   Name            vcedtof - top of file
*                                   
*   Description     Executes top of file command
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedtof(vced) 
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    vced->edcchar = 0;                  /* Set to first of line     */
    if(vced->edoffset ||                /* Is screen offset         */
       (vced->edtline != vced->edbuffer->bffline)) /* Need to redraw*/   
        {                               /*                          */
        vced->edoffset = 0;             /* Point to beginning       */
        vced->edtline = vced->edbuffer->bffline; /* Set top line    */
        vced->edupval |= VCEDUPDALL;    /* Update entire screen     */
        }                               /*                          */
    vced->edcline = vced->edtline;      /* Go to top line           */
    vced->edtrow = 0l;                  /* Set top row number       */
    vced->edcrow = 0l;                  /* Set current row number   */
    return(0);                          /* Return O.K.              */
    }                                   /* ------------------------ */

