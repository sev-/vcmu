/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 9/2/90 at 14:29:35
*
*   Name            vcsmall.c  --  Small start Vitamin C
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

COUNT vcsmall(no)
PFAST COUNT no;     /* True means save current screen               */
    {
    COUNT systrap(),dfvclist();
    VOID wwrtdw(),wwrtup();
    COUNT strpre(),strpost();
    TEXT *vcgoto();
    VOID vcputpad();
    WPTR wprep();
    COUNT vctinit();
    VOID dist_str();
    VOID at();
    COUNT colormon();
    VOID nocolor();
    VOID xerase();
    VOID dsorttbl();
    COUNT stgo();
    VOID vckeyset();
    VOID lightlr();
    VOID lightrl();
    COUNT rtolinp();
    COUNT ltorinp();
    VOID initlr();
    VOID initrl();
    VOID statsay();
#ifdef VMS
    vcldgl();
    vcldgt();
    vcldvc();
    vcldmn();
#endif
#ifdef IBM
    COUNT method;
#ifdef TERMINAL
    if(vctinit(NULLTEXT) == -1)
        return(-1);
#else
    if(vcnoterm(NULLTEXT) == -1)
        return(-1);
#endif
#endif
#ifdef OS2
    COUNT method;
#ifdef TERMINAL
    if(vctinit(NULLTEXT) == -1)
        return(-1);
#else
    if(vcnoterm(NULLTEXT) == -1)
        return(-1);
#endif
#endif
#ifdef TERMONLY
    if(vctinit(NULLTEXT) == -1)
        return(-1);
#endif
#ifdef TERMINAL
    stgo((struct PRECOMP *)&(vcterm.cursor.before),vcterm.cm);
    stgo((struct PRECOMP *)&(vcterm.color.before),vcterm.ct);
    padfunc = (PFI)vcputpad;
    gotofunc = vcgoto;
    ttranslate = 0;
    dsorttbl();
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
    if((wprep()) == (WPTR)0)
        return(-1);
    wdoctrl->wopnfunc = (PFI)wwrtdw;
    wdoctrl->wclfunc = (PFI)wwrtdw;
#endif
#ifdef TERMONLY
    vctio = 5;
    set_raw();
#endif
#ifdef IBM
    switch(colormon())
        {
        case 0 :              /*       MonoChrome Monitor       */
            method = 1;
            vcvram=0xb000;
            vcsprt=0x3ba;
            nocolor();
            break;
        case 1 :    /*          Color Card                          */
            method = 2;
            vcvram=0xb800;
            vcsprt=0x3da;
            break;
        case -1 :   /*          EGA MonoChrome Monitor              */
            method = 1;
            nocolor();
            break;
        case -2 :   /*          EGA Color Monitor                   */
            method = 1;
            break;
        }
    if(vctio == -1)
        vctio = method;
#endif
#ifdef OS2
    method = colormon();
    if(!method)
        nocolor();
    if(vctio == -1)
        vctio = method;
#endif
#ifdef TERMINAL
    if(vctio == 5)
        dist_str(vcterm.is,0);
    if(vctio == 5)
        {
        at(0,0);
        if(!colormon())
            nocolor();
        }
#endif
    if(!no)
        xerase(normattr);
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcstart:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(0);
    }


