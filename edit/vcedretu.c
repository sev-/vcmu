/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:33
*
*   Name            vcedretu.c - return
*                                   
*   Description     Executes return key
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedreturn(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    VOID vcedxreturn();     /* Declare functions used               */
    if(!(vced->edmode & VCEDOVER) &&    /* If in insert mode        */
            vced->edcline)              /* and a current line       */
        vcedxreturn(vced);              /* Issue a return           */
    vcedmvdown(vced);                   /* Move to next row         */
    vcedtol(vced);                      /* Move to beginning of line*/
    }                                   /* ------------------------ */

VOID vcedxreturn(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    VCEDLINE *cline;        /* Pointer to temporary line            */
    VCEDLINE *nline;        /* Pointer to temporary line            */
    TEXT *ptr1,*ptr2,*ptr3; /* Temporary pointers                   */
    COUNT newused = 1;      /* Amount of new line used              */
    VCEDLINE *vcedmline();  /* Declare functions used               */
    COUNT vcedadjtab();     /*    "        "      "                 */
    if(vced->edcline == 0)              /* If no current line       */
        return;                         /* Exit                     */
    vcedempty(vcedfbuf,vced->edbuffer->bflinelen);  /* Empty buf    */
    cline = vcedmline(vced->edbuffer,vced->edcline);/* Get cur      */
    if(vced->edcchar > cline->lused)    /* If not passed end of line*/
        vced->edcchar = cline->lused;   /* Assign to eol            */
    else                                /*                          */
        vced->edupval |= VCEDUPDPLINE;  /* Update previous line     */
    ptr1 = ptr2 = &cline->ltext[0];     /* Set to beginning of line */
    ptr1 += vced->edcchar;              /* Increment to current char*/
    if((*ptr1 == vcedval.tabspace) &&   /* If on tab space          */
       (vced->edcchar < cline->lused))  /* And not passed eol       */
        while((ptr1 > ptr2) &&          /* While not at top of line */
              (*ptr1 == vcedval.tabspace)) /* And still tabspace    */
            {                           /*                          */
            ptr1--;                     /* Move back one character  */
            vced->edcchar--;            /* Decrement current loc.   */
            }                           /*                          */
    ptr2 += cline->lused;               /* Point to end of line     */
    newused = cline->lused - vced->edcchar; /* Number used          */
    cline->lused = vced->edcchar;       /* Calculate no. left       */
    ptr3 = &vcedfbuf[0];                /* Point to temporary loc.  */
    while(ptr1 < ptr2)                  /* While more chars to move */
        {                               /*                          */
        *(ptr3++) = *ptr1;              /* Move character           */
        *(ptr1++) = 0;                  /* Erase characters         */
        }                               /*                          */
    ptr1 = &cline->ltext[0] + vced->edbuffer->bflinelen-1;/* Eol    */
    vcedfbuf[vced->edbuffer->bflinelen -1] = *ptr1; /* Move ret     */
    *ptr1 = vcedval.hardret;        /* Assign hard return           */
    vcedrline(vced->edbuffer,cline,vced->edcline);/* Update line    */
    newused = vcedadjtab(vcedfbuf,0,newused); /* Adjust tabs        */
    vcediline(vced->edbuffer,vced->edcline,cline->lnext,vcedfbuf,newused);
    vced->edupval |= VCEDUPDALL;        /* Refresh Screen           */
    }                                   /* ------------------------ */

