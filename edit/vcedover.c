/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:21
*
*   Name            vcedover.c - over type
*                                   
*   Description     Executes insert a key with over type
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedover(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    return(vcedxover(vced,vced->edkey[0])); /* Insert last key      */
    }                                       /* -------------------- */

COUNT vcedxover(vced,key)
VCED *vced;                 /* Pointer to edit structure            */
COUNT key;                  /* Key to insert                        */
    {                       /* ------------------------------------ */
    VCEDLINE *cline;        /* Pointer to temporary line            */
    TEXT *ptr1,*ptr2,*ptr3; /* Temporary pointers                   */
    VCEDLINE *vcedmline();  /* Declare functions used               */
    COUNT vcedllen();       /*    "        "      "                 */
    COUNT vcedmkreal();     /*    "        "      "                 */
    if(vced->edcline == (DBDP)0)        /* If not on real line      */
        vcedmkreal(vced);               /* Make the current loc real*/
    cline = vcedmline(vced->edbuffer,vced->edcline);/* Get cur. line*/
    ptr1 = ptr2 = &cline->ltext[0];     /* Set to beginning of line */
    ptr1 += vced->edcchar;              /* Increment to current char*/
    *ptr1 = key;                        /* Insert new character     */
    if(vced->edcchar >= cline->lused)   /* If passed end of line    */
        {                               /*                          */
        ptr2 += cline->lused;           /* Point to end of line     */
        while(ptr2 != ptr1)             /* While more spaces to ins */
            {                           /*                          */
            *(ptr2++) = ' ';            /* Insert spaces            */
            cline->lused++;             /* Increment chars used     */
            }                           /*                          */
        cline->lused++;                 /* Increment for new char.  */
        }                               /*                          */
    vcedmvright(vced);                  /* Move cursor to right     */
    vcedrline(vced->edbuffer,cline,vced->edcline);/* Update line    */
    vced->edupval |= VCEDUPDPCHAR;      /* Update previous character*/
    }                                   /* ------------------------ */

