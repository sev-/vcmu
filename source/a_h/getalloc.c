/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:11
*
*   name            getalloc.c  --  Allocate space for get
*
*   Description     This function allocates space for an entry in the
*                   get table.
*
*   Return Value    Returns NULL if error 
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

GETITEM *getalloc()
    {
    TEXT *vcalloc();
    GETITEM *node;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "getalloc:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    node=(GETITEM *)vcalloc(1,sizeof(GETITEM),"getalloc:");
    if( node == (GETITEM *) 0 )
        {
        vcerror = NOGETMEM;
        return((GETITEM *) 0);
        }
    node->gmagic=GETNODEMAGIC;
    return(node);
    }


