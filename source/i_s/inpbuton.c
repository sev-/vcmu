/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:40
*
*   Name            inpbuton.c - input Button field
*                                   
*   Description     Gets Button input
*
*   Return Value    VOID
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT inpbuton(table)
GETTABLE *table;    /* Get table to input field                     */
    {
    GETITEM *gp;
    COUNT *cptr;
    COUNT delay;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "inpbuton:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    gp = table->tcurnode;
    while(TRUE)
        {
        at(gp->g_row,gp->g_col);
        table->tkeypress = getone();
        if( gethk1 )
            {
            if((*gethk1)(table))
                continue;
            }
        if(table->tkeypress == spkey.fld_cleft)
            table->tkeypress = spkey.fld_left;
        if(table->tkeypress == spkey.fld_cright)
            table->tkeypress = spkey.fld_right;
        if(isexitkey(table->tkeypress))
            break;
        wat(gp->gwptr,gp->g_row,gp->g_col);
        wputattr(gp->gwptr,gp->gattrnag,gp->g_length);
        cptr = (COUNT *)gp->g_field;
        table->tkeypress = *cptr;
        wat(gp->gwptr,gp->g_row,gp->g_col);
        wputattr(gp->gwptr,gp->gattrag,gp->g_length);
        break;
        }
    return(GOOD);
    }
