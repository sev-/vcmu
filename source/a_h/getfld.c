/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:14
*
*   Name            getfld.c  --  Get an entry into a field
*
*   Description     This function prints the field in a non active
*                   attribute then call the correct input routine
*                   then calls the validation function if necessary
*                   returns the key that caused it to exit.
*
*   Return Value    Returns the character pressed
*
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS

#include <vcstdio.h>

COUNT getfld(table)
GETTABLE *table;    /* Get table to get input for                   */
    {
    COUNT editfld = TRUE;
    GETITEM *node;
    COUNT valret = 0;
    COUNT inptype;
    COUNT haveauth();
    COUNT keyrdy();
    COUNT getone();
    COUNT ungetone();
    COUNT vcpee();
    WPTR wselect();
    VOID vcflush();
    COUNT callval();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "getfld:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    table->tkeypress = 0;
    node = table->tcurnode;
    if( node->gmagic != GETNODEMAGIC )
        {
        vcerror = BADGTBL;
        return(0);
        }
    if(node->gprefunc)
        (*node->gprefunc)(node->gtmpfld,table);

    inptype = (node->gfldtyp >> 7) & 15;
    
    if((!haveauth(node->gfldtyp & 127,FLDEDIT)) ||
        (node->gcontrol & FLDSKIP) )
        {
        table->tkeypress = 0;
        return(0);
        }
    if(table->tkeypress)
        {
        if( table->tkeypress == spkey.fld_left ||
            table->tkeypress == spkey.fld_right ||
            table->tkeypress == spkey.fld_up ||
            table->tkeypress == spkey.fld_down ||
            table->tkeypress == spkey.fld_pgup ||
            table->tkeypress == spkey.fld_pgdn ||
            table->tkeypress == spkey.fld_end ||
            table->tkeypress == spkey.fld_home ||
            table->tkeypress == spkey.fld_ret ||
            table->tkeypress == spkey.abort ||
            table->tkeypress == spkey.done ||
            table->tkeypress >= 9000 )
            {
            if((callval(table) == GOOD) &&
               !(table->tcurnode->gcontrol & FLDSET) )
                {
                if(node->gpostfunc)
                    (*node->gpostfunc)(node->gtmpfld,table);
                return(table->tkeypress);
                }
            }
        }
#ifdef TERMINAL
    if(vctio == 5)
        vcpee();
#endif
#ifdef WINDOW
    if((node->gwptr != (WPTR)0) && (node->gwptr != wdoctrl->wcurrent))
        wselect(node->gwptr);
#endif
   if(node->gattrag == vc.dflt)
#ifdef WINDOW
        if(wdoctrl->wno_opn && !override)
            node->gcurattr = wdoctrl->wcurrent->get_at;
        else
#endif
            node->gcurattr = attrag;
    else
        node->gcurattr = node->gattrag;

    /* PRINT FIELD IN ACTIVE ATTRIBUTE */

    if(datalight[inptype] != NULLFUNC)
        (*datalight[inptype])(node);

#ifdef TERMINAL
    if(vctio == 5)
        vcflush();
#endif
    if(table->tctrl & RESETINS)
        table->tinsmode = FALSE;
    while(TRUE)
        {
        editfld = TRUE;
        if( ((selmode && !(node->gcontrol & FLDNOSET)) ||
            (node->gcontrol & FLDSET) ) && 
           node->gselset && (node->gplist != NULLFUNC))
            editfld = (*node->gplist)(table);
        if(valret)
            node->gcndx = valret - 1;
        if(editfld && (datafunc[inptype] != NULLFUNC) )
            if((*datafunc[inptype])(table))
                continue;
        if(((valret = callval(table)) == GOOD) ||
           (table->tkeypress == spkey.abort) ||
           ((valret == GOOD) && (table->tkeypress == spkey.done) ) )
            break;
        }
#ifdef TERMINAL
    if(vctio == 5)
        vcpee();
#endif
   if(node->gattrnag == vc.dflt)
#ifdef WINDOW
        if(wdoctrl->wno_opn && !override)
            node->gcurattr = wdoctrl->wcurrent->nget_at;
        else
#endif
            node->gcurattr = attrnag;
    else
        node->gcurattr = node->gattrnag;

    node->gstart = 0;

    if(datalight[inptype] != NULLFUNC)
        (*datalight[inptype])(node);

    if(node->gpostfunc)
        (*node->gpostfunc)(node->gtmpfld,table);

    if(!(table->tctrl & STARTLEFTOFF) &&
       (table->tstartnode != node) )
        node->gcndx = -1;

    return(table->tkeypress);
    }

COUNT callval(gt)
GETTABLE *gt;
    {
    COUNT retval = GOOD;
    if((gt->tkeypress == spkey.abort) &&
       (gt->tctrl & NOVALESC) )
        retval = GOOD;
    else
        {
        if(gt->tcurnode->g_funptr)
            retval = (*gt->tcurnode->g_funptr)(gt->tcurnode->gtmpfld,gt);
        }
    return(retval);
    }

