/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:17
*
*   Name            clrtbl.c  --  Clears gets and gettable
*
*   Description     This clears the gettable and all information
*                   associated with the table.
*
*   Return Value    Return -1 if no gets or says in table
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT clrtbl(tbl)
GETTABLE *tbl;      /* Pointer to get table to clear                */
    {
    VOID vcfree();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "clrtbl:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(tbl == (GETTABLE *) 0)
        tbl = dftgettbl;
    if(tbl == (GETTABLE *) 0)
        {
        vcerror=NOGETS;       
        return(-1);
        }
    clrgets(tbl);
    if(tbl->tnext != (GETTABLE *) 0)
        tbl->tnext->tprevious = tbl->tprevious;
    if(tbl->tprevious != (GETTABLE *) 0)
        tbl->tprevious->tnext = tbl->tnext;
    if( tbl == dftgettbl)
        dftgettbl = tbl->tnext;
    tbl->tnext=tbl->tprevious=(GETTABLE *) 0;
    if(tbl->table_name != NULLTEXT)
        vcfree(tbl->table_name,vcdebug);
    vcfree(tbl,vcdebug);
    return(0);
    }
