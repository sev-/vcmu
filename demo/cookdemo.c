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
*   Name            cookdemo
*                                   
*   Description     Sample of wcooked mode
*
*   Return Value    None.
*                                   
**/                                 

#include <vcstdio.h>

main()
    {
    WPTR wdo1,wdo2,wxopen();                /* Window variables         */ 
    TEXT buf[132];                          /* Buffer for read          */
    FILE *filename,*fopen();                /* File variables           */
    vcstart(CLRSCRN);                       /* Start Vitamin C          */
    wdoctrl->wbgdisplay = TRUE;             /* Allow background printing*/
    wdoctrl->wretlf = 1;                    /* Expand lf to lf + ret    */
    wdo1 = wxopen(4,10,18,50,"Receiving Data In Background", /* Open    */
	      SHADOW+ACTIVE+SCROLL+BORDER+BD2+COOKED+NOAUTO,0,80);  /* Two     */
    wdo2 = wxopen(14,20,16,60,NULL,SHADOW+ACTIVE+BORDER,0,0);       /* Windows */
    atsay(0,10,"Hit Any Key to Stop");                /* Display msg    */
    if((filename = fopen("cookdemo.c","r")) == NULL ) /* Open file      */
        terror("File cookdemo.c not found");          /* Error opening  */
    while(!keyrdy())                              /* While no key       */
        {                                         /*   waiting          */
        if((fgets(buf,130,filename)) != NULL)     /* Read line          */
            wputs(wdo1,buf,wdo1->say_at);         /* Write to window    */
        else                                      /*     or             */
            fseek(filename,0L,0);                 /* start over         */
        }                                         /*                    */
    getone();                                     /* Clear input        */
    wclose(wdo1);                                 /* Close first window */
    wclose(wdo2);                                 /* Close Second window*/
    vcend(CLOSE);                                 /* Clean up and exit  */
    }

 
