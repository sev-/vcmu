/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:47
*
*   Name            vcedstat.c - status
*                                   
*   Description     Prints status line
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

static TEXT *vcedmodes[] =
    {
    (TEXT *)"Insert",
    (TEXT *)"Over  "
    };

COUNT vcedstatus(vced) 
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    COUNT mode;             /* Value of insert or overwrite         */
    TEXT modified[2];       /* Is buffer Modified                   */
    TEXT status[80];        /* Status message                       */
    if(vced->edswptr == (WPTR)0)        /* If window not open       */
        return(0);                      /* Return                   */
    if(vced->edsline > 1)               /* If status line need clr  */
        {                               /*                          */
        watsay(vced->edswptr,0,0,"                              ");
        vced->edsline = 0;              /* Clear flag               */
        }                               /*                          */
    vced->edsline *= 2;                 /* Double status line value */
    mode = (vced->edmode & VCEDOVER ? 1 : 0); /* Determine ins mode */
    if(vced->edbuffer->bfchange)        /* If buffer changed        */
        strcpy(modified,"*");           /* Display changed          */
    else                                /*                          */
        strcpy(modified," ");           /* Not changed              */
    sprintf(status,"Line:%4d  Column:%3d  %s %s",(COUNT)vced->edcrow+1,
                    (COUNT)vced->edcchar+1,vcedmodes[mode],modified);
    watsay(vced->edswptr,0,48,status);  /* Display on status line   */
    }                                   /* ------------------------ */


/* Old status line    
    COUNT used = 0;
    VCEDLINE *cline,*vcedgline();
    TEXT current = -1;
    TEXT endchar = -1;
    DBDP prev = (DBDP) 0;
    DBDP next = (DBDP) 0;
    if(vced->edcline)
        {
        cline = vcedgline(vced->edbuffer,vced->edcline);
        current = cline->ltext[vced->edcchar];
        endchar = cline->ltext[vced->edbuffer->bflinelen-1];
        prev = cline->lprev;
        next = cline->lnext;
        used = cline->lused;
        }
    sprintf(status,                                 
"%s Line:%4d  Column:%3d  %s  Char:%3d Used:%3d Ret:%3d T:%4d",
        modified,(COUNT)vced->edcrow+1,(COUNT)vced->edcchar+1,vcedmodes[mode],
                    current,used,endchar,
                    vced->edbuffer->bfnlines);
    watsay(vced->edswptr,0,1,status);
*/
