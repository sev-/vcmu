/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:17
*
*   Name            vcedbksp.c - backspace
*                                   
*   Description     Executes a backspace
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedbksp(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    VCEDLINE *cline;        /* Pointer to temporary line            */
    TEXT *ptr;              /* Pointer to point to current character*/
    VCEDLINE *vcedmline();  /* Declare functions used               */
    COUNT vcedmvleft();     /*    "        "      "                 */
    COUNT vceddelete();     /*    "        "      "                 */
    COUNT vcedover();       /*    "        "      "                 */
    if((vced->edcrow == 0l) &&          /* If current row equ zero  */
        (vced->edcchar == 0l) )         /*  and on first char.      */
        return(0);                      /* No where to go           */
    else                                /* Else not at beginning    */
        {                               /*                          */
        vcedmvleft(vced);               /* Move left one character  */
#ifdef BKSPNODEL
        if((vced->edmode & VCEDOVER) && /* If in over write mode    */
                vced->edcline)          /* and a current line       */
            {                           /*                          */
            vcedxover(vced,' ');        /* Put space in file        */
            vcedmvleft(vced);           /* Move back to location    */
            vced->edupval &= ~VCEDUPDPCHAR;/* Remove Update prev ch */
            vced->edupval |= VCEDUPDCHAR;/* Add Update character    */
            }                           /*                          */
        else                            /* Must be in insert mode   */
            {                           /*                          */
#endif
            cline = vcedmline(vced->edbuffer,vced->edcline);
            ptr = &cline->ltext[0] + vced->edcchar; /* Get char     */
            if((*ptr == vcedval.tabspace) &&    /* If on a tab space*/
               (vced->edcchar < cline->lused) ) /* And ~passed eol  */
                {                       /*                          */
                while((*ptr == vcedval.tabspace) && /* While tabsp  */
                      (vced->edcchar) ) /* And not at top of line   */
                    {                   /*                          */
                    ptr--;              /* Next location            */
                    vced->edcchar--;    /*                          */
                    }                   /*                          */
                }                       /*                          */
            vcedxdelete(vced,cline,vced->edcchar);  /* Delete key   */
            vcedrline(vced->edbuffer,cline,vced->edcline);/* Updt ln*/
#ifdef BKSPNODEL
            }                           /*                          */
#endif                        
        }                               /*                          */
    return(GOOD);                       /* Return good              */
    }                                   /* ------------------------ */

