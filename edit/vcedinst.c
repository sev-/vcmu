/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:58
*
*   Name            vcedinst.c - inserts toggle
*                                   
*   Description     Toggles insert mode
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedinstog(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    if(vced->edaline != (DBDP)0)        /* If achor droped          */
        {
#ifdef VCEDFULL
        vcedblkcp(vced,1,FALSE);        /* Copy to scrap 1          */
#endif
        return(0);
        }
    else                                /*                          */
        {                               /*                          */
        if(vced->edmode & VCEDOVER)     /* Over write mode ?        */
            vced->edmode &= ~VCEDOVER;  /* Turn on insert mode      */
        else                            /* Else                     */
            vced->edmode |= VCEDOVER;   /* Turn on over write mode  */
        }                               /*                          */
    return(0);                          /* Return good              */    
    }                                   /* ------------------------ */

