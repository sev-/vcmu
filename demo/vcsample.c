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
*   Name            vcsample
*                                   
*   Description     Simple sample for Vitamin C
*
*   Return Value    None.
*                                   
**/                                 

#include <vcstdio.h>

main()
    {
    vcstart(CLRSCRN);                   /* Start Vitamin C          */
    wopen(2,10,14,40,vcterm.tmname);    /* Open Window              */
    atsay(2,2,"Hello World");           /* Print Message            */
    getone();                           /* Wait for input           */
    vcend(CLOSE);                       /* End Vitamin C            */
    }


