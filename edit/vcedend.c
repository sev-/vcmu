/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:32
*
*   Name            vcedend.c - end key
*                                   
*   Description     This function decides which end function
*                   gets called (eol,eos,eof)
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedend(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    COUNT retval;           /* Return value                         */
    if(vced->edkey[0] != vced->edkey[1])/* Last key not same        */
        retval = vcedeol(vced);         /* Call end line            */
    else if(vced->edkey[0] == vced->edkey[2]) /* Last two key ==    */
        retval = vcedeof(vced);         /* Goto end of file         */
    else                                /*                          */
        retval = vcedeos(vced);         /* Goto bottom of screen    */
    return(retval);                     /* Return status            */
    }                                   /* ------------------------ */

