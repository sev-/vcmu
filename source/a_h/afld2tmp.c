/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:33
*
*   Name            afld2tmp.c  --  Refresh all gettable items
*
*   Description     This refreshs all gettables items from the
*                   orginal locations
*
*   Return Value    Return -1 if no gets or says in table
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT afld2tmp(tbl,flag)
GETTABLE *tbl;      /* Pointer to get table to clear                */
COUNT flag;         /* Flag 1 refresh screen                        */
    {
    GETITEM *target1;
    COUNT fld2tmp();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "afld2tmp:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(tbl == (GETTABLE *) 0)
        tbl = dftgettbl;
    if( (tbl == (GETTABLE *) 0) ||
        (tbl->thead == (GETITEM *) 0) )
        {
        vcerror=NOGETS;
        return(-1);
        }
    if(tbl->tstartnode != (GETITEM *)0)
        target1 = tbl->tstartnode;
    else
        target1 = tbl->thead;
    while( target1 )
        {
        fld2tmp(target1,flag);
        target1 = target1->gnext;
        }
    return(0);
    }

