/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:15:55
*
*   Name            tblalloc.c  --  Allocate Get Table 
*
*   Description     Allocates the memory for a get table entry
*                   installs default functions
*
*   Return Value    Returns a pointer to the new get table or 
*                   NULL if error
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

GETTABLE *tblalloc(symnam,ctrl,seq)
TEXT *symnam;       /* Symbolic name for get table                  */
COUNT ctrl;         /* Control byte for get table                   */
PFI seq;            /* Pointer to sequencing function               */
    {
    GETTABLE *np,*node;
    TEXT *vcalloc();
    COUNT seqgetstd();
    COUNT strlen();
    TEXT *strcpy();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "tblalloc:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(ctrl == -1)
        ctrl = dtblctrl;
    if(seq == NULLFUNC)
        seq = seqgetstd;
    if( (node=(GETTABLE *)vcalloc(1,sizeof(GETTABLE),vcdebug)) ==
                         (GETTABLE *)0 )
        {
        vcerror=NOTBLMEM;
        return((GETTABLE *)0);
        }
    if( symnam )
        {
        if( (node->table_name=vcalloc(strlen(symnam)+1,sizeof(TEXT),
                vcdebug)) == NULLTEXT)
            {
            vcerror = NONAMMEM;
            return((GETTABLE *)0);
            }
        strcpy(node->table_name,symnam);
        }
    node->tstatus = 0;
    node->tmagic = GETTBLMAGIC;
    node->tnext = (GETTABLE *) 0;
    node->tctrl = ctrl;
    node->tgetseq = seq;
    if( dftgettbl == (GETTABLE *) 0)
        {
        dftgettbl = node;
        node->tprevious = (GETTABLE *) 0;
        }
    else
        {
        np = dftgettbl;
        while(np->tnext != (GETTABLE *) 0)
            np=np->tnext;
        np->tnext=node;
        node->tprevious = np;
        }
    return(node);
    }
