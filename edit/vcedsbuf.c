/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:42
*
*   Name            vcedsbuf.c - save buffer
*                                   
*   Description     Execute save buffer key
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedsbuf(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    VOID vcedsave();        /* Declare functions used               */
    vcedsave(vced->edbuffer);           /* Save buffer              */
    return(0);                          /* Return everthing O.K.    */
    }                                   /* ------------------------ */

