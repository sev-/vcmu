/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:37
*
*   Name            vcedeos.c - end of screen
*                                   
*   Description     Move to the end of the screen
*
*   Return Value    Return O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedeos(vced) 
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    LONG target;                        /* Location of bottom row   */
    target = (LONG)wrows(vced->edwptr); /* Get depth                */
    target += vced->edtrow - 1;         /* Find bottom row          */
    while(vced->edcrow < target)        /* While more to move       */
        vcedmvdown(vced);               /* Move down next row       */
    vcedeol(vced);                      /* Move to end of line      */
    return(0);                          /* Return O.K.              */
    }                                   /* ------------------------ */


