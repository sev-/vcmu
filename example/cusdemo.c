/**
*
*   Vitamin C Multi-User version 1.%R%
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .%L% on %G% at %U%
*
*   Name            cusdemo.c --  Custom start example
*
*   Description     This function show how to use custom start to 
*                   select the routines used by Terminal Control.
*                   This allows the programmer to customize the startup
*                   procedure and still remain compatiable with future
*                   releases of Terminal Control
*
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT main()
    {
    TEXT name[15];
    TEXT address[20];
    if(yoursetup())
        terror("Error During Startup");
    empty(name,15);
    empty(address,20);
    wopen(3,20,11,60,vcterm.tmname);
    atsayget(2,5,"Name: ",name,NULL);
    atsayget(4,5,"Address: ",address,NULL);
    readgets();
    vcend(CLOSE);
    }
        
    
COUNT yoursetup()
    {
    COUNT oldpre();
    COUNT lightlr();
    COUNT ltorinp();
    COUNT initlr();
    COUNT vcputpad();
    VOID yourkeys();
    TEXT *vcgoto();
                                    /* Must read the terminal info. */
                                    /* the following should call    */
                                    /* vctinit() - read termcap.vc  */
                                    /* vcctinit() - read termcap.vcc*/
                                    /* ttinit() - read termcap      */
                                    /* titinit() - terminfo(n/a)    */
    if(vcctinit((TEXT *)"vctest") == -1)
        terror("Error initalizing Terminal");
#ifdef TERMINAL
                                    /* If you use vctinit() must    */
                                    /* pre-compile the cursor       */
                                    /* addressing and color entries */
/*
    stgo((struct PRECOMP *)&(vcterm.cursor.before),vcterm.cm);
    stgo((struct PRECOMP *)&(vcterm.color.before),vcterm.ct);
*/
                                    /* Terminal translate Functions */
    padfunc = vcputpad;             /* Pad function:                */
                                    /* vcputpad() - use VC's        */
                                    /* tputpad() - Unix (-ltermcap) */
                                    /* -----------------------------*/
    gotofunc = vcgoto;              /* Terminal Addressing function */
                                    /* vcgoto() - use VC's          */
                                    /* tgoto() - Unix (-ltermcap)   */
                                    /* -----------------------------*/
    ttranslate = 0;                 /* 0 = pre compiled cursor      */
                                    /*     addressing (vcgoto())    */
                                    /* 1 = cursor addressing not pre*/
                                    /*     compiled (tgoto())       */ 
#endif
    vcustom(CLRSCRN);               /* Call vcustom to setup var.   */
    syskeytrap = NULLFUNC;          /* System Keyboard Trap function*/ 
    yourkeys();                     /* Setup Keys for Input routines*/
    datapre[0] = oldpre;            /* Data Type 0 pre function     */ 
    datapost[0] = NULLFUNC;         /* Date Type 0 post function    */
    datalight[0] = (PFI)lightlr;    /* Input type 0 display function*/
    datafunc[0] = ltorinp;          /* Input type 0 input routine   */
    datainit[0] = (PFI)initlr;      /* Input type 0 init. function  */
    dplist = NULLFUNC;              /* Default Selection set func.  */
    wdoctrl->wcookfunc = NULLFUNC;  /* Default Cook mode function   */
    return(0);
    }


VOID yourkeys()
    {
    vckeyset();
    }


