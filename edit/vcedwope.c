/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:52:08
*
*   Name            vcedwopen.c - window open
*                                   
*   Description     Low level function that opens vced window
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

VOID vcedwopen(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    WPTR wxopen();          /* Declare functions used               */
    if((vced->edwptr = wxopen(vced->edurow,vced->educol,/* Open wdo */
                            vced->edlrow,vced->edlcol,vced->edtitle,
                            vced->edctrl,0,0)) == (WPTR)0)
        askmsg("Editor Message","Error Opening Window",0);/* Inform*/
    }                       /* ------------------------------------ */

