/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:18
*
*   Name            vcedbkta.c - back tab
*                                   
*   Description     Executes a back tab
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>
        
COUNT vcedbktab(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    COUNT tval;             /* Temporary value to calc tab loc      */
    COUNT vcedmvleft();     /* Declare functions used               */
    vcedmvleft(vced);                   /* Move left one character  */
    while(TRUE)                         /* While more to move       */
        {                               /*                          */
        tval = vced->edcchar / vcedval.tabsize; /* Divide tab       */
        if(vced->edcchar == (tval * vcedval.tabsize)) 
            break;                      /* On tab stop              */
        vcedmvleft(vced);               /* Move left                */
        }                               /*                          */
    }                                   /* ------------------------ */

