/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:42
*
*   Name            vcputc.c  --  Put character and attribute
*
*   Description     This function puts a character and attribute
*                   to the screen and increments the column by
*                   one.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID vcputc(ch,attr)
TEXT ch;            /* Character to display                         */
COUNT attr;         /* Attribute to character                       */
    {
    TEXT outbuf[3];
#ifdef TERMINAL
    TEXT loc[2];
#endif
    COUNT wputchr();
    VOID vca_put();
    VOID at();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcputc:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if(wdoctrl->wno_opn && !override)
        {
        wputchr(wdoctrl->wcurrent,ch,attr);
        vcrow=wdoctrl->wcurrent->r_pos;
        vccol=wdoctrl->wcurrent->c_pos;
        }
    else
        {
        outbuf[0]=ch;
        outbuf[1]=attr;
        vca_put(vcrow,vccol,outbuf,1);
        if(vccol < vcterm.cols-1)
            vccol++;
        else
            {
            vccol = 0;
            if(vcrow < vcterm.rows-1)
                vcrow++;
            else
                vcrow = 0;
            }
#ifdef IBM
#ifdef TERMINAL
        if(vctio != 5)
#endif
            at(vcrow,vccol);
#endif
#ifdef OS2
#ifdef TERMINAL
        if(vctio != 5)
#endif
            at(vcrow,vccol);
#endif
        }

#else

#ifdef TERMONLY
        {
        loc[0] = ch;
        loc[1] = '\0';
        vca_cput(loc,attr);
        }
#endif
#ifdef IBM
#ifdef TERMINAL
        if(vctio == 5)
            {
            loc[0] = ch;
            loc[1] = '\0';
            vca_cput(loc,attr);
            }
        else
            {
#endif
        outbuf[0]=ch;
        outbuf[1]=attr;
        vca_put(vcrow,vccol,outbuf,1);
        if(vccol < vcterm.cols-1)
            vccol++;
        else
            {
            vccol = 0;
            if(vcrow < vcterm.rows-1)
                vcrow++;
            else
                vcrow = 0;
            }
#ifdef TERMINAL
        }
        if(vctio != 5)
#endif
        at(vcrow,vccol);
#endif
#ifdef OS2
#ifdef TERMINAL
        if(vctio == 5)
            {
            loc[0] = ch;
            loc[1] = '\0';
            vca_cput(loc,attr);
            }
        else
            {
#endif
        outbuf[0]=ch;
        outbuf[1]=attr;
        vca_put(vcrow,vccol,outbuf,1);
        if(vccol < vcterm.cols-1)
            vccol++;
        else
            {
            vccol = 0;
            if(vcrow < vcterm.rows-1)
                vcrow++;
            else
                vcrow = 0;
            }
#ifdef TERMINAL
        }
        if(vctio != 5)
#endif
        at(vcrow,vccol);
#endif

#endif
    }
