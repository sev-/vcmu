/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:53
*
*   Name            vcedhome.c - home key
*                                   
*   Description     This function decides which home function
*                   gets called (tol,tos,tof)
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedhome(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    COUNT retval;           /* Return value                         */
    if(vced->edkey[0] != vced->edkey[1])/* Last key not same        */
        retval = vcedtol(vced);         /* Call home line           */
    else if(vced->edkey[0] == vced->edkey[2]) /* Last two key ==    */
        retval = vcedtof(vced);         /* Goto beginning of file   */
    else                                /*                          */
        retval = vcedtos(vced);         /* Goto top of screen       */
    return(retval);                     /* Return status            */
    }                                   /* ------------------------ */

