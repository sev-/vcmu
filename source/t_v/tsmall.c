/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 9/2/90 at 14:29:56
*
*   Name            tsmall.c  --  Small start Vitamin C
*
*   Description     This function sets up the correct screen address
*                   and any other variables necessary for the correct
*                   operation of Vitamin C.  It sets up the minimum
*                   requirement for Vitamin C.
*
*   Return Value    Returns -1 if error.
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

#ifdef UNIX

COUNT tsmall(no)
PFAST COUNT no;     /* True means save current screen               */
    {
    COUNT systrap(),dfvclist();
    VOID wwrtdw(),wwrtup();
    COUNT strpre(),strpost();
    TEXT *tgoto();
    COUNT tputs();
    TEXT *wprep();
    COUNT ttinit();
    VOID vckeyset();
    VOID at();
    VOID nocolor();
    COUNT colormon();
    VOID xerase();
    VOID dist_str();
    VOID lightlr();
    VOID lightrl();
    COUNT rtolinp();
    COUNT ltorinp();
    VOID initlr();
    VOID initrl();
    VOID statsay();
    if(ttinit(NULLTEXT) == -1)
        return(-1);
#ifdef TERMINAL
    padfunc = tputs;
    gotofunc = tgoto;
    ttranslate = 1;
#endif
    vckeyset();
    syskeytrap = NULLFUNC;
    vcstatus = (PFI)statsay;
    datapre[0] = strpre;
    datapost[0] = strpost;
    datalight[0] = (PFI)lightlr;
    datafunc[0] = ltorinp;
    datainit[0] = (PFI)initlr;
    datalight[1] = (PFI)lightrl;
    datafunc[1] = rtolinp;
    datainit[1] = (PFI)initrl;
#ifdef WINDOW
    dplist = NULLFUNC;
    if((wprep()) == NULLTEXT)
        return(-1);
    wdoctrl->wopnfunc = (PFI)wwrtdw;
    wdoctrl->wclfunc = (PFI)wwrtdw;
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
    if(!no)
        xerase(normattr);
#ifdef VCDEBUG
    vcdebug = (TEXT *) "tsmall:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(0);
    }

#endif
