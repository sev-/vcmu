/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 9/2/90 at 22:04:19
*
*   Name            initchk - Initialize check field
*                                   
*   Description     Start check field
*
*   Return Value    VOID
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

VOID initchk(gi)
GETITEM *gi;
    {
    TEXT *vcalloc();
    VOID inpchkpic();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "initchk:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(gi->g_picture == gi->gtmppic)
        gi->gtmppic = vcalloc(sizeof(TEXT),strlen(gi->g_picture)+1,vcdebug);
    inpchkpic(gi);
    }





