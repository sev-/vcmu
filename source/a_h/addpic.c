/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:21
*
*   Name            addpic.c - add new picture
*                                   
*   Description     Adds a new picture character to input routines
*
*   Return Value    Returns 0 if no errors
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT addpic(pic,pfunc)
COUNT pic;                  /* New value for picture                */
PFI pfunc;                  /* Pointer to function to validate pic  */
    {                       /* ------------------------------------ */
    VCPIC *pnew;            /* Pointer to new picture structure     */
    TEXT *vcalloc();        /* Declare functions used               */
    pnew = (VCPIC *)vcalloc(1,sizeof(*pnew),vcdebug);   /* Allocate */
    pnew->picchar = pic;                /* Add new picture character*/
    pnew->picfunc = pfunc;              /* Picture function         */
    pnew->picnext = vcpicture;          /* Assign next pointer      */
    vcpicture = pnew;                   /* Make new first           */
    return(1);                          /* Return O.K.              */
    }                                   /* ------------------------ */
