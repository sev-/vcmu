/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:32
*
*   Name            numstrcpy.c  --  Copy one number string to another
*
*   Description     Takes two string representations and copies the
*                   source into the destination. Destination is padded
*                   with zeros
*
*   Return Value    Returns 0
*
**/

#include <vcstdio.h>

COUNT numstrcpy(dest,srce)
TEXT *dest;         /* Destination numeric string                   */
TEXT *srce;         /* Source numeric string                        */
    {
    TEXT *sp,*dp,*sdp,*ddp;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "numstrcpy:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    sp=srce;
    dp=dest;
    while( sp && *sp && *sp!='.' )
        sp++;
    while( dp && *dp && *dp!='.' )
        dp++;
    ddp = dp;
    sdp = sp;
    if( *dp=='.' )
        {
        dp++;
        if( *sp )
            sp++;
        while( *dp && *sp )
            *(dp++) = *(sp++);
        while( *dp )
            *(dp++) = '0';
        }
    dp=ddp;
    sp=sdp;
    dp--;
    sp--;
    while( dp >= dest && sp >= srce )
        *(dp--) = *(sp--);
    if( dp >= dest )
        *(dp--)=' ';
    return(0);
    }



