/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:45
*
*   Name            wstyleop.c - wstyle open
*                                   
*   Description     Open window with style
*
*   Return Value    Returns window pointer or (WPTR)0 if error
*                                   
**/

#include <vcstdio.h>

WPTR wstyleopen(style,ur,uc,lr,lc,title)
TEXT *style;                /* Pointer to Name of Window Style      */
COUNT ur;                   /* Upper Right                          */
COUNT uc;                   /* Upper Left                           */
COUNT lr;                   /* Lower Right                          */
COUNT lc;                   /* Lower Left                           */
TEXT *title;                /* Pointer to Title for window          */
    {                       /* ------------------------------------ */
    WPTR wdefinit();        /* Declare functions used               */
    return(wdefinit(NULLTEXT,style,title,NULLTEXT,NULLTEXT,NULLTEXT,
                    ur,uc,lr,lc,0,0,0,0));  /* Open window / return */
    }                                       /* -------------------- */


