/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:57
*
*   Name            vcedtogs.c - toggle status
*                                   
*   Description     Executes toggle status line command
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedtogstat(vced) 
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    if(vced->edmode & VCEDSTATUS)       /* If display status line   */
        {                               /*                          */
        vced->edmode &= ~VCEDSTATUS;    /* Turn off status          */
        if(vced->edswptr != (WPTR)0)    /* If status window open    */
            werase(vced->edswptr,-1);   /* Erase status window      */
        }                               /*                          */
    else                                /* Status is off            */
        vced->edmode |= VCEDSTATUS;     /* Turn status on           */
    return(GOOD);                       /* Return O.K.              */
    }

