/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:43
*
*   Name            vcedscro.c - scroll
*                                   
*   Description     Low level scroll routine used by page up
*                   and page down
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedscroll(vced,direction,shift)
VCED *vced;                 /* Pointer to edit structure            */
COUNT direction;            /* Direction to scroll                  */
COUNT shift;                /* Number of rows to move               */
    {                       /* ------------------------------------ */
    VCEDLINE *cline;        /* Temporary pointer for line           */
    VCEDLINE *vcedgline();  /* Declare functions used               */
    if(direction == vckey.cur_up)       /* If scroll up             */
        {                               /*                          */
        if(vced->edtline == (DBDP)0)    /* If no top line           */
            {                           /*                          */
            while(shift && vced->edtrow)/* While more to move       */
                {                       /*                          */
                shift--;                /* Decrement count          */
                vced->edtrow--;         /* Decrement top row        */
                if(vced->edtrow == (vced->edbuffer->bfnlines-1))
                    {                   /* Did we hit a bottom line */
                    vced->edtline = vced->edbuffer->bfbline;
                    break;              /* We did so break and let  */
                    }                   /* Next part finish         */
                }                       /*                          */
            }                           /*                          */
        while(shift && vced->edtrow)    /* While more to shift      */
            {                           /*                          */
            shift--;                    /* Decrement count          */
            cline = vcedgline(vced->edbuffer,vced->edtline);
            vced->edtrow--;             /* Decrement row count      */
            vced->edtline = cline->lprev;   /* Assign previous      */
            }                           /*                          */
        }                               /*                          */
    if(direction == vckey.cur_down)     /* If scroll down           */
        {                               /*                          */
        while((vced->edtline != (DBDP)0) && /* While more lines     */
              shift)                    /*      and more to go      */
            {                           /*                          */
            shift--;                    /* Decrement count          */
            cline = vcedgline(vced->edbuffer,vced->edtline);
            vced->edtrow++;             /* Increment row count      */
            vced->edtline = cline->lnext;   /* Assign next line     */
            }                           /*                          */
        while(shift)                    /* If still more to shift   */
            {                           /*                          */
            shift--;                    /* Decrement count          */
            vced->edtrow++;             /* Increment top row        */
            }                           /*                          */
        }                               /*                          */
    }                                   /* ------------------------ */

