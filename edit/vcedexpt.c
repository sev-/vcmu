/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:43
*
*   Name            vcedexpt.c - expand tabs
*                                   
*   Description     Low level function to expand tabs
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

VOID vcedexptab(edbuf,tloc,cnt,retchr)
VCEDBUF *edbuf;             /* Edit buffer                          */
TEXT *tloc;                 /* String to expand tabs                */
COUNT cnt;                  /* Current length of buffer             */
COUNT retchr;               /* Return character                     */
    {                       /* ------------------------------------ */
    TEXT *ptr;              /* Working buffer pointer               */
    TEXT *dest;             /* Working buffer pointer               */
    TEXT *eptr;             /* Pointer for return character         */
    COUNT tval;             /* Used to calculate tab locations      */
    COUNT used = 0;         /* Number of characters used on line    */
    ptr = tloc;                         /* Point to top of line     */
    dest = vcedibuf;                    /* Point to destination     */
    vcedempty(vcedibuf,edbuf->bflinelen);/* Empty line location     */
    while(cnt--)                        /* While more characters    */
        {                               /*                          */
        if((*ptr == vcedval.tabchr) &&  /* If tab character         */
           ((used + vcedval.tabsize) > edbuf->bflinelen - 1) )/*room*/
           break;                       /* Put on next line         */
        *(dest++) = *ptr;               /* Move character           */
        used++;                         /* Increment number used    */
        if(*ptr == vcedval.tabchr)      /* If tab character         */
            {                           /*                          */
            while(TRUE)                 /* While more to move       */
                {                       /*                          */
                tval = used / vcedval.tabsize; /* Divide tab        */
                if(used == (tval * vcedval.tabsize)) /* On tab      */
                    break;              /* Stop                     */
                vcedsins(vcedibuf,used,vcedval.tabspace,used);/* Ins*/
                used++;                 /* Increment number used    */
                dest++;                 /* Increment destination    */
                }                       /*                          */
            }                           /*                          */
        ptr++;                          /* Point to next character  */
        if(used > (edbuf->bflinelen - 1))/* Is there room on line   */
           break;                       /* Put on next line         */
        }                               /*                          */
    eptr = vcedibuf + edbuf->bflinelen -1;  /* Point to end of line */
    if(cnt > 0)                         /* If some left on line     */
        *eptr = vcedval.softret;        /* Assign soft return       */
    else                                /*                          */
        *eptr = retchr;                 /* Assign passed value      */
    vcedaline(edbuf,vcedibuf,used);     /* Add line to database     */
    if(cnt > 0)                         /* If some left on line     */
        vcedexptab(edbuf,ptr,cnt,retchr); /* Add next part of line  */
    }                                   /* ------------------------ */
        

