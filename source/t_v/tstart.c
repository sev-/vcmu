/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 9/2/90 at 14:29:57
*
*   Name            tstart.c  --  Start Vitamin C
*
*   Description     This function sets up the correct screen address
*                   and any other variables necessary for the correct
*                   operation of Vitamin C.
*
*   Return Value    Returns -1 if error.
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

#ifdef UNIX

COUNT tstart(no)
PFAST COUNT no;     /* True means save current screen               */
    {
    COUNT systrap(),dfvclist();
    VOID wpickopn(),wpickcl();
    COUNT strpre(),strpost();
    COUNT numpre(),numpost();
    COUNT datepre(),datepost();
    COUNT intpre(),intpost();
    COUNT snumpre(),snumpost();
    COUNT sintpre(),sintpost();
    COUNT longpre(),longpost();
    COUNT wexpand();
    TEXT *tgoto();
    COUNT tputs();
    TEXT *wprep();
    COUNT ttinit();
    VOID vckeyset();
    VOID at();
    COUNT colormon();
    VOID nocolor();
    VOID dist_str();
    VOID wrd_scrn();
    VOID xerase();
    VOID lightlr();
    VOID lightrl();
    COUNT rtolinp();
    COUNT ltorinp();
    VOID initlr();
    VOID initrl();
    COUNT vctrap();
    VOID statsay();
    if(ttinit(NULLTEXT) == -1)
        return(-1);
#ifdef TERMINAL
    padfunc = tputs;
    gotofunc = tgoto;
    ttranslate = 1;
#endif
    vckeyset();
    syskeytrap = systrap;
    keytrap = vctrap;
    vcstatus = (PFI)statsay;
    datapre[0] = strpre;
    datapost[0] = strpost;
    datapre[1] = intpre;
    datapost[1] = intpost;
    datapre[2] = numpre;
    datapost[2] = numpost;
    datapre[3] = datepre;
    datapost[3] = datepost;
    datapre[4] = longpre;
    datapost[4] = longpost;
    datapre[5] = snumpre;
    datapost[5] = snumpost;
    datapre[6] = sintpre;
    datapost[6] = sintpost;
    datalight[0] = (PFI)lightlr;
    datafunc[0] = ltorinp;
    datainit[0] = (PFI)initlr;
    datalight[1] = (PFI)lightrl;
    datafunc[1] = rtolinp;
    datainit[1] = (PFI)initrl;
#ifdef WINDOW
    dplist = dfvclist;
    if((wprep()) == NULLTEXT)
        return(-1);
    wdoctrl->wopnfunc = (PFI) wpickopn;
    wdoctrl->wclfunc = (PFI) wpickcl;
    wdoctrl->wcookfunc = wexpand;
#endif
#ifdef TERMINAL
    dist_str(vcterm.is,0);
#endif
#ifdef TERMONLY
    vctio = 5;
    set_raw();
#endif
if(vctio == 5)
    {
    at(0,0);
    if(!colormon())
        nocolor();
    }
#ifdef WINDOW
    if(no)
        wrd_scrn();
    else
#endif
        xerase(normattr);
#ifdef VCDEBUG
    vcdebug = (TEXT *) "tstart:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(0);
    }


#endif
