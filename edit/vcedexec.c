/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:39
*
*   Name            vcedexec.c - execute command
*                                   
*   Description     Searches command list to see if character
*                   is command character if is executes command
*                   or inserts char 
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedexec(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    PFI command = NULLFUNC; /* Command to execute                   */
    PFI vcedfndcmd();       /* Find command in command structure    */
    if(vcedisch(vced->edkey[0]))        /* If valid printable char  */
        {                               /*                          */
        if(vced->edmode & VCEDOVER)     /* Over write mode ?        */
            vcedover(vced);             /* Over write the character */
        else                            /* Else                     */
            vcedinsert(vced);           /* Insert the character     */
        }                               /*                          */
    else if((command = vcedfndcmd(vced)) != NULLFUNC) /* Find cmd   */
        (*command)(vced);               /* Execute command          */
    else                                /*                          */
        bell();                         /* Inform user              */
    return(0);                          /* Return O.K.              */
    }                                   /* ------------------------ */

COUNT vcedisch(key)
COUNT key;
    {
    COUNT retval = TRUE;
    if((key < ' ') || (key > '~'))
        retval = FALSE;
    return(retval);
    }
