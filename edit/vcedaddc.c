/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:10
*
*   Name            vcedaddc.c - Address cursor
*                                   
*   Description     This address the cursor for the editor
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedaddcur(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    COUNT col;              /* Used to calculate column             */
    VOID wat();             /* Declare functions used               */
    col = max(0,(vced->edcchar-vced->edoffset+vced->edlmar));
    wat(vced->edwptr,(COUNT)(vced->edcrow-vced->edtrow),col); 
    return(0);                          /* Return O.K.              */
    }                                   /* ------------------------ */

