/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:21
*
*   Name            vcedclos.c - vced close
*                                   
*   Description     Closes the editor structure.  The buffer should be
*                   close first
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedclose(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    if(vced->edwptr != (WPTR)0)         /* If window open           */
        {                               /*                          */
        wclose(vced->edwptr);           /* Close window             */ 
        vced->edwptr = (WPTR)0;         /* Zero variable            */
        }                               /*                          */
    vcfree(vced,vcdebug);               /* Clear structure          */
    }                       /* ------------------------------------ */

