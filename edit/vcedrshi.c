/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:38
*
*   Name            vcedrshi.c - right shift
*                                   
*   Description     Low level function used to shift string to right
*
*   Return Value    VOID
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

VOID vcedrshift(str,ofset,amount,length)
TEXT *str;                  /* Pointer to string to shift           */
COUNT ofset;                /* Starting location to shift           */
COUNT amount;               /* Number of characters to shift        */
COUNT length;               /* Length of string before shift        */
    {                       /* ------------------------------------ */
    TEXT *start;            /* Location of start of move            */
    TEXT *end;              /* End of string                        */
    TEXT *moveto;           /* Move to location pointer             */
    start = str + ofset;                /* Find starting location   */
    end = str + length - 1;             /* Find end of string       */
    moveto = end + amount;              /* Destination location     */
    while((end >= start) &&             /* While more to move       */
          (end >= str) )                /* And not past first       */
        *(moveto--) = *(end--);         /* Move character           */
    while((moveto >= start) &&          /* While more to blank      */
          (moveto >= str) )             /* And not past first       */
        *(moveto--) = '\0';             /* Blank character          */
    }                                   /* ------------------------ */


