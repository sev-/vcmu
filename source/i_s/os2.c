/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:36
*
*   Name            os2.c - os2 files
*                                   
*   Description     File necessary for OS2
*
*   Return Value    
*                                   
**/

#include <vcstdio.h>

#ifdef OS2

COUNT vcin()
    {
    KBDKEYINFO keyinfo;
    COUNT retval;
    COUNT firsttime = TRUE;
    COUNT bufkdy();
    COUNT gbufkey();
    COUNT xkeyrdy();
    while(!xkeyrdy())
        if(waitfunc)
            (*waitfunc)();
    while(TRUE)
        {
        KbdCharIn(&keyinfo,0,0);
        if(firsttime)
            {
            vcshift = keyinfo.fsState;
            retval = keyinfo.chChar;
            firsttime = FALSE;
            }
        else
            ungetone(keyinfo.chChar);
        if((keyinfo.chChar == 0) || 
           (keyinfo.chChar == 0xe0))
            ungetone(keyinfo.chScan);
        if(keyinfo.fbStatus & 0x40)
            break;
        }
    return(retval);
    }

COUNT vcout(buf,nbytes)
TEXT *buf;
COUNT nbytes;
    {
    int write();
    return((COUNT)write(1,buf,(int)nbytes));
    }

COUNT xkeyrdy()
    {
    KBDKEYINFO keyinfo;
    KbdPeek(&keyinfo,0);
    return(keyinfo.fbStatus & 0x40);
    }

#endif





