/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:57
*
*   Name            evalpic.c  --  evaluate special characters
*
*   Description     This function checks to see if the character
*                   is include in the special characters.
*
*   Return Value    Returns False if not picture character
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT evalpic(c)
COUNT c;                /* Character to evaluate                    */
    {                   /* ---------------------------------------- */
    COUNT retval = FALSE;   /* Assign return value to false         */
    VCPIC *pcur;            /* Pointer to new picture structure     */
#ifdef VCDEBUG
    vcdebug = (TEXT *) "evalpic:";      /* Assign function name     */
    if(vcdbfunc != NULLFUNC)            /* If debug function        */
        (*vcdbfunc)(CONTINUE);          /* Call debug function      */
#endif
    pcur = vcpicture;                   /* Start at top             */
    while(pcur != (VCPIC *)0)           /* While more to check      */
        {                               /*                          */
        if(pcur->picchar == c)          /* Is this it               */
            {                           /*                          */
            retval = TRUE;              /* Return found             */
            break;                      /* Exit loop                */
            }                           /*                          */
        pcur = pcur->picnext;           /* Look at next             */
        }                               /*                          */
    return(retval);                     /* Return results           */
    }                                   /* ------------------------ */

