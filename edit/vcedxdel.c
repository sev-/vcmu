/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:52:09
*
*   Name            vcedxdel.c - delete
*                                   
*   Description     Low level delete from line function
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedxdelete(vced,cline,loc)
VCED *vced;                 /* Pointer to edit structure            */
VCEDLINE *cline;            /* Pointer to line to delete            */
COUNT loc;                  /* Location of character to delete      */
    {                       /* ------------------------------------ */
    VCEDLINE *nline;        /* Pointer to temporary line            */
    COUNT cnt;              /* Counting variable                    */
    COUNT amt;              /* Amount to move                       */
    COUNT save_chr;         /* Save current column                  */
    TEXT *ptr1,*ptr2,*ptr3; /* Temporary pointers                   */
    VCEDLINE *vcedmline();  /* Declare functions used               */
    COUNT vcedllen();       /*    "        "      "                 */
    VOID vceddline();       /*    "        "      "                 */
    if(cline == (VCEDLINE *)0)          /* If no current line       */
        return(0);                      /* Return nothing to delete */
    ptr1 = ptr2 = &cline->ltext[0];     /* Set to beginning of line */
    ptr1 += loc;                        /* Increment to current char*/
    ptr2 += cline->lused;               /* Point to end of line     */
    if(loc < cline->lused)              /* If not passed end of line*/
        {                               /*                          */
        ptr3 = ptr1 + 1;                /* Point to next character  */
        if((*ptr1 == vcedval.tabspace) || /* If a real tab space    */
           (*ptr1 == vcedval.tabchr) )  /* or a real tab            */
            {                           /*                          */
            while((*ptr3 == vcedval.tabspace) && /* While tabspace  */
                  (ptr3 < ptr2) )       /* and not eol              */
                {                       /*                          */
                ptr3++;                 /* Increment starting loc   */
                cline->lused--;         /* Decrement line used      */
                }                       /*                          */
            if(*ptr1 == vcedval.tabspace)   /* If tab space         */
                vcedrmtab(&cline->ltext[0],ptr1);/* Move tab->space */
            }                           /*                          */
        while(ptr3 < ptr2)              /* While more chars to move */
            *(ptr1++) = *(ptr3++);      /* Move characters          */
        while(ptr1 < ptr2)              /* Blank all characters     */
            *(ptr1++) = 0;              /* Blank character          */
        cline->lused--;                 /* Decrement chars used     */
        cline->lused = vcedadjtab(&cline->ltext[0],loc,
                                    cline->lused); /* Adjust tabs   */
        vced->edupval |= VCEDUPDEOL;    /* Update from cur to eol   */
        }                               /*                          */
    else                                /* Else pass end of line    */
        {                               /*                          */
        if(cline->lnext != (DBDP)0)     /* If a next line merge it  */
            {                           /*                          */
            cline->lused++;             /* Adjust number of char.   */
            while(ptr2 != ptr1)         /* While more spaces to ins */
                {                       /*                          */
                *(ptr2++) = ' ';        /* Insert spaces            */
                cline->lused++;         /* Increment chars used     */
                }                       /*                          */
            nline = vcedmline(vced->edbuffer,cline->lnext); 
            cnt = loc;                  /* Set column location      */
            amt = nline->lused;         /* Number to move           */
            ptr2 = &nline->ltext[0];    /* Set to beginning of line */
            while(((cnt++) < (vced->edbuffer->bflinelen-1))/* ~ eol */
                         && amt-- )     /* and more to move         */
                {                       /*                          */
                *(ptr1++) = *(ptr2++);  /* Move character           */
                cline->lused++;         /* Adjust number of char.   */
                }                       /*                          */
            cline->lused--;             /*                          */
            cline->lused = vcedadjtab(&cline->ltext[0],loc,
                                    cline->lused); /* Adjust tabs   */
            if(amt > 0)                 /* If some left on line     */
                {                       /*                          */
                ptr1 = &nline->ltext[0];/* Point to beginning       */
                cnt = nline->lused - amt;   /* Calc nbr to clear    */
                nline->lused = amt;     /* Number remaining         */
                while(amt--)            /* While more               */
                    *(ptr1++) = *(ptr2++);  /* Move characters      */
                while(cnt--)            /* While more to clear      */
                    *(ptr1++) = '\0';   /* Clear characters         */
                nline->lused = vcedadjtab(&nline->ltext[0],0,
                                    nline->lused); /* Adjust tabs   */
                vcedrline(vced->edbuffer,nline,cline->lnext);
                }                       /* Update line              */
            else                        /* Else                     */
                vceddline(vced->edbuffer,nline->lprev,cline->lnext,
                                nline->lnext);  /* Delete line      */
            vced->edupval |= VCEDUPDALL;/* Update entire screen     */
            }                           /*                          */
        }                               /*                          */
    }                                   /* ------------------------ */

