/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:52:03
*
*   Name            vcedupda.c - update
*                                   
*   Description     Checks the update flag and updates the screen
*                   accordingly
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedupdate(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    COUNT col;              /* Temporary column variable            */
    static COUNT fast = 0;  /* Restore complete window (type ahead) */
    static DBDP row = (DBDP)-1;  /* Row on when fast started        */
    static LONG line = (DBDP)-1; /* Line on when fast started       */
    COUNT keyrdy();         /* Declare functions used               */
    if((vced->edaline != (DBDP)0) && !vced->edupval)
        vced->edupval = VCEDUPDALL;     /* Update screen            */
    if(vckeyrdy && keyrdy() &&          /* If another key waiting   */
      (vced->edupval & VCEDUPDALL) )    /* And update entire screen */
        {                               /*                          */
        fast = TRUE;                    /* Flag type ahead          */
        if(vced->edmode & VCEDSTATUS)   /* If display status line   */
            vcedstatus(vced);           /* Display status line      */ 
        vcedaddcur(vced);               /* Address cursor           */
        return(0);                      /* Return and process       */
        }                               /*                          */
    if(fast || (vced->edupval & VCEDUPDALL))/* Update entire screen */
        {                               /*                          */
        fast = FALSE;                   /* Reset fast variable      */
        vcedprtbuf(vced);               /* Restore entire screen    */
        vced->edupval = 0;              /* Clear update flag        */
        }                               /*                          */
    if(vced->edupval & VCEDUPDLINE)     /* Update line ?            */
        {
        vcedprtline(vced,vced->edcline,0);/* Update line            */
        }
    if(vced->edupval & VCEDUPDPEOL)     /* Update prev. char to eol */
        {                               /*                          */
        col = max(0,vced->edcchar-1);   /* Max current char or 0    */
        vcedprtline(vced,vced->edcline,col);/* Update line          */
        }                               /*                          */
    if(vced->edupval & VCEDUPDEOL)      /* Update character to eol  */
        {                               /*                          */
        vcedprtline(vced,vced->edcline,vced->edcchar);/* Update line*/
        }                               /*                          */
    if(vced->edupval & VCEDUPDPCHAR)    /* Update previous char     */
        {                               /*                          */
        col = max(0,vced->edcchar-1);   /* Max current char or 0    */
        vcedprtchar(vced,vced->edcline,col);/* Update line          */
        }                               /*                          */
    if(vced->edupval & VCEDUPDCHAR)     /* Update character         */
        {                               /*                          */
        col = max(0,vced->edcchar);     /* Max current char or 0    */
        vcedprtchar(vced,vced->edcline,col);/* Update line          */
        }                               /*                          */
    vced->edupval = 0;                  /* Clear update flag        */
    if(vced->edmode & VCEDSTATUS)       /* If display status line   */
        vcedstatus(vced);               /* Display status line      */ 
    vcedaddcur(vced);                   /* Address cursor           */
    }                                   /* ------------------------ */

