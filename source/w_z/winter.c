/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:41
*
*   Name            winter.c  --  Check to see if two window intersect
*
*   Description     Check to see if two window intersect used 
*                   throughout the program where ever necessary
*
*   Return Value    Return 1 if intersect
*
**/

#include <vcstdio.h>

#ifdef WINDOW

COUNT winter(wptr,wptr2)
PFAST WPTR wptr;    /* Pointer to first window                      */
PFAST WPTR wptr2;   /* Pointer to second window                     */  
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "winter:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if((wptr == (WPTR)0) || (wptr2 == (WPTR)0) )
        return(0);
    if((wptr2->lower_r < wptr->upper_r) ||
        (wptr2->upper_r > wptr->lower_r) ||
        (wptr2->lower_c < wptr->upper_c) ||
        (wptr2->upper_c > wptr->lower_c) )
        return(0);
    return(1);
    }

#endif


