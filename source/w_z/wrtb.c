/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:23
*                
*   Name            wrtb.c  --  remove temporary border
*
*   Description     Removes a temporary border described by
*                   upr,upc and lor,loc. Uses the memory screen
*                   as the correct image so the memory screen
*                   must be kept perfect.
*
*   Return Value    VOID
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef WINDOW

VOID wrtb(up_r,up_c,lo_r,lo_c)
COUNT up_r,up_c;    /* Upper left row and column                    */
COUNT lo_r,lo_c;    /* Lower right row and column                   */
    {
    COUNT width,twidth,across,nrow;
#ifdef TERMINAL
    COUNT flow = 0;
#endif
    FAST COUNT cnt;
    FAST TEXT *sptr;
    COUNT vcpee();
    VOID vca_put();
    VOID vcflush();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wrtb:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    twidth = vcterm.cols << 1;
    width=lo_c-up_c+1;
    if((up_r < 0) || (lo_r < up_r) ||
       (up_c < 0) || (lo_c < up_c)  )
        {
        vcerror = WTBCOORD;
        return;
        }
#ifdef TERMINAL
    if(vctio == 5)
        flow=vcpee();
#endif
    sptr = wscreen+(up_r*twidth)+(up_c << 1);
    vca_put(up_r,up_c,sptr,width);
    sptr += twidth;
    across = (width << 1)-2;
    nrow = twidth-across;
    for(cnt=up_r+1;cnt < lo_r;cnt++)
        {
        vca_put(cnt,up_c,sptr,1);
        sptr += across;
        vca_put(cnt,lo_c,sptr,1);
        sptr += nrow;
        }
    if(up_r != lo_r)
        vca_put(lo_r,up_c,sptr,width);
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    return;
    }

#endif


