/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:52:06
*
*   Name            vcedvars.c - vcedvars
*                                   
*   Description     Tced global variables
*
**/

#include <vcstdio.h>
#include <vcdbms.h>
#define VCEDVARS
#include <vced.h>

VCEDVAL vcedval = 
    {                       /* ------------------------------------ */
    (COUNT) 132,            /* Maximum line length                  */
    (COUNT) 10,             /* Number of Pages to buffer            */
    (COUNT) 100,            /* Number of slots per page             */
    (COUNT)   0,            /* Soft Return                          */
    (COUNT)  13,            /* Hard Return                          */
    (COUNT)  14,            /* Justified Return                     */
    (COUNT)   0,            /* Use real tabs                        */
    (COUNT)   4,            /* Tab size                             */
    (COUNT)'\t',            /* Tab character                        */
    (COUNT)   0,            /* Tab space character                  */
    (COUNT)  10,            /* Number to move when shifting left    */
    (COUNT)   1,            /* Number to move when shifting up/down */
    (COUNT)   0,            /* Default Right Margin                 */
    (COUNT)   0,            /* Default Left Margin                  */
    (COUNT)   0,            /* Display control characters           */
    (COUNT)   1             /* Backup the file when saving          */
    };                      /* ------------------------------------ */

TEXT vcedfbuf[MAXLIN];      /* File buffer work area                */
TEXT vcedibuf[MAXLIN];      /* Internal buffer work area            */

#ifdef VCEDFULL

VCEDUNSTR *vcedustr = (VCEDUNSTR *)0;   /* Undo structure           */
VCEDCUTSTR *vcedscrap = (VCEDCUTSTR *)0;/* Cut buffers location     */
COUNT vcedrkeys[VCEDMAXREC];            /* Storage for keys         */
COUNT vcedcrkey = 0;                    /* Current position         */
COUNT vcedrecstat = 0;                  /* Record on or off         */

#endif
