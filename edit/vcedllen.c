/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:03
*
*   Name            vcedllen.c - line len
*                                   
*   Description     Gets the lenght of a line
*
*   Return Value    Returns line length
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedllen(vced,cdbdp)
VCED *vced;                 /* Pointer to edit structure            */
DBDP cdbdp;                 /* Address of the line                  */
    {                       /* ------------------------------------ */
    VCEDLINE *cline;        /* Temporary line pointer               */
    COUNT retval = 0;       /* Return value                         */
    VCEDLINE *vcedgline();  /* Declare functions used               */
    cline = vcedgline(vced->edbuffer,cdbdp);    /* Get line         */
    if(cline != (VCEDLINE *)0)          /* If line was found        */
        retval = cline->lused;          /* Assign retval value      */
    return(retval);                     /* Return the value         */
    }                                   /* ------------------------ */    

