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
*   Name            tscroll.c
*                                   
*   Description     Test window scrolling
*
**/

#include <vcstdio.h>

WPTR wptr;

main()
    {
    COUNT i,j,key;
    WPTR wxopen();
    COUNT trap(),prtstatus();
    vcstart(CLRSCRN);
    wptr = wxopen(0,0,vcterm.rows-1,vcterm.cols-1,"Message Window",
            BORDER+ACTIVE,0,0);
    key = 'a';
    for(i=0;i<23;i++)
        {
        for(j=0;j<wptr->width;j++)
            wputchr(wptr,key,vc.black+vc.blue*vc.bg);
        key++;
        }
    while((key = getone()) != vckey.esc)
        {
        if((key == vckey.cur_down) ||
           (key == vckey.cur_up) )
            {
            wsscroll(wptr,key,3);
            won();
            }
        }
    vcend(CLOSE);
    }




