/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:40
*
*   Name            vcedsave.c - save
*                                   
*   Description     Save buffer to original location
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

VOID vcedsave(edbuf)
VCEDBUF *edbuf;             /* Edit buffer                          */
    {                       /* ------------------------------------ */
    if(!edbuf->bfchange)                /* If buffer not changed    */
        return;                         /* Return nothing to save   */
    if(edbuf->bfctrl & VCED2BUF)        /* If write to buffer       */
        edbuf->bfchange = vcedtobuf(edbuf); /* Write to buffer      */
    else                                /* else                     */
        {                               /*                          */
        if(vcedval.bckupfil)            /* If backup file wanted    */
            vcedback(edbuf);            /* Make backup of file      */
        edbuf->bfchange = vcedtofil(edbuf); /* Write to file        */
        }                               /*                          */
    }                                   /* ------------------------ */

