/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:13
*
*   Name            wdelbox -- delete box                  
*                                   
*   Description     Deletes a box from the window                        
*
*   Return Value    VOID
*                                   
**/                                 

#include <vcstdio.h>

static TEXT top[160],bot[160];

VOID wdelbox(wptr,up_r,up_c,lo_r,lo_c,attr)
WPTR wptr;          /* Pointer to window to display on              */
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
    VOID wxatsay();
    COUNT vcpee();
    VOID vcflush();
    if(attr == vc.dflt)
        attrb = (TEXT) wptr->say_at;
    else
        attrb = (TEXT) attr;
    width=lo_c-up_c;
    top[0] = ' ';
    bot[0] = ' ';
    side[0] = ' ';
    side[1] = '\0';
    for(cnt=1;cnt < width ;cnt++)
        top[cnt]=bot[cnt] = ' ';
    top[cnt] = ' ';
    bot[cnt++] = ' ';
    top[cnt] = bot[cnt] = '\0';
#ifdef TERMINAL
    if(vctio == 5)
        flow = vcpee();
#endif
    wxatsay(wptr,up_r,up_c,top,attrb);
    wxatsay(wptr,lo_r,up_c,bot,attrb);
    for(cnt=up_r+1;cnt < lo_r;cnt++)
        {
        wxatsay(wptr,cnt,up_c,side,attrb);
        wxatsay(wptr,cnt,lo_c,side,attrb);
        }
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    }
