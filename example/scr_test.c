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
*   Name            scr_test.c
*                                   
*   Description     Test some unusual screen features
*
**/

#include <vcstdio.h>

TEXT *mess[] =
    {
    (TEXT *)"Message 0:This is a Test",
    (TEXT *)"Message 1:First Line \nMessage 1:Second line \nMessage 1:Third line \n",
    (TEXT *)"\nMessage 2:First Line \nMessage 2:Second line \nMessage 2:Third line \n\n",
    (TEXT *)"\nMessage 3:First Line \nMessage 3:Second line \nMessage 3:Third line \n\n\n",
    NULLTEXT
    };

WPTR wptr,status;

main()
    {
    WPTR wxopen();
    COUNT trap(),prtstatus();
    vcstart(CLRSCRN);
    status = wxopen(0,0,3,vcterm.cols-1,"Status",BORDER+ACTIVE,0,0);
    wptr = wxopen(18,0,vcterm.rows-1,vcterm.cols-1,"Message Window",
            COOKED+BORDER+ACTIVE+NOAUTO+SCROLL,80,0);
    setloop(prtstatus);
    prtstatus();
    setup();
    setkeytrap(trap);
    while(getone() != vckey.esc);
    vcend(CLOSE);
    }

setup()
    {
    COUNT i; 
    for(i=0;i<80;i++)
        atsaynum(i,75,&i,"##",FLDINT);
    at(0,0);
    }

prtstatus()
    {
    TEXT buffer[80];
    sprintf(buffer,
"  Current Row = %d  Current_Column = %d    Upper Left: row = %d  col = %d",wptr->r_pos,
            wptr->c_pos,wptr->cur_r,wptr->cur_c);
    woff();
    werase(status);
    watsay(status,0,0,buffer);
    wdoctrl->wfreeze = 0;
    wupdate(status);
    wwrtdw(status);
    }

COUNT trap(key)
COUNT key;
    {
    COUNT row,col;
    if((key >= '1') && (key <= '4'))
        {
        message(mess[key - '1']);
        key = 9999;
        }
    if((key == vckey.cur_down) ||
       (key == vckey.cur_up) )
        {
        row = wptr->cur_r;
        col = wptr->cur_c;
        wscroll(wptr,key,1);
        if((row == wptr->cur_r) && (col == wptr->cur_c))
            bell();
        key = 9999;
        }
    return(key);
    }

message(msg)
TEXT *msg;
    {
    while(*msg < ' ')
        wputchr(wptr,*(msg++),wptr->say_at);
    wptr->wctrl &= ~NOAUTO;
    wputchr(wptr,*(msg++),wptr->say_at);
    wptr->wctrl |= NOAUTO;
    while( *msg != '\0')
        wputchr(wptr,*(msg++),wptr->say_at);
    if(wptr->c_pos)
        wputchr(wptr,'\n',wptr->say_at);
    }
    

