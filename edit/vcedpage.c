/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:23
*
*   Name            vcedpage.c - page
*                                   
*   Description     Low level page command, called by both page up
*                   and page down
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedpage(vced,direction)
VCED *vced;                 /* Pointer to edit structure            */
COUNT direction;            /* Direction to scroll                  */
    {                       /* ------------------------------------ */
    LONG row_ofst;          /* Current top row                      */
    VCEDLINE *lptr;         /* Current line                         */
    DBDP cdbdp;             /* Current data base data pointer       */
    VCEDBUF *edbuf;         /* Edit buffer                          */
    COUNT vcedscroll();     /* Declare functions used               */
    VCEDLINE *vcednline();  /*    "        "      "                 */
    VCEDLINE *vcedgline();  /*    "        "      "                 */
    if((direction == vckey.cur_up) &&   /* If want to move up       */
       (vced->edtrow == 0) )            /* and at the top of file   */
        {                               /*                          */
        if((vced->edcchar != 0) ||      /* If not own first char. or*/
            (vced->edcrow != 0) )       /* If not own first row     */
            vcedtof(vced);              /* Top of screen            */
        return(0);                      /* Return                   */
        }                               /*                          */
    row_ofst = vced->edcrow - vced->edtrow;      /* Save difference */
    vcedscroll(vced,direction,wrows(vced->edwptr)); /* Scroll       */
    vced->edcrow = vced->edtrow + row_ofst;     /* Assign cur. row  */
    edbuf = vced->edbuffer;             /* Get buffer pointer       */
    cdbdp = vced->edtline;              /* Assign current dbase ptr */
    if(cdbdp != (DBDP)0);               /* If there is a top line   */
        lptr = vcedgline(edbuf,cdbdp);  /* Get top of screen line   */
    while(row_ofst-- && (cdbdp != (DBDP)0)) /* While more to move   */
        {                               /*                          */
        cdbdp = lptr->lnext;            /* Assign current dbase ptr */
        lptr = vcednline(edbuf,lptr);   /* Get next line from file  */
        }                               /*                          */
    vced->edcline = cdbdp;              /* Assign current line      */
    vced->edupval = VCEDUPDALL;         /* Update entire screen     */
    return(0);                          /* Return                   */
    }                                   /* ------------------------ */

