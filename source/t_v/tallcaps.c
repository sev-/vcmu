/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:15:53
*
*   Name            tallcaps -- temporary allcaps         
*                                   
*   Description     Returns a pointer to a new buffer contain
*                   the string in allcaps.  Because this function
*                   uses a static buffer, it should not be call more
*                   than once on any line            
*
*   Return Value    Returns pointer to ALLCAPSBUF
*                                   
**/                                 

#include <vcstdio.h>

TEXT ALLCAPBUF[132];

TEXT *tallcaps(str)
TEXT *str;
    {
    TEXT *strncpy();
    VOID allcaps();
    if(str == NULLTEXT)
        return(NULLTEXT);
    strncpy(ALLCAPBUF,str,131);
    allcaps(ALLCAPBUF);
    return(ALLCAPBUF);
    }
