/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:58
*
*   Name            vcedtol - top of line
*                                   
*   Description     Executes beginning of line command
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedtol(vced) 
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    vced->edcchar = 0;                  /* Set to first of line     */
    if(vced->edoffset)                  /* Is screen offset         */
        {                               /*                          */
        vced->edoffset = 0;             /* Point to beginning       */
        vced->edupval |= VCEDUPDALL;    /* Update entire screen     */
        }                               /*                          */
    }                                   /* ------------------------ */

