/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:27
*
*   Name            gettype.c  --  Get type of input
*
*   Description     Evaluates the picture to decide what kind of input
*                   is required
*
*   Return Value    Returns 0 for ltorinp 1 for rtolinp
*
**/

#include <vcstdio.h>

COUNT gettype(pic)
TEXT *pic;          /* Picture to evalute                           */
    {
    COUNT n=0;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "gettype:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    while(pic[n])
        {
        if(pic[n]=='#')
            {
            return(1);
            }
        n++;
        }
    return(0);
    }


