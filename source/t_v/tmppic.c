/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:33
*
*   Name            tmppic.c  --  Allocate temporary picture
*
*   Description     This builds a temporary picture if the input field
*                   has a NULL for a picture. This terminal errors if
*                   there is not enough memory to allocate the picture.
*
*   Return Value    Returns pointer to temporary picture
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

TEXT *tmppic(fld,picchr)
TEXT *fld;          /* Field that need a temporary picture          */
TEXT picchr;        /* Character to use on temporary picture        */
    {
    TEXT *pic,*vcalloc();
    COUNT n;
    COUNT strlen();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "tmppic:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( (pic = vcalloc((UCOUNT)1,(UCOUNT)( n = strlen(fld))+1,vcdebug))
                      == NULLTEXT )
        {
        vcerror = NOTMPMEM;
        return(NULLTEXT);
        }
    pic[n--] = '\0';
    if( picchr == 0 )
       picchr = 'x';
    while(n >= 0)
        pic[n--] = picchr;
    return(pic);
    }



