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
*   Name            vccolor
*                                   
*   Description     Displays color of the default windows
*
*                                   
**/                                 

#include <vcstdio.h>

struct WDO_LOC
   {
   COUNT ur,uc,lr,lc;
   TEXT *tit;
   };

struct WDO_LOC wdo_loc[] = 
   {
   0,0,7,19,(TEXT *)"Window 0",
   0,20,7,39,(TEXT *)"Window 1",
   0,40,7,59,(TEXT *)"Window 2",
   0,60,7,79,(TEXT *)"Window 3",
   8,0,15,19,(TEXT *)"Window 4",
   8,20,15,39,(TEXT *)"Window 5",
   8,40,15,59,(TEXT *)"Window 6",
   8,60,15,79,(TEXT *)"Window 7",
   16,0,23,19,(TEXT *)"Window 8",
   16,20,23,39,(TEXT *)"Window 9",
   0,0,0,0,NULL
   };

main()
    {
    WPTR wptr,wopen();                      /* Window pointer variable  */
    struct WDO_LOC *wp;                     /* Struct of window info    */
    vcstart(CLRSCRN);                       /* Start Vitamin C          */
#ifdef TERMINAL                             /* If Terminal Driver       */
    vcpee();                                /* Start Screen buffer      */
#endif                                      /*                          */
    wp = &wdo_loc[0];                       /* Point to first window    */
    while(wp->tit != NULL)                  /* Until out of window      */
        {
        wptr = wopen(wp->ur,wp->uc,wp->lr,wp->lc,wp->tit); /* Open wdo  */
        xatsay(1,1,"Name:",wptr->say_at);       
        xatsay(2,1,"Address:",wptr->say_at);
        xatsay(3,1,"City:",wptr->say_at);
        xatsay(1,7,"xxxxxxxxxx",wptr->nget_at);
        xatsay(2,10,"xxxxxxx",wptr->get_at);
        xatsay(3,7,"xxxxxxxxxx",wptr->nget_at);
        wp++;
        }
    wopen(16,40,23,79,"Instructions");      /* Open Instruction Window  */
    atsay(2,14,"Hit Any Key");              /* Display Instructions     */
#ifdef TERMINAL                             /* If Terminal Driver       */
    vcflush();                              /* Flush screen buffer      */
#endif                                      /*                          */
    getone();                               /* Wait for character       */
    vcend(CLOSE);                           /* Close and Exit           */
    }

