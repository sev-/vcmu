/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:45
*
*   Name            vcedsins.c - insert into string
*                                   
*   Description     Low level function to insert character
*                   into string
*
*   Return Value    VOID
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

VOID vcedsins(str,loc,chr,length)
TEXT *str;                  /* Pointer to string to insert          */
COUNT loc;                  /* Location to insert                   */
COUNT chr;                  /* Character to insert                  */
COUNT length;               /* Length of string before insert       */
    {                       /* ------------------------------------ */
    TEXT *newchr;           /* Location to put new character        */
    VOID vcedsrshift();     /* Declare functions used               */
    vcedrshift(str,loc,(COUNT)1,length);/* Shift string             */
    newchr = str + loc;                 /* Find offset              */
    *newchr = (TEXT)chr;                /* Insert character         */
    }                                   /* ------------------------ */

