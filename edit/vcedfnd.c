/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:45
*
*   Name            vcedfnd.c - find
*                                   
*   Description     Finds a key in the command structure.  Called
*                   by vcedexec to locate command to exec.
*
*   Return Value    Returns pointer to command for key if available
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

PFI vcedfndcmd(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    VCEDCMD *curcmd;        /* Current command structure            */
    PFI retval = NULLFUNC;  /* Return value                         */
    curcmd = &vcedcmds[0];              /* Start at beginning       */
    while(curcmd->cmdname != NULLTEXT)  /* While more commands      */
        {                               /*                          */
        if(vced->edkey[0] == curcmd->cmdkey) /* Is this the key?    */
            {                           /*                          */
            retval = curcmd->cmdloc;    /* Assign function address  */
            break;                      /* and return               */
            }                           /*                          */
        curcmd++;                       /* Point to next member     */
        }                               /*                          */
    return(retval);                     /* Return function address  */
    }                                   /* ------------------------ */

