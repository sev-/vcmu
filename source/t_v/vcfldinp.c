/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:40
*
*   Name            vcfldinp.c - Get a single field
* 
*   Description     Gets a single field is the field is both
*                   FLDHIDDEN & FLDSKIP field is blanked after
*                   exiting.
*
*   Return Value    Returns key that caused exit
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT vcfldinput(table,fld,ofset)
GETTABLE *table;
TEXT *fld;
COUNT ofset;
    {                       /* ------------------------------------ */
    COUNT retval;
    TEXT *oldhlp;
    COUNT isskip = FALSE;
    GETITEM *vcfldgo();
    COUNT getfld();
    VOID vcfldblk();
    VOID vcflush();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcfldinput:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(table == (GETTABLE *)0)
        table = dftgettbl;
    if(vcfldgo(table,fld,ofset) == (GETITEM *)0)
        return(-1);
    table->tcurnode = table->tstartnode;
    if(table->tcurnode->gcontrol & FLDSKIP)
        {
        isskip = TRUE;
        table->tcurnode->gcontrol &= ~FLDSKIP;
        }
    if(vcstatus != NULLFUNC)
        (*vcstatus)(table->tcurnode->g_msg,-1);
    if(table->tcurnode->g_help)
        {
        oldhlp = hlptxt;
        hlptxt = table->tcurnode->g_help;
        }
    retval = getfld(table);
    table->tstartnode = (GETITEM *)0;
    if(table->tcurnode->g_help)
        hlptxt=oldhlp;
    if(isskip)
        table->tcurnode->gcontrol |= FLDSKIP;
    if((table->tcurnode->gcontrol & FLDSKIP) &&
       (table->tcurnode->gcontrol & FLDHIDDEN) )
        vcfldblk(table->tcurnode);
    vcflush();
    return(retval);
    }
