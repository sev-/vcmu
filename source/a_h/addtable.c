/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:25
*
*   Name            addtable.c --  Add a node to a table
*
*   Description     Adds a item to a table this table function
*                   is used for sorting and for the keyboard 
*                   input
*
*   Return Value    Return -1 if error or return the number added
*                   to the table for this entry or the number 
*                   currently in the table for this entry
*
**/

#define VCERROR_DEFS

#include <vcstdio.h>

COUNT addtable(node,str,value)
struct KEYTBLNODE **node;
TEXT *str;
COUNT value;
    {
    TEXT *vcalloc();
    struct KEYTBLNODE *newnode,*next;
    COUNT key;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "addtable:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    key = *str;
    if(key == 0xff)
        key = 0x100;
    if(*node == (struct KEYTBLNODE *) 0)
        {
        if( (newnode = (struct KEYTBLNODE *) 
              vcalloc(1,sizeof(struct KEYTBLNODE),vcdebug)) == 
                                         (struct KEYTBLNODE *) 0)
            {
            vcerror=NODEMEM;
            return(-1);
            }
        *node = (struct KEYTBLNODE *) newnode;
        newnode->key = key;
        str++;
        if(*str == '\0')
            {
            newnode->val = value;
            return(value);
            }
        else
            return(addtable(&newnode->nxtkey,str,value));
        }
    else
        {
        next = *node;
        while( (next->key != key) && 
               (next->othkey != (struct KEYTBLNODE *)0) )
            next = next->othkey;
        if(next->key == key)
            {
            str++;
            if(*str == '\0')
                {
                if(next->val)
                    return(next->val);
                else
                    return(next->val = value);
                }
            else
                return(addtable(&next->nxtkey,str,value));
            }
        else
            return(addtable(&next->othkey,str,value));
        }
    }
