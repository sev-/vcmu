/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:59
*
*   Name            vctblsel.c - table select
*                                   
*   Description     Selects a new default get table
*
*   Return Value    Returns pointer to previous default
*                   field table.
*                                   
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

GETTABLE *vctblsel(tbl)
GETTABLE *tbl;      /* Pointer to get table to clear                */
    {
    GETTABLE *retval = (GETTABLE *)0;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vctblsel:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if((tbl != (GETTABLE *) 0) &&
       (tbl != dftgettbl) )
        {
        if(tbl->tnext != (GETTABLE *) 0)
            tbl->tnext->tprevious = tbl->tprevious;
        if(tbl->tprevious != (GETTABLE *) 0)
            tbl->tprevious->tnext = tbl->tnext;
        tbl->tprevious = (GETTABLE *)0;
        tbl->tnext = dftgettbl;
        dftgettbl->tprevious = tbl;
        retval = dftgettbl;
        dftgettbl = tbl;
        }
    return(retval);
    }
