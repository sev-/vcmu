/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:56
*
*   Name            wwtb.c  --  Write temporary border
*
*   Description     This function writes a temporary border to the
*                   physical screen. It does not write it to the 
*                   memory screen so any refresh will make it 
*                   disappear. This is used to cut and paste and
*                   in window adjust.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

static TEXT top[320],bot[320];

VOID wwtb(up_r,up_c,lo_r,lo_c,attr)
COUNT up_r,up_c;    /* Upper left row and column                    */
COUNT lo_r,lo_c;    /* Lower right row and column                   */
COUNT attr;         /* Attribute to use                             */
    {
    TEXT side[2],attrb;
    COUNT width;
    FAST COUNT cnt;
#ifdef TERMINAL
    COUNT flow = 0;
#endif
    COUNT vcpee();
    VOID vcflush();
    VOID vca_put();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wwtb:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    attrb = (TEXT) attr;
    width=lo_c-up_c;
#ifdef TERMINAL
    if(vctio == 5)
        flow=vcpee();
#endif
    top[0]=border[1].tl;
    top[1]=attrb;
    bot[0]=border[1].bl;
    bot[1]=attrb;
    side[0]=border[1].up;
    side[1]=attrb;
    for(cnt=2;cnt < (width << 1);cnt++)
        {
        top[cnt]=bot[cnt]=border[1].across;
        cnt++;
        top[cnt]=bot[cnt]=attrb;
        }
    top[cnt]=border[1].tr;
    bot[cnt++]=border[1].br;
    top[cnt]=bot[cnt]=attrb;
    vca_put(up_r,up_c,top,width+1);
    vca_put(lo_r,up_c,bot,width+1);
    for(cnt=up_r+1;cnt < lo_r;cnt++)
        {
        vca_put(cnt,up_c,side,1);
        vca_put(cnt,lo_c,side,1);
        }
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    }

#endif


