/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:46
*
*   Name            vcedfrmb.c - from buffer
*                                   
*   Description     Moves information from buffer into edit
*                   file structure
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedfrmbuf(edbuf)
VCEDBUF *edbuf;             /* Edit buffer                          */
    {                       /* ------------------------------------ */
    COUNT cnt;              /* Counting variable                    */
    COUNT retchr;           /* Return character                     */
    TEXT *mptr;             /* Current location pointer             */
    VOID vcedexptab();      /* Declare functions used               */
    mptr = edbuf->bfbuffer; /* Start at beginning                   */
    if(mptr == NULLTEXT)                /* If buffer NULL           */
        return(0);                      /* Return                   */
    while(*mptr != '\0')                /* While not at end of buf. */
        {                               /*                          */
        cnt = 0;                        /* Zero number of characters*/
        vcedempty(vcedfbuf,edbuf->bflinelen); /* Empty work buffer  */
        while((*mptr != '\n') && (*mptr != '\0') && (cnt < edbuf->bflinelen-2))
            vcedfbuf[cnt++] = *(mptr++);/* Move to temporary buffer */
        if(*mptr == '\n')               /* If new line character    */
            retchr = vcedval.hardret;   /* Has a hard return        */
        else                            /*   or                     */
            retchr = vcedval.softret;   /* Has a soft return        */
        if(cnt || (*mptr != '\0'))      /* If some char or not eof  */
            vcedexptab(edbuf,vcedfbuf,cnt,retchr);/* Expand & save  */
        mptr++;                         /* Point to next character  */
        }                               /*                          */
    return(0);                          /* Return no errors         */
    }                                   /* ------------------------ */

