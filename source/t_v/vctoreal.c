/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:03
*
*   Name            vctoreal.c - to real location
*                                   
*   Description     Converts a get node from the temporary
*                   location to the real location
*
*   Return Value    VOID
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

VOID vctoreal(gi)
GETITEM *gi;                /* Pointer to getnode to convert        */
    {                       /* ------------------------------------ */
    COUNT datatype;         /* Used to convert datatype             */
    datatype = (gi->gfldtyp >> 11) & 15;    /* Calculate data type  */
    if( datapost[datatype] )            /* If conversion function   */
        (*datapost[datatype])(gi);      /* Call function            */
    }                                   /* ------------------------ */
    
