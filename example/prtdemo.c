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
*   Name            prtdemo -- Print demo                 
*                                   
*   Description     Test the printer functions                           
*
*                                   
**/                                 

#define VCKEY_DEFS
#include <vcstdio.h>

main(argc,argv)
COUNT argc;
TEXT *argv[];
    {
    TEXT msg[50];
    COUNT printwdo();
    vcstart(CLRSCRN);
    setkeytrap(printwdo);
    wopen(0,0,vcterm.rows-1,vcterm.cols-1,"Print Demo");
    xatsay(18,27,"Press F3 to print Window",vc.black+(vc.white*vc.bg));
    xatsay(20,25,"Press Ctrl-P to print Screen",vc.black+(vc.white*vc.bg));
    vcprtopn(NULL);  /* Open default "/dev/vcprt" link to printer */
    while(TRUE)
        {
        empty(msg,50);
        atsayget(10,5,"Enter Message ",msg,NULL);
        readgets();
        if(isblank(msg))
            break;
        vcprtstr(msg);
        vcprtstr("\n\r");
        }
    vcend(CLOSE);
    }

COUNT printwdo(key)
COUNT key;
    {
    if(key == F3)
        {
        vcprtwdo(wdoctrl->wcurrent,NULLFUNC);
        key = 9999;
        }
    return(key);
    }
