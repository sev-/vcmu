/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:49
*
*   Name            vcedtab.c - tab
*                                   
*   Description     Executes tab key
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedtab(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    VCEDLINE *cline;        /* Pointer to temporary line            */
    COUNT tval;             /* Temporary value for calculations     */
    COUNT save_loc = -1;    /* Used to determine if tab ins on tab  */
    COUNT inschr;           /* Character to insert (space or tabsp) */
    TEXT *ptr,*ptr2;        /* Temporary pointers                   */
    VCEDLINE *vcedmline();  /* Declare functions used               */
    COUNT vcedmkreal();     /*    "        "      "                 */
    VOID vcedsins();        /*    "        "      "                 */
    COUNT vcedadjtab();     /*    "        "      "                 */
    if(vced->edmode & VCEDOVER)         /* If in over write mode    */
        {                               /*  do not insert tab       */
        vcedmvright(vced);              /* Move right one character */
        while(TRUE)                     /* While more to move       */
            {                           /*                          */
            tval = vced->edcchar / vcedval.tabsize; /* Divide tab   */
            if(vced->edcchar == (tval * vcedval.tabsize)) 
                break;                  /* On tab stop              */
            vcedmvright(vced);          /* Move right               */
            }                           /*                          */
        }                               /*                          */
    else                                /*                          */
        {                               /*                          */
        if(vced->edcline == (DBDP)0)    /* If not on real line      */
            vcedmkreal(vced);           /* Make the current loc real*/
        cline = vcedmline(vced->edbuffer,vced->edcline);/* Get line */
        ptr = &cline->ltext[0] + vced->edcchar; /* Get current char */
        if((*ptr == vcedval.tabspace) &&    /* If on a tab space    */
           (vced->edcchar < cline->lused) ) /* And not passed eol   */
            {                           /*                          */
            while(*ptr == vcedval.tabspace) /* While more tabspaces */
                {                       /*                          */
                ptr++;                  /* Next location            */
                vced->edcchar++;        /*                          */
                if(vced->edcchar >= cline->lused) /* If at end      */
                    break;              /* Exit                     */
                }                       /*                          */
            save_loc = vced->edcchar;   /* Save current location    */
            }                           /*                          */
        if(vced->edcchar >= cline->lused)/* If passed eol           */
            {                           /*                          */
            ptr2 = &cline->ltext[0] + cline->lused; /* Point to eol */
            while(ptr2 < ptr)           /* While more spaces to ins */
                {                       /*                          */
                *(ptr2++) = ' ';        /* Insert spaces            */
                cline->lused++;         /* Increment chars used     */
                }                       /*                          */
            }                           /*                          */   
        if(vcedval.realtabs)            /* If useing real tabs      */
            {                           /*                          */
            vcedsins(&cline->ltext[0],vced->edcchar,vcedval.tabchr,
                            cline->lused); /* Insert character      */
            cline->lused++;             /* Increment lines used     */
            vcedmvright(vced);          /* Move cursor to right     */
            inschr = vcedval.tabspace;  /* Insert tab spaces        */
            }                           /*                          */
        else                            /* Else space for tabs      */
            {                           /*                          */
            vcedsins(&cline->ltext[0],vced->edcchar,' ',
                            cline->lused); /* Insert character      */
            cline->lused++;             /* Increment lines used     */
            vcedmvright(vced);          /* Move cursor to right     */
            inschr = ' ';               /* Setup for space insert   */
            }                           /*                          */
        while(TRUE)                     /* While more to insert     */
            {                           /*                          */
            tval = vced->edcchar / vcedval.tabsize; /* Divide tab   */
            if(vced->edcchar == (tval * vcedval.tabsize)) /* On tab */
                break;                  /* Stop                     */
            vcedsins(&cline->ltext[0],vced->edcchar,inschr,
                        cline->lused);  /* Insert character         */
            cline->lused++;             /* Increment lines used     */
            vcedmvright(vced);          /* Move cursor to right     */
            }                           /*                          */
        cline->lused = vcedadjtab(&cline->ltext[0],vced->edcchar,
                                    cline->lused); /* Adjust tabs   */
        if(save_loc != -1)              /* Correct location         */
            vced->edcchar = save_loc;   /* Set correct location     */
        vced->edupval |= VCEDUPDLINE;   /* Update entire line       */
        }                               /*                          */
    }                                   /* ------------------------ */

