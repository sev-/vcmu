/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:37
*
*   Name            picok.c  --  Check for good key
*
*   Description     Low level function used by input routines to
*                   check for valid key. returns 1 if the key is
*                   ok else returns 0.
*
*   Return Value    Returns True if ok else False
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT picok(ch,pic)
TEXT ch;                    /* Character to check                   */
TEXT pic;                   /* Picture character to evaluate        */
    {                       /* ------------------------------------ */
    COUNT retval = FALSE;   /* Assign return value to false         */
    VCPIC *pcur;            /* Pointer to new picture structure     */
#ifdef VCDEBUG
    vcdebug = (TEXT *) "pickok:";       /* Assign function name     */
    if(vcdbfunc != NULLFUNC)            /* If debug function        */
        (*vcdbfunc)(CONTINUE);          /* Call debug function      */
#endif
    pcur = vcpicture;                   /* Start at top             */
    while(pcur != (VCPIC *)0)           /* While more to check      */
        {                               /*                          */
        if(pcur->picchar == pic)        /* Is this it               */
            {                           /*                          */
            retval = (*pcur->picfunc)(ch);  /* Check character      */
            break;                      /* Exit loop                */
            }                           /*                          */
        pcur = pcur->picnext;           /* Look at next             */
        }                               /*                          */
    return(retval);                     /* Return results           */
    }                                   /* ------------------------ */


