/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:33
*
*   Name            hasdata.c  --  Field has data
*
*   Description     Evaluates a field to see if it contains any 
*                   characters ignores special characters from the
*                   picture.
*
*   Return Value    Returns False if empty else True if has data
*
**/

#include <vcstdio.h>

COUNT hasdata(fld,pic)
TEXT *fld,*pic;
    {
    COUNT evalpic();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "hasdata:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    while( *fld && *pic )
        {
        if( evalpic(*pic) && (*fld != SPACE) )
            return(TRUE);
        fld++;
        pic++;
        }
    return(FALSE);
    }


