/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:27
*
*   Name            vcedprtb.c - print buffer
*                                   
*   Description     Draws entire buffer to window
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedprtbuf(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    VCEDLINE *lptr = (VCEDLINE *)0; /* Pointer to current line      */
    VCEDBUF *edbuf;         /* Edit buffer                          */
    DBDP cdbdp;             /* Current data base data pointer       */
    LONG crow;              /* Current row in file                  */
    COUNT to,from;          /* Highlight from to variables          */
    COUNT row = 0;          /* Current row                          */
    COUNT depth;            /* Depth of current window              */
    WPTR wptr;              /* Current window                       */
    VCEDLINE *vcednline();  /* Declare functions used               */
    VCEDLINE *vcedgline();  /*    "        "      "                 */
    VOID vcedsetfta();      /*    "        "      "                 */
    edbuf = vced->edbuffer;             /* Get buffer pointer       */
    wptr = vced->edwptr;                /* Window to use            */
    depth = wrows(wptr);                /* Get depth                */
    woff();                             /* Freeze output to screen  */
    werase(wptr,-1);                    /* Erase Window             */
    cdbdp = vced->edtline;              /* Assign current dbase ptr */
    if(cdbdp != (DBDP)0);               /* If there is a top line   */
        lptr = vcedgline(edbuf,cdbdp);  /* Get top of screen line   */
    crow = vced->edtrow;                /* Start at top row         */
    while((lptr != (VCEDLINE *)0) &&    /* While more lines         */
          (row < depth) )               /*  and not at bottom       */
        {                               /*                          */
        if(vced->edaline != (DBDP)0)    /* If anchor dropped        */
            vcedsetfta(vced,crow,&from,&to); /* Find settings       */
        wat(wptr,row++,vced->edlmar);   /* Next row                 */
        vceddisp(vced,wptr,lptr,vced->edoffset,from,to); /* Disp lin*/
        cdbdp = lptr->lnext;            /* Assign current dbase ptr */
        lptr = vcednline(edbuf,lptr);   /* Get next line of file    */
        crow++;                         /* Looking at next line     */
        }                               /*                          */
#ifdef IBM
    wdoctrl->wfreeze = FALSE;           /* Turn on updates          */
    wstack(wptr);                       /* Redraw window            */
    vca_put(0,0,wscreen,vcterm.rows*vcterm.cols);   /* Put on screen*/
#else
    won();                              /* Turn on window           */
#endif 
    }                                   /* ------------------------ */

VOID vcedsetfta(vced,crow,from,to)
VCED *vced;                 /* Pointer to edit structure            */
LONG crow;                  /* Current row evaluating               */
COUNT *from;                /* Starting location                    */
COUNT *to;                  /* Ending location                      */
    {                       /* ------------------------------------ */
    WPTR wptr;              /* Current window pointer               */
    wptr = vced->edwptr;                /* Window to use            */
    *from = -1;                         /* Set from to -1           */
    if(crow == vced->edcrow)            /* If on current line       */
        {                               /*                          */
        if(vced->edarow < vced->edcrow) /* If previous to this line */
            {                           /*                          */
            *from = 0;                  /* From the first position  */
            *to = vced->edcchar;        /* To the current character */
            }                           /*                          */
        else if(vced->edarow == vced->edcrow) /* If on row          */
            {                           /*                          */
            *from = min(vced->edcchar,vced->edachar);/* Start       */
            *to = max(vced->edcchar,vced->edachar);  /* End         */
            }                           /*                          */
        else                            /*                          */
            {                           /*                          */
            *from = vced->edcchar;      /* From the current pos.    */
            *to = vcedval.linlen;       /* To the end of line       */
            }                           /*                          */
        }                               /*                          */
    else if(crow == vced->edarow)       /* if on anchor row         */
        {                               /*                          */
        if(vced->edcrow < vced->edarow) /* If current previous      */
            {                           /*                          */
            *from = 0;                  /* From the first position  */
            *to = vced->edachar;        /* To the anchor position   */
            }                           /*                          */
        else                            /*                          */
            {                           /*                          */
            *from = vced->edachar;      /* From the current pos.    */
            *to = vcedval.linlen;       /* To the end of line       */
            }                           /*                          */
        }                               /*                          */
    else if(((crow > vced->edarow) && (crow < vced->edcrow)) ||
            ((crow < vced->edarow) && (crow > vced->edcrow)) )
        {                               /*                          */
        *from = 0;                      /* From beginning of line   */
        *to = vcedval.linlen;           /* To the end of line       */
        }                               /*                          */
    }
