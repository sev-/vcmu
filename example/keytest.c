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
*   Name            keytest -- Test keyboard setup        
*                                   
*   Description     Displays the values and label associated with        
*                   a key.  Used to check termcap file for proper
*                   setup.
*
*   Return Value    None.              
*                                   
**/                                 

#include <vcstdio.h>

main()
    {
    TEXT *getlabel(),*ptr,buf[80];
    COUNT key=0;
    vcstart(0);
    screen_one();
    while(key != vckey.esc)
        {
        key=getone();
        atsaynum(10,44,&key,"####",FLDINT);
        if((ptr = getlabel(vcterm.firstkeylbl,key)) == NULL)
            ptr = (TEXT *)"None";
        atsay(12,44,ptr);
        eraeol();
        }
    vcend(CLOSE);
    }

screen_one()
    {
    erase();
    atsay(10,30,"Value of Key:");
    atsay(12,30,"Label of Key:");
    atsay(19,25,"        Press any Key          ");
    atsay(20,25,"         ESC to Quit        ");
    }
