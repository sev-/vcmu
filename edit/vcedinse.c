/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:56
*
*   Name            vcedinse.c - insert
*                                   
*   Description     Insert a character routine
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedinsert(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    vcedxinsert(vced,vced->edkey[0]);   /* Insert key               */
    return(0);                          /* Return O.K.              */
    }                                   /* ------------------------ */

COUNT vcedxinsert(vced,key)
VCED *vced;                 /* Pointer to edit structure            */
COUNT key;                  /* Key to insert                        */
    {                       /* ------------------------------------ */
    VCEDLINE *cline;        /* Pointer to temporary line            */
    COUNT old_loc;          /* Old column location                  */
    TEXT *ptr1,*ptr2;       /* Temporary pointers                   */
    VCEDLINE *vcedmline();  /* Declare functions used               */
    VOID vcedsins();        /*    "        "      "                 */
    COUNT vcedmkreal();     /*    "        "      "                 */
    if(vced->edcline == (DBDP)0)        /* If not on real line      */
        vcedmkreal(vced);               /* Make the current loc real*/
    cline = vcedmline(vced->edbuffer,vced->edcline);/* Get cur. line*/
    ptr1 = ptr2 = &cline->ltext[0];     /* Set to beginning of line */
    ptr1 += vced->edcchar;              /* Increment to current char*/
    if(cline->lused < cline->lsize)     /* If there is room on line */
        {                               /*                          */
        ptr2 += cline->lused;           /* Point to end of line     */
        if(vced->edcchar < cline->lused)/* If not passed end of line*/
            {                           /*                          */
            if(*ptr1 == vcedval.tabspace)   /* If on a tab space    */
                {                       /*                          */
                vcedrmtab(&cline->ltext[0],ptr1-1);/* Rem tab       */
                *ptr1 = key;            /* Insert character         */
                vcedmvright(vced);      /* Move cursor to right     */
                if(*(ptr1+1) == vcedval.tabspace)  /* Next != sp    */
                    {                   /*                          */
                    *(ptr1+1) = vcedval.tabchr;    /* Move tab char */
                    vced->edupval |= VCEDUPDLINE;  /* Update char   */
                    }                   /*                          */
                else                    /* else                     */
                    {                   /*                          */
                    old_loc = vced->edcchar;    /* Save location    */
                    vcedtab(vced);      /* Insert tab               */
                    vced->edcchar = old_loc;    /* Restore location */
                    vced->edupval |= VCEDUPDLINE; /* Update to eol  */
                    }                   /*                          */
                }                       /*                          */
            else                        /*                          */
                {                       /*                          */
                vcedsins(&cline->ltext[0],vced->edcchar,key,
                            cline->lused); /* Insert character      */
                cline->lused++;         /* Increment lines used     */
                vcedmvright(vced);      /* Move cursor to right     */
                cline->lused = vcedadjtab(&cline->ltext[0],vced->edcchar,
                                    cline->lused); /* Adjust tabs   */
                vced->edupval |= VCEDUPDPEOL;/* Update cur to eol   */
                }                       /*                          */
            }                           /*                          */
        else                            /* Passed end of line       */
            {                           /*                          */
            while(ptr2 != ptr1)         /* While more spaces to ins */
                {                       /*                          */
                *(ptr2++) = ' ';        /* Insert spaces            */
                cline->lused++;         /* Increment chars used     */
                }                       /*                          */
            *ptr1 = key;                /* Insert new character     */
            vcedmvright(vced);          /* Move cursor to right     */
            cline->lused++;             /* Increment chars used     */
            vced->edupval |= VCEDUPDPCHAR;/* Update previous char.  */
            }                           /*                          */
        vcedrline(vced->edbuffer,cline,vced->edcline);/* Update line*/
        }                               /*                          */
    }                                   /* ------------------------ */



