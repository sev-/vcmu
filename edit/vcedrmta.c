/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:36
*
*   Name            vcedrmta.c - remove tabs
*                                   
*   Description     Removes tabs from file
*
*   Return Value    VOID
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

VOID vcedrmtab(ptr1,ptr2)
TEXT *ptr1;                 /* Pointer to beginning of line         */
TEXT *ptr2;                 /* Pointer to starting location         */
    {                       /* ------------------------------------ */
    while((*ptr2 == vcedval.tabspace)   /* While more to change     */
          && (ptr2 >= ptr1)  )          /* and not passed beginning */
        *(ptr2--) = ' ';                /* Change to spaces         */
    if(*ptr2 == vcedval.tabchr)         /* Stoped on tab            */
        *ptr2 = ' ';                    /* Change to space          */
    }                                   /* ------------------------ */

