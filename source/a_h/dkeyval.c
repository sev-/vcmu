/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:40
*
*   Name            dkeyval.c --  Delete key value from table
*
*   Description     Deletes an item from the keyboard table.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

static struct KEYTBLNODE **tstack,**bstack,**curstack;

VOID dkeyval(val)
COUNT val;
    {
    TEXT *vcalloc();
    VOID xdkeyval();
    VOID vcfree();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "dkeyval:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( (tstack = ( struct KEYTBLNODE **) vcalloc(500,sizeof(TEXT *),
                                     vcdebug)) == (struct KEYTBLNODE **) 0)
        return;
    curstack = tstack;
    bstack = tstack + 500;
    xdkeyval(vcterm.table,val);
    vcfree(tstack,vcdebug);
    }

VOID pushknode(node)
struct KEYTBLNODE *node;
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "pushknode:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    *(++curstack) = node;
    if(curstack == bstack)
        curstack--;
    }

struct KEYTBLNODE *popknode()
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "popknode:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return( *(curstack--));
    }

VOID xdkeyval(node,val)
struct KEYTBLNODE *node;
COUNT val;
    {
    struct KEYTBLNODE *popknode();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xdkeyval:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(node->val != val)
        {
        if(node->nxtkey != (struct KEYTBLNODE *) 0)
            {
            pushknode(node);
            xdkeyval(node->nxtkey,val);
            }
        else
            {
            do
                node = popknode();
            while((node->othkey == (struct KEYTBLNODE *)0) &&
                                     (curstack > tstack));
            if(node->othkey != (struct KEYTBLNODE *) 0)
                xdkeyval(node->othkey,val);
            }
        }
    else
        {
        node->val = 0;
        }
    }


