/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 9/2/90 at 14:29:47
*
*   Name            vccustom.c  --  Custom start Vitamin C
*
*   Description     This function sets up the correct screen address
*                   and any other variables necessary for the correct
*                   operation of Vitamin C.  It sets up the bare
*                   min requirements for Vitamin C.
*
*   Return Value    Returns -1 if error.
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT vcustom(no)
PFAST COUNT no;             /* TRUE means save current screen       */
    {
    VOID wwrtdw(),wwrtup();
    WPTR wprep();
    COUNT vcctinit();
    VOID dist_str();
    VOID at();
    COUNT colormon();
    VOID xerase();
    VOID nocolor();
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
#ifdef WINDOW
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


