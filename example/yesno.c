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
*   Name            yesno.c  
*                                   
*   Description     Examples of yes and no answers
*
**/

#include <vcstdio.h>

main()
    {
    TEXT yesno[2];
    COUNT yesnopic();
    vcstart(CLRSCRN);
    wopen(2,2,20,70," Yes / No Examples ");
    addpic('Y',yesnopic);
    empty(yesno,2);
    atsay(2,2,"Your Answer:   (Y/N)");
    atget(2,15,yesno,"Y");
    readgets();
    vcend(CLOSE);
    }

COUNT yesnopic(key)
COUNT key;
    {
    COUNT retval = FALSE;
    if((key == 'Y') || (key == 'y') ||
       (key == 'N') || (key == 'n')   )
        retval = TRUE;
    return(retval);
    }
