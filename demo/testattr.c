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
*   Name            testattr
*                                   
*   Description     Test terminal attributes
*
*   Return Value    None.
*                                   
**/                                 

#include <vcstdio.h>

main()
    {
    WPTR wptr,wxopen();                         /* Window Pointer           */
    vcstart(CLRSCRN);                           /* Start Vitamin C          */
    wptr = wxopen(0,0,vcterm.rows-1,vcterm.cols-1,/* Open a Full screen     */
                    vcterm.tmname,BORDER,0,0);    /* Window with Term. Name */
    box(2,10,20,68,0,vc.dflt);                  /* Draw Box around area     */
    box(3,39,19,39,0,vc.dflt);                  /* Draw line                */
    at(2,39);                                   /* Address the cursor       */
    vcputc(border[0].mt,wptr->say_at);          /* Put top merge character  */
    at(20,39);                                  /* Move the cursor          */
    vcputc(border[0].mb,wptr->say_at);          /* Put bottom merge char    */
    xatsay(4,16,"Invisible",0);                 /* Draw Characters          */
    xatsay(6,16,"Underline",vc.blue);           /* Blue = underline on Mono */
    xatsay(8,16,"Normal",vc.white);
    xatsay(10,16,"Lo/Underline",vc.blue+vc.bold);
    xatsay(12,16,"Lo/Normal",vc.white+vc.bold);
    xatsay(14,16,"Inverse",vc.white*vc.bg);
    xatsay(16,16,"Inverse/Underline",vc.white*vc.bg+vc.blue);
    xatsay(18,16,"Lo/Inverse",vc.bold+vc.white*vc.bg);
    xatsay(4,45,"Blink/Underline",vc.blue+vc.blink);
    xatsay(6,45,"Blink/Normal",vc.blink+vc.white);
    xatsay(8,45,"Blink/Und/Lo",vc.blink+vc.blue+vc.bold);
    xatsay(10,45,"Blink/Lolight",vc.white+vc.blink+vc.bold);
    xatsay(12,45,"Blink/Inverse",vc.white*vc.bg+vc.blink);
    xatsay(14,45,"Blink/Inv/Und",vc.white*vc.bg+vc.blue+vc.blink);
    xatsay(16,45,"Blink/Inv/Lo",vc.white*vc.bg+vc.bold+vc.blink);
    xatsay(18,45,"Blink/Inv/Und/Lo",vc.white*vc.bg+vc.blue+vc.bold+vc.blink);
#ifdef TERMINAL                                 /* If compiled with Terminal*/
    vcpee();                                    /* drivers (not direct scrn)*/
#endif                                          /* Start screen buffer      */
    wshow(wptr);                                /* Show window              */
#ifdef TERMINAL                                 /* If compiled with Terminal*/
    vcflush();                                  /* drivers (not direct scrn)*/
#endif                                          /* Empty screen buffer      */
    getone();                                   /* Wait for a character     */
    vcend(CLOSE);                               /* Close Vitamin C          */
    }

