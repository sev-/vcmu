/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:39
*
*   Name            inpblock.c - input block field
*                                   
*   Description     Gets block input
*
*   Return Value    VOID
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT inpblock(table)
GETTABLE *table;    /* Get table to input field                     */
    {
    GETITEM *gp,*gi;
    TEXT **ptr;
    GETITEM *vcfldfnd();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "inpblock:";
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
        if(gp->gcontrol & FLDSINGLE)
            {
            ptr = (TEXT **)gp->gselset;
            while(*ptr != NULLTEXT)
                {
                if(strcmp(*ptr,gp->gptr))
                    {
                    if((gi = vcfldfnd(table,*ptr,0,0)) == (GETITEM *)0)
                        break;
                    inpchktog(gi,OFF);
                    lightblk(gi);
                    }
                else
                    {
                    inpchktog(gp,ON);
                    lightblk(gp);
                    }
                ptr++;
                }
            }
        else
            {           
            inpchktog(gp,TOGGLE);
            lightblk(gp);
            }
        if(gp->gcontrol & FLDNORET)
            {
            table->tkeypress = 0;
            break;
            }
        else
            continue;
        }
    return(GOOD);
    }


