/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:33
*
*   Name            vcedeof - end of file
*                                   
*   Description     Executes end of file
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedeof(vced) 
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    VCEDLINE *lptr;         /* Pointer to current line              */
    VCEDLINE *vcedgline();  /* Declare function used                */
    if(vced->edcline == (DBDP)0)        /* If passed end of file    */
        vcedtof(vced);                  /* Move to top of file      */
    while(vced->edcline != vced->edbuffer->bfbline) /* While not eof*/
        vcedmvdown(vced);               /* Move down                */
    lptr = vcedgline(vced->edbuffer,vced->edcline); /* Get cur line */
    vced->edcchar = lptr->lused;        /* Move end of line         */
    return(0);                          /* Return O.K.              */
    }                                   /* ------------------------ */


