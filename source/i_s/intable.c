/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:49
*
*   Name            intable.c --  In the node ?
*
*   Description     Checks to see if the {str} is in the node
*                   pointed to by {node}.  Also sets the {value}
*                   pointer to the value assigned to {str}
*
*   Return Value    Returns NULL if not in the node else
*                   return to the node pointed to by str value
*
**/

#include <vcstdio.h>

struct KEYTBLNODE *intable(node,str,value)
struct KEYTBLNODE *node;
COUNT str;
COUNT *value;
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "intable:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(str == 0)
        str = 0x100;
    if(node == (struct KEYTBLNODE *) 0)
        return((struct KEYTBLNODE *) 0);
    else
        {
        while( (node->key != str) && (node->othkey != (struct KEYTBLNODE *)0) )
            node = node->othkey;
        if(node->key == str)
            {
            *value = node->val;
            return(node->nxtkey);
            }
        else
            return((struct KEYTBLNODE *) 0);
        }
    }


