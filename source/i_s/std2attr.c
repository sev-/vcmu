/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:31
*
*   Name            std2attr - standard to attribute      
*                                   
*   Description     Converts from the color standards to the             
*                   current colors
*
*   Return Value    Returns the color
*                                   
**/                                 

#include <vcstdio.h>

COUNT std2attr(attr)
UCOUNT attr;
    {
    COUNT fg;       /* Foreground value                             */
    COUNT bg;       /* Background value                             */
    COUNT bl;       /* Is blinking on                               */
    COUNT bo;       /* Is bold on                                   */
    COUNT *ptr;     /* Pointer to colors                            */
    FAST COUNT color;/* Described color                             */
    ptr = (COUNT *)&vc.black;
    if(attr < 256)
        return(attr);
    if(attr == 65535)
        return(-1);
    attr = attr >> 8;
    fg = attr & 7;
    bg = (attr >> 4) & 7;
    bl = attr & 128;
    bo = attr & 8;
    color = *(ptr+fg);
    color += (*(ptr+bg))*vc.bg;
    if(bl)
        color += vc.blink;
    if(bo)
        color += vc.bold;
    return(color);
    }    

