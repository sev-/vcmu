/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:25
*
*   Name            xreadget.c  --  Read from table
*
*   Description     This is the function that indexes through
*                   a get table. It is responsible for displaying
*                   the status line, setting up the help string
*                   and moving forward and backwards in the get
*                   table sending the next field to getfield.
*
*   Return Value    Returns the key that caused exit
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT xreadgets(gptr)
GETTABLE *gptr;     /* Pointer to get table to read                 */
    {
    TEXT *oldhlp;
    COUNT direction = 0;
    SAYITEM *si;
    GETITEM *gi;
    WPTR wptr;
    COUNT savctrl;
    WPTR wselect();
    VOID sayget();
    COUNT getfld();
    VOID vcflush();
    COUNT vcpee();
    VOID vcsaveds();
    VOID bell();
    VOID getsay();
    GETITEM *valtable();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xreadgets:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( !gptr )
        {
        vcerror=XRDBADGTBL;
        return(-1);
        }
    else
        if( gptr->tmagic != GETTBLMAGIC )
            {
            vcerror=XRDBADGTBL;
            return(-1);
            }
    if( gptr->thead == (GETITEM *)0 )
       {
       vcerror=XRDNOGETS;
       return(-1);
       }
#ifdef TERMINAL
    if(vctio == 5)
        vcpee();
#endif
    if( (gptr->tgetseq == NULLFUNC) || (*gptr->tgetseq)(gptr) )
        return(-1);
    if( gptr->tctrl & QDISPLAY)
        {
#ifdef WINDOW
        if(wdoctrl->wcurrent != (WPTR)0)
            {
            savctrl = wdoctrl->wcurrent->wctrl;
            wdoctrl->wcurrent->wctrl |= NOAUTO;
            }
#endif
        si = gptr->tsayhead;
        while(si != (SAYITEM *)0)
            {
            sayget(si);
            si = si->snnext;
            }
        gi = gptr->thead;
        while(gi != (GETITEM *)0)
            {
            getsay(gi);
            gi = gi->gnext;
            }
#ifdef WINDOW
        wdoctrl->wcurrent->wctrl = savctrl;
#endif
        }
    if( gptr->tstartnode != (GETITEM *)0)
        {
        gptr->tcurnode = gptr->tstartnode;
        gptr->tstartnode = (GETITEM *)0;
        }
    if(gethk2)
        (*gethk2)(gptr);
    while( gptr->tcurnode )
        {
        if( gptr->tcurnode->gmagic != GETNODEMAGIC )
            {
            vcerror = XRDBADGET;
            return(-1);
            }
        if(vcstatus != NULLFUNC)
            (*vcstatus)(gptr->tcurnode->g_msg,-1);
        if(gptr->tcurnode->g_help)
            {
            oldhlp=hlptxt;
            hlptxt=gptr->tcurnode->g_help;
            }

        getfld(gptr);

        if(gethk3)
            if((*gethk3)(gptr))
                continue;
        if(gptr->tcurnode->g_help)
            hlptxt=oldhlp;

        if(gptr->tstartnode != (GETITEM *)0)
            {
            gptr->tcurnode = gptr->tstartnode;
            gptr->tstartnode = (GETITEM *)0;
            continue;
            }

        if( gptr->tkeypress == 0 )
            {
            switch(direction)
                {
                case 0:
                    gptr->tkeypress=spkey.fld_ret;
                    break;
                case 1:
                    gptr->tkeypress=spkey.fld_right;
                    break;
                case 2:
                    gptr->tkeypress=spkey.fld_down;
                    break;
                case -1:
                    gptr->tkeypress=spkey.fld_left;
                    break;
                case -2:
                    gptr->tkeypress=spkey.fld_up;
                    break;
                }
            }
        if( gptr->tkeypress == spkey.abort || gptr->tkeypress == spkey.done 
            || gptr->tkeypress >= 9000)
            {
            if((gptr->tctrl & VALALLTBL) && (gptr->tkeypress != spkey.abort))
                {
                gi = valtable(gptr);
                if(gi != (GETITEM *)0)
                    {
                    gptr->tcurnode = gi;
                    continue;
                    }
                }
            break;
            }

        if( gptr->tkeypress == spkey.fld_left )
            {
            if( gptr->tcurnode->gleft )
                gptr->tcurnode = gptr->tcurnode->gleft;
            else
                {
                if(gptr->tctrl & MKCIRCLE)
                    gptr->tcurnode = gptr->ttail;
                else
                    {
                    if(gptr->tctrl & MKEXIT)
                        break;
                    else
                        {
                        bell();
                        if(gptr->tcurnode->gcontrol & FLDSKIP)
                            {
                            direction = 1;
                            continue;
                            }
                        }
                    }
                }
            direction = -1;
            continue;
            }

        if( gptr->tkeypress == spkey.fld_ret )
            {
            if(gptr->tctrl & NORETEXIT)
                gptr->tkeypress = spkey.fld_right;
            else
                {
                gptr->tcurnode = gptr->tcurnode->gright;
                if((gptr->tcurnode == (GETITEM *)0) &&
                   (gptr->tctrl & VALALLTBL) && 
                   (gptr->tkeypress != spkey.abort))
                    {
                    gi = valtable(gptr);
                    if(gi != (GETITEM *)0)
                        gptr->tcurnode = gi;
                    }
                direction = 0;
                continue;
                }
            }

        if( gptr->tkeypress == spkey.fld_right )
            {
            if( gptr->tcurnode->gright )
                gptr->tcurnode = gptr->tcurnode->gright;
            else
                {
                if(gptr->tctrl & MKCIRCLE)
                    gptr->tcurnode = gptr->thead;
                else
                    {
                    if(gptr->tctrl & MKEXIT)
                        break;
                    else
                        {
                        bell();
                        if(gptr->tcurnode->gcontrol & FLDSKIP)
                            {
                            direction = -1;
                            continue;
                            }
                        }
                    }
                }
            direction = 1;
            continue;
            }

        if( ( (gptr->tkeypress == spkey.fld_down) ||
              (gptr->tkeypress == spkey.fld_up)   ) &&
              (gptr->tctrl & TBLRETUP)  )
            {
            if(gptr->tctrl & VALALLTBL)
                {
                gi = valtable(gptr);
                if(gi != (GETITEM *)0)
                    {
                    gptr->tcurnode = gi;
                    continue;
                    }
                }
            break;
            }

        if( gptr->tkeypress == spkey.fld_up )
            {
            if( gptr->tcurnode->gup )
                {
                gptr->tcurnode = gptr->tcurnode->gup;
                direction = -2;
                }
            else
                {
                if(gptr->tctrl & MKCIRCLE)
                    gptr->tcurnode = gptr->ttail;
                else
                    {
                    if(gptr->tctrl & MKEXIT)
                        break;
                    else
                        {
                        bell();
                        if(gptr->tcurnode->gcontrol & FLDSKIP)
                            {
                            direction = 2;
                            continue;
                            }
                        }
                        bell();
                    }
                }
            continue;
            }

        if( gptr->tkeypress == spkey.fld_down )
            {
            if( gptr->tcurnode->gdown )
                {
                gptr->tcurnode = gptr->tcurnode->gdown;
                direction = 2;
                }
            else
                {
                if(gptr->tctrl & MKCIRCLE)
                    gptr->tcurnode = gptr->thead;
                else
                    {
                    if(gptr->tctrl & MKEXIT)
                        break;
                    else
                        {
                        bell();
                        if(gptr->tcurnode->gcontrol & FLDSKIP)
                            {
                            direction = -2;
                            continue;
                            }
                        }
                    }
                }
            continue;
            }

        if( gptr->tkeypress == spkey.fld_home )
            {
            if(gptr->tcurnode != gptr->thead)
                gptr->tcurnode = gptr->thead;
            else
                bell();
            continue;
            }

        if( gptr->tkeypress == spkey.fld_end )
            {
            if(gptr->tcurnode != gptr->ttail)
                gptr->tcurnode = gptr->ttail;
            else
                bell();
            continue;
            }
        
        if( (gptr->tctrl & TBLRETPG) && 
            ( (gptr->tkeypress == spkey.fld_pgdn) ||
              (gptr->tkeypress == spkey.fld_pgup) )  )
            {
            if(gptr->tctrl & VALALLTBL)
                {
                gi = valtable(gptr);
                if(gi != (GETITEM *) 0)
                    {
                    gptr->tcurnode = gi;
                    continue;
                    }
                }
            break;
            }
            
        if( (gptr->tkeypress == spkey.fld_pgup) &&
            (gptr->tcurnode != gptr->thead) )
            {
            gi = gptr->tcurnode;
            wptr = gptr->tcurnode->gwptr;
            while(gi != gptr->thead)
                {
                if(gi->gwptr != wptr)
                    break;
                gi = gi->gleft;
                }
            gptr->tcurnode = gi;
            continue;
            }

        if( (gptr->tkeypress == spkey.fld_pgdn) &&
            (gptr->tcurnode != gptr->ttail) )
            {
            gi = gptr->tcurnode;
            wptr = gptr->tcurnode->gwptr;
            while(gi != gptr->ttail)
                {
                if(gi->gwptr != wptr)
                    break;
                gi = gi->gright;
                }
            gptr->tcurnode = gi;
            continue;
            }

        }

    if(vcstatus != NULLFUNC)
        (*vcstatus)(NULLTEXT,-1);
#ifdef TERMINAL
    if(vctio == 5)
        vcflush();
#endif
    if( gptr->tkeypress != spkey.abort )
       {
       vcsaveds(gptr);
       }

    if(gethk4)
        (*gethk4)(gptr);

    return( gptr->tkeypress );
    }



