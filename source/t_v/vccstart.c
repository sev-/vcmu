/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 9/2/90 at 14:29:14
*
*   Name            vccstart.c  --  Start Vitamin C
*
*   Description     This function sets up the correct screen address
*                   and any other variables necessary for the correct
*                   operation of Vitamin C. Uses the compiled
*                   termcap file.
*
*   Return Value    Returns -1 if error.
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT vccstart(no)
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
    TEXT *vcgoto();
    VOID vcputpad();
    COUNT wexpand();
    WPTR wprep();
    VOID dist_str();
    VOID xerase();
    VOID at();
    COUNT colormon();
    VOID nocolor();
    VOID wrd_scrn();
    COUNT vcctinit();
    VOID vckeyset();
    VOID lightlr();
    VOID lightrl();
    COUNT rtolinp();
    COUNT ltorinp();
    VOID initlr();
    VOID initrl();
    VOID statsay();
    COUNT vctrap();
#ifdef IBM
    COUNT method;
#endif
#ifdef OS2
    COUNT method;
#endif
#ifdef VMS
    vcldgl();
    vcldgt();
    vcldvc();
    vcldmn();
#endif
    if(vcctinit(NULLTEXT) == -1)
        return(-1);
#ifdef TERMINAL
    padfunc = (PFI)vcputpad;
    gotofunc = vcgoto;
    ttranslate = 0;
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
    if((wprep()) == (WPTR)0)
        return(-1);
    wdoctrl->wopnfunc = (PFI)wpickopn;
    wdoctrl->wclfunc = (PFI)wpickcl;
    wdoctrl->wcookfunc = wexpand;
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
#ifdef WINDOW
    if(no)
        wrd_scrn();
    else
#endif
        xerase(normattr);
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcstart:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(0);
    }


