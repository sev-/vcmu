/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:28
*
*   Name            delpic.c - deletes input picture
*                                   
*   Description     Deletes an input picture character
*
*   Return Value    Returns 0 if no errors
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT delpic(pic)
COUNT pic;                  /* New value for picture                */
    {                       /* ------------------------------------ */
    COUNT retval = TRUE;    /* Assign return value to false         */
    VCPIC *pcur;            /* Pointer to new picture structure     */
    VCPIC *pprv;            /* Pointer to current picture           */
    pcur = vcpicture;                   /* Start at top             */
    while(pcur != (VCPIC *)0)           /* While more to check      */
        {                               /*                          */
        if(pcur->picchar == pic)        /* Is this it               */
            break;                      /* Exit loop                */
        pprv = pcur;                    /* Save previous            */
        pcur = pprv->picnext;           /* Look at next             */
        }                               /*                          */
    if(pcur != (VCPIC *)0)              /* If found                 */
        {                               /*                          */
        if(pcur == vcpicture)           /* If head                  */
            vcpicture = pcur->picnext;  /* Make next top and pop    */
        else                            /*                          */
            pprv->picnext = pcur->picnext;  /* Point around char.   */
        vcfree(pcur,vcdebug);           /* Free node                */
        retval = FALSE;                 /* Return no errors         */
        }                               /*                          */
    return(retval);                     /* Return results           */
    }                                   /* ------------------------ */
