/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:42
*
*   Name            dsorttbl.c  --  Delete sort table
*
*   Description     This function deletes the sort table used
*                   to speed up reading.
*
*   Return Value    Returns -1 if error
*
**/

#include <vcstdio.h>

#ifdef TERMCAP

VOID dsorttbl()
    {
    VOID xdeltable();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "dsorttbl:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(sorted != (struct KEYTBLNODE *)0)
        xdeltable(sorted);
    sorted = (struct KEYTBLNODE *) 0;
    }

VOID xdeltable(node)
struct KEYTBLNODE *node;
    {
    VOID vcfree();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xdeltable:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( node->othkey != (struct KEYTBLNODE *) 0)
        xdeltable(node->othkey);
    if( node->nxtkey != (struct KEYTBLNODE *) 0)
        xdeltable(node->nxtkey);
    vcfree(node,vcdebug);
    }
#endif


