/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:01
*
*   Name            keyrdy.c  --  Check and see if key is ready
*
*   Description     This function checks to see if a key is ready for
*                   input.  getone() uses this to work a loop function
*                   while awaiting a key.
*
*   Return Value    True if key ready - False if no key ready
*
**/

#include <vcstdio.h>

COUNT keyrdy()
    {
    COUNT repeat = 1;
    COUNT retval;
    COUNT xkeyrdy();
    COUNT bufkdy();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xkeyrdy:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( bufkdy() )
        return((COUNT)1);
#ifdef REPEAT_KEYRDY
    repeat = max(1,vcterm.zt);
#endif
    while(repeat--)
        {
        retval = xkeyrdy();
        if(retval)
            break;
        if(vcterm.zd > 0)
            vcnap(vcterm.zd);
        }
    return(retval);
    }



