/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:20
*
*   Name            getsay.c
*
*   Description     This function displays an input item
*
*   Return Value    VOID
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS

#include <vcstdio.h>

VOID getsay(gi)
GETITEM *gi;
    {
    COUNT inptype;
    COUNT haveauth();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "getsay:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(((haveauth(gi->gfldtyp & 127,FLDEDIT)) ||
        (haveauth(gi->gfldtyp & 127,FLDVIEW))) &&
        !(gi->gcontrol & FLDHIDDEN) )
        {
        inptype = (gi->gfldtyp >> 7) & 15;
        if(datalight[inptype] != NULLFUNC)
            (*datalight[inptype])(gi);
        }
    }




