/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:12
*
*   Name            vcedadjt.c - Adjust tabs
*                                   
*   Description     Adjusts the line for spacing caused by real tabs
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedadjtab(str,start,length)
TEXT *str;                  /* Pointer to string to insert          */
COUNT start;                /* Starting location                    */
COUNT length;               /* Length of string before adjustment   */
    {                       /* ------------------------------------ */
    TEXT *curloc;           /* Current working location             */
    COUNT tval;             /* Used to calculate tab locations      */
    curloc = str + start;               /* Point to first character */
    while(start < length)               /* While more to check      */
        {                               /*                          */
        if(*curloc == vcedval.tabchr)   /* Found tab                */
            {                           /*                          */
            while(TRUE)                 /* While more to check      */
                {                       /*                          */
                start++;                /* Look at next location    */
                curloc++;               /* Look at next character   */
                tval = start / vcedval.tabsize;  /* Divide tab      */
                if(start == (tval * vcedval.tabsize)) /* On tab     */
                    break;               /* Stop                    */
                if(*curloc != vcedval.tabspace) /* Ins tabspace ?   */
                    {                   /*                          */
                    vcedsins(str,start,vcedval.tabspace,length);
                    length++;           /* Add to length            */
                    }                   /*                          */
                }                       /*                          */
            while((start < length) &&   /* More to check            */
                  (*curloc == vcedval.tabspace)) /* And tabspace    */
                {                       /*                          */
                vcedlshift(str,start,(COUNT)1,length); /* Delete    */
                length--;               /* Shorten line             */
                }                       /*                          */
            break;                      /* Finished                 */
            }                           /*                          */
        start++;                        /* Look at next location    */
        curloc++;                       /* Look at next character   */
        }
    return(length);                     /* Return new line length   */
    }                                   /* ------------------------ */

