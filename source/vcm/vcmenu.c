/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:31
*
*   Name            vcmenu -- menu driver                 
*                                   
*   Description     displays and process menu structures                 
*
*   Return Value    Returns -1 if error
*                                   
**/                                 

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT vcmenu(m)
VCMENU *m;          /* Pointer to menu to execute                   */
    {
    MENUITEM *olditmptr;
    TEXT *oldhlp;
    COUNT boxwid=0;
    COUNT ofst;
    COUNT wdoctrl;
    COUNT hrow=0,hcol=0,maxhcol=0;
    COUNT movenext,moveprev;
    COUNT bdofst;
    COUNT ntmp,savchr;
    COUNT strlen();
    VOID xerase();
    VOID box();
    COUNT wclose();
    VOID xatsay();
    COUNT dracuritm();
    COUNT findavl();
    COUNT wshow();
    VOID vcmselbar();
    VOID statsay();
    COUNT getone();
    COUNT prevmitm();
    COUNT nextmitm();
    COUNT whide();
    VOID won();
    VOID woff();
    COUNT mnukey();
    WPTR wxopen();
    WPTR wselect();
    vcerror = 0;
    if((m == (VCMENU *)0) ||
       (m->mmagic != MENUMAGIC) )
        {
        vcerror = BADMENU;
        return(MENUERROR);
        }

    m->mresult=0;         /* this is the code returned by this func */
    m->mfuncret=0;        /* code returned by the func this menu calls */
    m->mkeyhit=0;

    if( vcmhk1 )
        if( (*vcmhk1)(m) )
            return(m->mresult);

    bdofst = (m->mstyle & BORDERLESS) ? 0 : 2;
    wdoctrl = NOADJ;
    if(m->mstyle & SHADOW)
        wdoctrl |= SHADOW;
    if(m->mstyle & CURSOR)
        wdoctrl |= CURSOR;
    /* SET-UP FOR VERTICAL MENUS */
    if( m->mstyle & VERTICAL )
        {
        moveprev=spkey.list_up;                     /* selection keys */
        movenext=spkey.list_dn;
        if( m->mchecks )                      /* need room to   */
            ofst=1;                           /* display check  */
        else                                 /* marks ?        */
            ofst=0;
        if( m->mknamwid > 0 )                 /* Compute min    */
            boxwid=m->mknamwid+1;              /* window width   */
        boxwid+=m->mitemwid+ofst+bdofst-1;
        if( m->mwidth == AUTO || m->mwidth < boxwid )
            {
            if( m->menuname && !(m->mstyle & BORDERLESS) &&
                    (m->mstyle & TITLELEFT || m->mstyle & TITLECENTER ||
                    m->mstyle & TITLERIGHT) )
                m->mmnuwid = max(boxwid,strlen(m->menuname));
            else
                m->mmnuwid = boxwid;
            }
        else
            m->mmnuwid = m->mwidth-1;
        if( m->mcol+m->mmnuwid >= vcterm.cols )  /* Be sure coords will fit */
            m->mcol -= (1+m->mcol+m->mmnuwid) - vcterm.cols;
        if( m->mrow+m->mitemcnt-1+bdofst >= vcterm.rows)  /* If not enough rows */
            {
            vcerror = BADCORD;                           /* error out & return */
            return(0);
            }
        m->mwptr = wxopen(m->mrow,m->mcol,
                 m->mrow+m->mitemcnt-1+bdofst,m->mcol+m->mmnuwid,
                 m->menuname,wdoctrl,0,0);
        if( m->mwptr == (WPTR) 0 )
            return(0);
        xerase(m->mnormattr);
        if( bdofst )
            box(0,0,m->mwptr->depth-1,m->mwptr->width-1,1,m->mbordattr);
        }
    if( m->mstyle & HORIZONTAL )
        {
        moveprev=spkey.list_left;
        movenext=spkey.list_right;
        m->mcuritmnbr=1;
        m->mcuritmptr = m->mitemhead;
        if( bdofst )
            hrow=hcol=1;
        /* loop through all items & set-up coordinates for item display */
        if( m->mwidth == AUTO || m->mwidth-1 >= vcterm.cols )
            boxwid=vcterm.cols-1;
        else
            boxwid=m->mwidth-1;
        while( m->mcuritmptr )
            {
            if( m->mcuritmptr->emagic != MITEMMAGIC )
                {
                vcerror = BADMITEM;
                return(MENUERROR);
                }
            if( m->mcuritmptr->eitemname && *m->mcuritmptr->eitemname )
                ntmp=strlen( m->mcuritmptr->eitemname );
            else
                ntmp=0;
            if( hcol+ntmp > boxwid-bdofst )
                {
                /* Too wide for line, add another */
                hcol = (m->mstyle & BORDERLESS) ? 0 : 1;
                hrow++;
                }
            m->mcuritmptr->ehcoords= ((hrow << 8) + hcol);
            hcol += strlen( m->mcuritmptr->eitemname );
            maxhcol = max(maxhcol,hcol);
            hcol += 2;
            m->mcuritmptr = m->mcuritmptr->enext;
            m->mcuritmnbr++;
            }
        if( m->mwidth != AUTO )
            maxhcol = m->mwidth-1;
        else
            maxhcol += bdofst;
        m->mwptr =wxopen(m->mrow,
                       m->mcol,
                       m->mrow+hrow+((bdofst>0)?1:0),
                       m->mcol+maxhcol,
                       m->menuname,wdoctrl,0,0);
        if( m->mwptr == (WPTR) 0 )
            return(0);
        m->mmnuwid=maxhcol;
        xerase(m->mnormattr);
        if( bdofst )
            box(0,0,m->mwptr->depth-1,m->mwptr->width-1,1,m->mbordattr);
        }

    m->mcuritmnbr=1;
    m->mcuritmptr = m->mitemhead;
    while( m->mcuritmptr != (MENUITEM *)0 )
        {
        if( dracuritm(m) )
            {
            wclose(m->mwptr);
            return(MENUERROR);     /*  */
            }
        m->mcuritmptr = m->mcuritmptr->enext;
        m->mcuritmnbr++;
        }

    if( m->menuname && !(m->mstyle & BORDERLESS) &&
        (m->mstyle & TITLELEFT || m->mstyle & TITLECENTER || 
        m->mstyle & TITLERIGHT) )
        {
        ntmp=m->mwptr->width-2;
        if( strlen(m->menuname) >= ntmp )
            {
            savchr=m->menuname[ntmp];
            m->menuname[ntmp]=0;
            xatsay(0,1,m->menuname,m->mbordattr);
            m->menuname[ntmp]=savchr;
            }
        else
            {
            if( m->mstyle & TITLELEFT )
                ntmp=1;
            if( m->mstyle & TITLERIGHT || m->mstyle & TITLECENTER )
                ntmp=m->mwptr->width-strlen(m->menuname)-1;
            if( m->mstyle & TITLECENTER )
                {
                ntmp--;
                ntmp = (ntmp >> 1) + 1;
                }
            xatsay(0,ntmp,m->menuname,m->mbordattr);
            }
        }
    m->mcuritmnbr=1;
    m->mcuritmptr=m->mitemhead;
    if( findavl(m) )
        {
        wclose(m->mwptr);
        return(m->mresult=ESCAPE);
        }
    wshow(m->mwptr);
    vcmselbar(m,ON);
    oldhlp=hlptxt;
    while( m->mresult==0 )
        {                                     /* set-up help. */
        if( m->mcuritmptr->ehelpkey )
            hlptxt=m->mcuritmptr->ehelpkey;      /* item level   */
        else if( m->mhelpkey )
            hlptxt=m->mhelpkey;                 /* menu level   */
        else                                                
            hlptxt=oldhlp;                     /* default      */
      
        statsay(m->mcuritmptr->estat,-1);

        if( vcmhk2 )
            if( (*vcmhk2)(m) )
                continue;

        m->mkeyhit=getone();

        if( vcmhk3 )
            if( (*vcmhk3)(m) )
                continue;
      
        if( m->mkeyhit == spkey.abort )
            {
            vcmselbar(m,OFF);
            m->mresult = ESCAPE;     /* return this to caller */
            continue;
            }
        if( m->mkeyhit == moveprev )
            {
            vcmselbar(m,OFF);
            prevmitm(m);
            vcmselbar(m,ON);
            continue;
            }
        if( m->mkeyhit == movenext )
            {
            vcmselbar(m,OFF);
            nextmitm(m);
            vcmselbar(m,ON);
            continue;
            }
        if( m->mkeyhit == vckey.ret )
            {
            vcmselbar(m,OFF);
            if( vcmhk4 )
                if( (*vcmhk4)(m) )
                    continue;
            if( m->mcuritmptr->efunc )
                {
                if( m->mcuritmptr->ectrl & HIDE )
                    whide(m->mwptr);
                if( m->mcuritmptr->ectrl & MENU )
                    {
                    m->mcuritmptr->eparm.pmnuptr->mcalledby = m;
                    m->mfuncret=(*m->mcuritmptr->efunc)(m);
                    m->mcuritmptr->eparm.pmnuptr->mcalledby = (VCMENU *)0;
                    }
                else
                    {
                    if(m->mcuritmptr->ectrl & SENDTXT)
                        {
                        if( m->mcuritmptr->ectrl & STRPARM)
                            m->mfuncret=(*m->mcuritmptr->efunc)
                                       (m->mcuritmptr->eparm.pchrptr);
                        else
                            m->mfuncret=(*m->mcuritmptr->efunc)
                                       (m->mcuritmptr->eparm.pnumptr);
                        }
                    else
                        m->mfuncret=(*m->mcuritmptr->efunc)(m);
                    }
                }
            else
                {
                if( m->mcuritmptr->ectrl & MENU )
                    {
                    if( m->mcuritmptr->ectrl & HIDE )
                        whide(m->mwptr);
                    m->mcuritmptr->eparm.pmnuptr->mcalledby=m;
                    m->mfuncret=vcmenu(m->mcuritmptr->eparm.pmnuptr);
                    m->mcuritmptr->eparm.pmnuptr->mcalledby = (VCMENU *)0;
                    }
                if( m->mcuritmptr->ectrl & MSCREEN)
                    {
                    if( m->mcuritmptr->ectrl & HIDE)
                        whide(m->mwptr);
                    if(scrnfunc != NULLFUNC)
                        m->mfuncret = (*scrnfunc)(m);
                    }
                }
            if( vcmhk5 )
                if( (*vcmhk5)(m) )
                    continue;
/*                                                         dag 5.18.90 
            if( (m->mcuritmptr->ectrl & ESCAPE) ||
               ((m->mfuncret == ESCAPE) && !(m->mcuritmptr->ectrl & RETURN)))
                m->mresult = ESCAPE;
            else 
*/
            if( (m->mfuncret == RETURN)  ||
               ((m->mcuritmptr->ectrl & RETURN) && (m->mfuncret != ESCAPE)))
                m->mresult = -1;
            else
                {
                wselect(m->mwptr);
                if(m->mstyle & REFRESH ||
                   m->mfuncret & REFRESH ||
                   m->mcuritmptr->ectrl & REFRESH)
                    {
                    woff();
                    olditmptr=m->mcuritmptr;
                    m->mcuritmnbr=1;
                    m->mcuritmptr = m->mitemhead;
                    while( m->mcuritmptr != (MENUITEM *)0 )
                        {
                        dracuritm(m);
                        m->mcuritmptr = m->mcuritmptr->enext;
                        m->mcuritmnbr++;
                        }
                    m->mcuritmptr=olditmptr;
                    m->mcuritmnbr=m->mcuritmptr->eitemnbr;
                    won();
                    }
                else
                    dracuritm(m);
                if(m->mcuritmptr->ectrl & HIDE)
                    wshow(m->mwptr);                      /* show the window        */
                vcmselbar(m,ON);
                }
            continue;
            }
        vcmselbar(m,OFF);
        mnukey(m);
        vcmselbar(m,ON);
        }
    wclose(m->mwptr);
    hlptxt=oldhlp;
    return(m->mresult);
    }


