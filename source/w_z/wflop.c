/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:31
*
*   Name            wflop.c  --  Move from scratch window to window
*
*   Description     This function takes {dth} rows and {wth} columns starting
*                   at location 0,0 on the scratch window and moves it to the
*                   virtual window (number) starting at the location relative
*                   to {trow},{tcol} on the screen and window (number).
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wflop(wptr,toprow,topcol,dth,wth,attr)
WPTR wptr;          /* Pointer to Window to place information       */
COUNT toprow,topcol;/* Upper left row and column                    */
COUNT dth,wth;      /* Depth and width to copy                      */
COUNT attr;         /* True = move attribute                        */
    {
    FAST COUNT cnt1,cnt2;
    COUNT bd;
    COUNT temp1,temp2;
    COUNT dif1,dif2,tmp1,tmp2;
    TEXT *cpntr,*cpntr2;
    WPTR wptr2;
    COUNT offset;
    VOID wborder();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wflop:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    wptr2 = wdoctrl->wcutwdo;
    bd=(wptr->wctrl & BORDER ? 1 : 0);
    temp1=(((topcol-wptr->upper_c) == 0) && bd ? 1 : topcol-wptr->upper_c);
    temp2=(((toprow-wptr->upper_r) == 0) && bd ? 1 : toprow-wptr->upper_r);
    dif1=wptr->cur_c+temp1-bd;
    dif2=wptr->cur_r+temp2-bd;
    dif1=(dif1 < 0 ? 0 : dif1);
    dif2=(dif2 < 0 ? 0 : dif2);
    offset = ((dif2*wptr->width+dif1) << 1);
    cpntr=wptr->location+offset;
    cpntr2=wptr2->location;
    dth = min(dth,(wptr->depth-dif2));
    wth = min(wth,(wptr->width-dif1));
    tmp1 = (wptr->width-wth) << 1;
    tmp2 = (vcterm.cols-wth) << 1;
    for(cnt1=0;cnt1 < dth;cnt1++)
        {
        for(cnt2=0;cnt2 < wth;cnt2++)
            {
            *(cpntr++) = *(cpntr2++);
            if(attr == 1)
                *(cpntr++) = *(cpntr2++);
            else
                {
                cpntr++;
                cpntr2++;
                }
            }
        cpntr += tmp1;
        cpntr2 += tmp2;
        }
    if(bd)
        wborder(wptr,-1);
    }

#endif


