/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:21
*
*   Name            mapstr.c  --  Builds an input map
*
*   Description     This function inserts the non special characters
*                   from the picture into the string making them a
*                   part of the string even if no input is done
*
*   Return Value    VOID
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

VOID mapstr(gi)
GETITEM *gi;                /* Get item to map                      */
    {                       /* ------------------------------------ */
    COUNT x,n;
    COUNT strlen();
    COUNT evalpic();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "mapstr:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if((n = strlen(gi->gtmpfld)) < (x = strlen(gi->gtmppic)))
        x = n;
    for(n=0;n<x;n++)
        {
        if(evalpic(gi->gtmppic[n]))
            {
            gi->gcndx = gi->gbegndx = n;
            break;
            }
        }
    for(n=x-1;n>=0;n--)
        {
        if(evalpic(gi->gtmppic[n]))
            {
            gi->gendndx=n;
            break;
            }
        }
    }



