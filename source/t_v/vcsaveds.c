/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:48
*
*   Name            vcsaveds.c  --  Saves Edits
*
*   Description     This function copys or translates the edited copy
*                   of the data into the real data location. This 
*                   function is not called if xreadgets is exited with
*                   spkey.abort.
*
*   Return Value    VOID
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

VOID vcsaveds(gt)
GETTABLE *gt;       /* Get table to use                             */
    {
    GETITEM *gi;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcsaveds:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    gi = gt->thead;
    while(gi != (GETITEM *)0)
        {
        vctoreal(gi);
        gi=gi->gnext;
        }
    }



