/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:16
*
*   Name            clrgets.c  --  Clear pending gets
*
*   Description     This clears all pending and active gets and
*                   frees temp edit and temp pic space
*
*   Return Value    Return -1 if no gets or says in table
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT clrgets(tbl)
GETTABLE *tbl;      /* Pointer to get table to clear                */
    {
    GETITEM *target1,*target2;
    VOID vcfree();
    VOID clrsays();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "clrgets:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(tbl == (GETTABLE *) 0)
        tbl = dftgettbl;
    if( (tbl == (GETTABLE *) 0) ||
        ( (tbl->thead == (GETITEM *) 0) && 
          (tbl->tsayhead == (SAYITEM *) 0) ) )
        {
        vcerror=NOGETS;       
        return(-1);
        }
    target1=tbl->thead;
    while( target1 )
        {
        if( (target1->gtmppic != NULLTEXT) && 
           (target1->gtmppic != target1->g_picture) )
            {
            vcfree(target1->gtmppic,vcdebug);
            target1->gtmppic = NULLTEXT;
            }
        if( (target1->gtmpfld != NULLTEXT) && 
           (target1->gtmpfld != target1->g_field) )
            {
            vcfree(target1->gtmpfld,vcdebug);
            target1->gtmpfld = NULLTEXT;
            }
        target2=target1->gnext;
        vcfree(target1,vcdebug);
        target1=target2;
        }
    clrsays(tbl->tsayhead);
    tbl->tsayhead = (SAYITEM *)0;
    tbl->tsaytail = (SAYITEM *)0;        
    tbl->thead = (GETITEM *)0;
    tbl->ttail = (GETITEM *)0;
    tbl->tcurnode = (GETITEM *)0;
    return(0);
    }

VOID clrsays(snptr)
SAYITEM *snptr;
    {
    VOID vcfree();
    SAYITEM *tmp;
#ifdef VCDEBUG
    vcdebug = "clrsays:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    while(snptr != (SAYITEM *) 0)
        {
        tmp = snptr->snnext;
        vcfree(snptr,vcdebug);
        snptr = tmp;
        }
    }

