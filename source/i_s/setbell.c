/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:02
*
*   Name            setbell.c  --  set bell on or off
*
*   Description     This function sets the global variable that controls
*                   whether the bell is on or off.
*
*   Return Value    Returns old mode or -1 if error
*
**/

#include <vcstdio.h>

COUNT setbell(mode)
PFAST COUNT mode;   /* Set bel ON, OFF, or TOGGLE                   */
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "setbell:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    switch(mode)
        {
        case ON:
            bellstat = ON;
            break;
        case OFF:
            bellstat = OFF;
            break;
        case TOGGLE:
            if(bellstat == ON)
                bellstat = OFF;
            else
                bellstat = ON;
            break;
        default:
            return(-1); /* error */
        }
    return(0);
    }


