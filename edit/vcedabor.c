/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:09
*
*   Name            vcedabor.c - abort editor
*                                   
*   Description     Caused the editor to abort
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedabort(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    vced->edmail = VCEDABORT;           /* Set mail to exit value   */
    return(0);                          /* Return good              */
    }                                   /* ------------------------ */

