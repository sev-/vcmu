/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:27
*
*   Name            delbox -- delete box                  
*                                   
*   Description     Deletes a box from the screen                        
*
*   Return Value    VOID
*                                   
**/                                 

#include <vcstdio.h>

static TEXT top[160],bot[160];

VOID delbox(up_r,up_c,lo_r,lo_c,attr)
COUNT up_r,up_c;    /* Upper left row and column                    */
COUNT lo_r,lo_c;    /* Lower right row and column                   */
COUNT attr;         /* Attribute to use                             */
    {
    TEXT side[2],attrb;
    COUNT width;
    FAST COUNT cnt;
#ifdef TERMINAL
    COUNT flow=0;
#endif
    VOID xatsay();
    COUNT vcpee();
    VOID vcflush();
    attrb = (TEXT) attr;
    width=lo_c-up_c;
    top[0] = ' ';
    bot[0] = ' ';
    side[0] = ' ';
    side[1] = '\0';
#ifdef TERMINAL
    if(vctio == 5)
        flow = vcpee();
#endif
    for(cnt=1;cnt < width ;cnt++)
        top[cnt]=bot[cnt] = ' ';
    top[cnt] = ' ';
    bot[cnt++] = ' ';
    top[cnt] = bot[cnt] = '\0';
    xatsay(up_r,up_c,top,attrb);
    xatsay(lo_r,up_c,bot,attrb);
    for(cnt=up_r+1;cnt < lo_r;cnt++)
        {
        xatsay(cnt,up_c,side,attrb);
        xatsay(cnt,lo_c,side,attrb);
        }
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    }
