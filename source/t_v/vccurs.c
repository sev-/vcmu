/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:17
*
*   Name            vccurs.c  --  Cursor on or off
*
*   Description     This turn the cursor on or off.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID vccurs(code)
PFAST COUNT code;   /* 1=On Reg:2=On Alt:3=Off Reg:4=Off Reg        */
    {
#ifdef IBM
    FAST COUNT cur_start,cur_end;
    COUNT vcgetcur();
    VOID vcsetcur();
    VOID tvccurs();
#ifdef TERMINAL
    if((vctio == 5) && (vcterm.cf != NULLTEXT))
        {
        tvccurs(code);
        return;
        }
#endif
    cur_end = (vcvram == (COUNT)0xb000 ? 12 : 7);
    cur_start = cur_end - 1;
    if(code == ON)
        {
        if(vccursor <= 2)
            return;
        if(vccursor == 3)
            cur_end += (cur_start << 8);
        else
            {
            cur_start = cur_end/2;
            cur_end += (cur_start << 8);
            }    
        vcsetcur(cur_end);
        vccursor -= 2;
        }
    if(code == OFF)
        {
        if(vccursor > 2)
            return;
        vcsetcur(vcgetcur() | OFFCURSOR);
        vccursor += 2;
        }
    if(code == NORMCURSOR)
        {
        if((vccursor <= 1) || (vccursor == 3))
            return;
        cur_end += (cur_start << 8);
        vcsetcur(cur_end);
        if(vccursor <= 2 )
            vccursor = 1;
        else
            vccursor = 3;
        }
    if(code == ALTCURSOR)
        {
        if((vccursor == 2) || (vccursor == 4))
            return;
        cur_start = cur_end/2;
        cur_end += (cur_start << 8);
        vcsetcur(cur_end);
        if(vccursor <= 2 )
            vccursor = 2;
        else
            vccursor = 4;
        }
    return;
#endif
#ifdef TERMONLY
    VOID tvccurs();
    tvccurs(code);
#endif
#ifdef OS2
    FAST COUNT cur_start,cur_end;
    VIOCURSORINFO curinfo;
#ifdef TERMINAL
    VOID tvccurs();
    if((vctio == 5) && (vcterm.cf != NULLTEXT))
        {
        tvccurs(code);
        return;
        }
#endif
    VioGetCurType(&curinfo,0);
    cur_start = cur_end - 1;
    if(code == ON)
        {
        if(vccursor <= 2)
            return;
        vccursor -= 2;
        if(vccursor == 1)
            curinfo.yStart = curinfo.cEnd - 2;
        else
            curinfo.yStart = curinfo.cEnd / 2;
        curinfo.attr = 0;
        VioSetCurType(&curinfo,0);
        }
    if(code == OFF)
        {
        if(vccursor > 2)
            return;
        curinfo.attr = -1;
        VioSetCurType(&curinfo,0);
        vccursor += 2;
        }
    if(code == NORMCURSOR)
        {
        if((vccursor <= 1) || (vccursor == 3))
            return;
        if(vccursor <= 2 )
            {
            curinfo.yStart = curinfo.cEnd - 2;
            VioSetCurType(&curinfo,0);
            vccursor = 1;
            }
        else
            vccursor = 3;
        }
    if(code == ALVCURSOR)
        {
        if((vccursor == 2) || (vccursor == 4))
            return;
        if(vccursor <= 2 )
            {
            curinfo.yStart = curinfo.cEnd / 2;
            VioSetCurType(&curinfo,0);
            vccursor = 2;
            }
        else
            vccursor = 4;
        }
    return;
#endif
   }

#ifdef IBM
VOID vcsetcur(lines)
COUNT lines;
    {
    VOID vcint();
    struct VCREGS ir,or;
    ir.ax = 0x100;
    ir.cx = lines;
    vcint(0x10,&ir,&or);
    }

COUNT vcgetcur()
    {
    VOID vcint();
    struct VCREGS ir,or;
    ir.ax = 0x300;
    vcint(0x10,&ir,&or);
    return(or.cx);
    }
#endif

