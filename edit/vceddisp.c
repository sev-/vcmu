/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:26
*
*   Name            vceddisp.c - display
*                                   
*   Description     Prints one line of buffer
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vceddisp(vced,wptr,lptr,start,from,to)
VCED *vced;                 /* Pointer to edit structure            */
WPTR wptr;                  /* Pointer to window for display        */
VCEDLINE *lptr;             /* Pointer to line to display           */
COUNT start;                /* Starting location                    */
COUNT from;                 /* Start lighting infomation            */
COUNT to;                   /* End lighting information             */
    {                       /* ------------------------------------ */
    FAST TEXT *sptr;        /* Pointer to window buffer             */
    COUNT offset;           /* Offset to start at in window buffer  */
    TEXT outchr;            /* Character to output                  */
    COUNT length = 0;       /* Length of current line               */
    COUNT output = 0;       /* Temporary variable for output count  */
    COUNT width;            /* Width of window                      */
    COUNT attr;             /* Attribute to print with              */
    COUNT tmp;              /* Temporary variable                   */
    TEXT *ptr;              /* Actual text of current line          */
    COUNT wcols();          /* Declare functions used               */
    width = wcols(wptr);                /* Get width                */
    attr = wptr->say_at;                /* Set default attribute    */
    length = lptr->lused;               /* Find length of line      */
    if(from >= 0)                       /* If this row lighted      */
        length = max(length,to+1);      /* Set to display to cursor */
    ptr = lptr->ltext;                  /* Point to first char      */
    ptr += start;                       /* Point to start char      */
    length -= start;                    /* Subtract for start       */
    width -= start - vced->edoffset + vced->edlmar; /* Adjust width */
    width = width-vced->edlmar;         /* Len must be < width      */
    output = 0;                         /* Initialize count variable*/
    offset = ((wptr->r_pos*wptr->width+wptr->c_pos) << 1);
    sptr = wptr->location + offset;     /* Find offset into window  */
    while((output < length) &&          /* While more characters    */
          (output < width) )            /* And more room            */
        {                               /*                          */
        if(vced->edaline != (DBDP)0)    /* If anchor dropped        */
            {                           /*                          */
            if(from >= 0)               /* If this row lighted      */
                {                       /*                          */
                tmp = output+start;     /* Temporary calculation    */
                if((tmp >= from) && (tmp <= to)) /* If highlite     */
                    attr = wptr->get_at;/* Set highlite attribute   */
                else                    /*                          */
                    attr = wptr->say_at;/* Set normal attribute     */
                }                       /*                          */
            }                           /*                          */
        if(*ptr == vcedval.tabchr)      /* If a tab character       */
            {                           /*                          */
            if(vcedval.dispctrl)        /* If display controls      */
                outchr = '+';           /* Display tab              */
            else                        /*                          */
                outchr = ' ';           /* Display space            */
            }                           /*                          */
        else if(*ptr == vcedval.tabspace)     /* If a tab space     */
            {                           /*                          */
            if(vcedval.dispctrl)        /* If display controls      */
                outchr = '.';           /* Display tabsp            */
            else                        /*                          */
                outchr = ' ';           /* Display space            */
            }                           /*                          */
        else                            /*                          */
            outchr = *ptr;              /* Display character        */
        *(sptr++) = outchr;             /* Move character           */
        *(sptr++) = attr;               /* Move attribute           */
        output++;                       /* Next space               */
        ptr++;                          /*                          */
        }                               /*                          */
    }
