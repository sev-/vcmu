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
    COUNT row;
    vcstart(0);
    screen_one();
    while(key != 'x')
        {
        row = 10;
        key = xgetone();
        erabox(10,44,16,50);
        atsaynum(row,44,&key,"####",FLDINT);
        while(keyrdy())
            {
            row++;
            key = xgetone();
            atsaynum(row,44,&key,"####",FLDINT);
            }
        }
    vcend(CLOSE);
    }

screen_one()
    {
    erase();
    atsay(10,30,"Value of Key:");
    atsay(19,25,"        Press any Key          ");
    atsay(20,25,"         'x' to Quit        ");
    }
