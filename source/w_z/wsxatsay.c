/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:47
*
*   Name            wsxatsay - put special string to window        
*
*   Description     This function places the special attributes on       
*                   the screen for terminal where attributes require
*                   a space
*
*   Return Value    VOID
*                                   
**/                                 

#include <vcstdio.h>

#ifdef TERMINAL

VOID wsxatsay(wptr,row,col,str,attr)
WPTR wptr;
COUNT row;
COUNT col;
TEXT *str;
COUNT attr;
    {
    COUNT crow,ccol;
    COUNT bd;
    TEXT hold[2];
    COUNT len;
    COUNT unfreeze = FALSE;
    COUNT flow = 0;
    VOID wplace_cur();
    COUNT ckspattr();
    COUNT whit();
    COUNT winwdo();
    VOID vca_put();
    VOID wputs();
    VOID vcflush();
    COUNT vcpee();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wsxatsay:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    flow = vcpee();
    bd=(wptr->wctrl & BORDER ? 1: 0);
    wptr->r_pos = row;
    wptr->c_pos = col;
    wplace_cur(wptr);
    row = wptr->r_pos;
    col = wptr->c_pos;
    len = strlen(str);
    crow = wptr->upper_r+bd-wptr->cur_r+row;
    ccol = wptr->upper_c+bd-wptr->cur_c+col;
    if(vcterm.mc)
        {
        len += 2;
        if(ccol == 0)
            {
            if(ckspattr(attr))
                {
                col++;
                str++;
                len--;
                wptr->c_pos = col;
                wplace_cur(wptr);
                }
            }
        else
            {
            ccol--;
            }
        }
    if(!wdoctrl->wfreeze && (wptr->wctrl & ACTIVE))
            /* May Need && whit(wptr,crow,ccol) &&
                        winwdo(wptr,crow,ccol)   */
        {
        wdoctrl->wfreeze = TRUE;
        unfreeze = TRUE;
        }
    wputs(wptr,str,attr);
    if(unfreeze)
        {
        wdoctrl->wfreeze = FALSE;
        wstack(wptr);
        if((wbound(wptr)) || (wptr->r_pos != row))
            wwrtdw(wptr);
        else
            {
            vca_put(crow,ccol,wscreen+(((vcterm.cols*crow)+ccol) << 1),len);
            }
        wplace_cur(wdoctrl->wcurrent);
        }
    if(flow)
        vcflush();
    }

#endif
