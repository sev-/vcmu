/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:25
*
*   Name            wexpand.c  --  Expand control codes
*
*   Description     Low level function that expands control character
*                   when window is in COOKED mode.  
*
*   Return Value    Returns the draw variable
*
**/

#include <vcstdio.h>

#define TERM_RET '\r'
#define TERM_LF '\n'
#define TERM_TAB '\t'
#define TERM_BKSP '\b'

COUNT wexpand(wptr,text,attr)
WPTR wptr;
COUNT *text;   
COUNT *attr;
    {
    COUNT draw = 0;
    COUNT temp;
    COUNT parm;
    if( (*text == TERM_RET) || (*text == vckey.ret) )
        {
        draw = -1;
        wptr->c_pos = 0;
        if(wdoctrl->wretlf == 2)
            {
            parm = TERM_LF;
            draw = wexpand(wptr,&parm,attr);
            }
        }
    if( *text == TERM_LF )
        {
        draw = -1;
        if(wdoctrl->wretlf == 1)
            {
            parm = TERM_RET;
            draw = wexpand(wptr,&parm,attr);
            }
        if(wptr->r_pos >= wptr->depth-1)
            { 
            if(wptr->wctrl & SCROLL)
                {
                wsscroll(wptr,0,1);
                draw = -2;
                }
            else
                wptr->r_pos=0;
            }
        else
            wptr->r_pos++;
        }
    if( *text == TERM_TAB )
        {
        draw = -1;
        for(temp=1;(wptr->c_pos >= wtab[temp]) && (temp<=wmaxtab);temp++);
        if(temp < wmaxtab)
            wptr->c_pos = wtab[temp];
        else
            wptr->c_pos = wtab[1];
        }
    if((*text == vckey.backsp) || (*text == TERM_BKSP) || 
        (*text == vckey.cur_left))
        {
        wptr->c_pos--;
        draw = -1;
        }
    if( *text == vckey.cur_right )
        {
        wptr->c_pos += 1;
        draw = -1;
        } 
    if( *text == vckey.cur_up )
        {
        wptr->r_pos--;
        draw = -1;
        }
    if( *text == vckey.cur_down )
        {
        wptr->r_pos++;
        draw = -1;
        }
    if(!(wptr->wctrl & NOAUTO))
        if(wbound(wptr))
            {
            if(draw < 0)
                draw = -2;
            else
                draw = 1;
            }
    if(wdoctrl->wstrip)
        *text &= 0x7f;
    return(draw);
    }

