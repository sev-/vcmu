/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:40
*
*   Name            vcprtwdo.c  --  print window to printer
*
*   Description     This function prints a window to the printer
*
*   Return Value    Returns the valued returned by the called
*                   function or the key
*                    
*
**/

#include <vcstdio.h>

COUNT vcprtwdo(wptr,mapfunc)
WPTR wptr;          /* Window to print                              */
PFI mapfunc;        /* Pointer to function for characters           */
    {
    TEXT *wimage, *wmemloc();
    COUNT wvirtsiz();
    VOID vcprtchr();
    COUNT wrow,wcol;
    COUNT prow=0,pcol=0;
    COUNT prevattr = -1;
    COUNT vcprtfls();
    if( (wimage=wptr->location) == NULLTEXT )
        return(-1);
    if(wvirtsiz(wptr,&wrow,&wcol) == -1 )
        return(-2);
    while( prow < wrow )
        {
        while( pcol < wcol )
            {
            if( mapfunc )
                {
                if( prevattr != *(wimage+1) )
                    {
                    prevattr=(*mapfunc)(wptr,*(wimage+1));
                    }
                }
            vcprtchr(*wimage);
            wimage++;
            wimage++;
            pcol++;
            }
        vcprtchr('\n');
        pcol=0;
        prow++;
        }
    vcprtfls();
    return(0);
    }

