/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:32
*
*   Name            timeloop.c  --  displays time
*
*   Description     Displays time at location set by timeloc(). 
*                   Format of display is hh:mm:ss
*
*   Return Value    VOID
*                    
*
**/

#include <vcstdio.h>

COUNT vctimrow=0;
COUNT vctimcol=0;
COUNT vctimattr = -1;
WPTR vctimwdo = (WPTR) 0;

VOID timeloop()
    {
    static TEXT oldtim[20];
    WPTR wptr;
    COUNT row,col;
#ifdef TERMINAL
    COUNT flow = 0;
#endif
    TEXT newtim[20];
    VOID GETTIME();
    TEXT *strncmp();
    TEXT *strcpy();
    VOID atsay();
    VOID xatsay();
    VOID watsay();
    VOID wxatsay();
    GETTIME(newtim);
    if(strncmp(oldtim,newtim,8))
        {
        strcpy(oldtim,newtim);
        oldtim[8] = '\0';
#ifdef TERMINAL
        flow = vcpee();
#endif
        wptr = wdoctrl->wcurrent;
        row = wptr->r_pos;
        col = wptr->c_pos;
        if(vctimwdo == (WPTR) 0)
            {
            if(vctimattr == vc.dflt)
                atsay(vctimrow,vctimcol,oldtim);
            else
                xatsay(vctimrow,vctimcol,oldtim,vctimattr);
            }
        else
            {
            if( vctimattr == vc.dflt )
                watsay(vctimwdo,vctimrow,vctimcol,oldtim);
            else
                wxatsay(vctimwdo,vctimrow,vctimcol,oldtim,vctimattr);
            }
        wat(wptr,row,col);
#ifdef TERMINAL
        if(flow)
            vcflush();
#endif
        }
    }

