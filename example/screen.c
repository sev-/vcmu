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
*   Name            button.c
*                                   
*   Description     Test new button and window defines
*
**/

#include <vcstdio.h>

main(argc,argv)
int argc;
char *argv[];
    {
    COUNT x;
    TEXT ontime[12],offtime[12];
    if(argc > 1)
        vctio = atoi(argv[1]);
    vcstart(CLRSCRN);
    gettime(ontime);   
    for(x=0;x<20;x++)
        {
        wxxopen(x,0,vcterm.rows-1,vcterm.cols-1," Windows! ",ACTIVE+BORDER,0,0,1,'1');
        }
    gettime(offtime);
    elapstim(ontime,offtime);
    atsay( 5,5,ontime);
    getone();
    vcend(CLOSE);
    }

