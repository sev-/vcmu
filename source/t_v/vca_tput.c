/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:01
*
*   Name            vca_tput.c  --  Terminal put
*
*   Description     This program puts a buffer of character and 
*                   attribute combinations to a terminal while 
*                   checking a memory image of the terminal to see
*                   if necessary.
*                   
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

extern TEXT vcspfill;
extern COUNT vcspafill;

VOID vca_tput(row,col,buffer,len)
COUNT row,col;      /* Row and Column to put information            */
TEXT *buffer;       /* Buffer to put on terminal                    */
COUNT len;          /* Len of buffer in words (two bytes)           */
    {
    COUNT twidth;
    FAST TEXT *sptr;
    TEXT *bptr,*ssptr;
    FAST COUNT cnt=0;
    COUNT start,amt;
    TEXT *ch;
    COUNT attr;
    VOID vca_cput();
    VOID vcmem();
    VOID term_at();
    VOID vcalmode();
    VOID dist_str();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vca_tput:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if((vcterm.xs == 1) && (len > 1))
        vcalmode(&row,&col,&buffer,&len);
    twidth = vcterm.cols << 1;
    sptr = tscreen+(row*twidth)+(col << 1);
    if((vcterm.am == 1) && (row == (vcterm.rows-1)) &&
                    ((col+len) == (vcterm.cols)) )
        {
        len--;
        if(vcterm.ic != NULLTEXT) 
            {
            term_at(row,vcterm.cols-2);
            ch = buffer + (len << 1);
            attr = *(ch+1);
            vca_cput(ch,attr);
            term_at(row,vcterm.cols-2);
            dist_str(vcterm.ic,0);
            if(len)
                {
                ch = sptr + ((len - 1) << 1);
                *ch = '\0';
                }
            else
                {
                ch = sptr - 2;
                term_at(row,vcterm.cols-2);
                attr = *(ch+1);
                vca_cput(ch,attr);
                }
            }
        }
    if((vcterm.xs == 1) && (len > 1) )
            {
            if(col)
                {
                termattr = *(sptr-1);
                graphattr = (*(sptr-2) > 127 ? TRUE : FALSE);
                }
            else
                flipattr(NORM_ATTR);
            }
    while(cnt < len)
        {
        while( ( ( *(sptr) == *(buffer) ) && (*(sptr+1) == *(buffer+1)) ) &&
                     (cnt < len) )
            {
            sptr += 2;
            buffer += 2;
            cnt++;
            }
        if(cnt < len)
            {
            bptr = buffer;
            ssptr = sptr;
            start = cnt;
            amt = 0;
            term_at(row,col+cnt);
            while(cnt < len)
                {
                if( ((*sptr != *(buffer)) || (*(sptr+1) != *(buffer+1))))
                    {
                    cnt++;
                    amt++;
                    sptr += 2;
                    buffer += 2;
                    continue;
                    }
                if((++cnt) >= len)
                    break;
                sptr += 2;
                buffer += 2;
                if((*sptr != *(buffer)) || (*(sptr+1) != *(buffer+1)))
                    {
                    cnt++;
                    amt += 2;
                    sptr += 2;
                    buffer += 2;
                    continue;
                    }
                if((++cnt) >= len)
                    break;
                sptr += 2;
                buffer += 2;
                if( (*sptr != *(buffer)) || (*(sptr+1) != *(buffer+1)))
                    {
                    cnt++;
                    amt += 3;
                    sptr += 2;
                    buffer += 2;
                    continue;
                    }
                cnt++;
                sptr += 2;
                buffer += 2;
                break;
                }
            vcmem(ssptr,bptr,amt << 1);
            start += amt;
            while(amt--)
                {
                ch = bptr++;
                attr = *(bptr++);
                if(attr < 0)
                    attr += 256;
#ifdef NOUNSIGNED
                if(vcterm.mc && (*ch <= AT_OFF))
#else
                if(vcterm.mc && (*ch >= AT_OFF))
#endif
                    {
                    ssptr = wscreen+(row*twidth)+((col+cnt-amt-1) << 1);
                    vcspfill = *(ssptr++);
                    vcspafill = *ssptr;
                    if(ckspattr(vcspafill))
                        vcspfill = AT_OFF;
                    }
#ifdef NOUNSIGNED
                if(!vcterm.ms && (*ch <= AT_OFF) && !vcterm.mc)
#else
                if(!vcterm.ms && (*ch >= AT_OFF) && !vcterm.mc)
#endif
                    {
                    if(*ch == AT_OFF)
                        {
                        ssptr = wscreen+(row*twidth)+((col) << 1);
                        if(col < vcterm.cols-1)
                            flipattr(*(ssptr+1));
                        if((*(ssptr) > 127) && (vcterm.gs != NULLTEXT))
                            {
                            dist_str(vcterm.gs,0);
                            graphattr = TRUE;
                            }
                        }
                    else
                        {
                        dist_str(vcterm.ge,0);
                        graphattr = FALSE;
                        flipattr(attr);
                        }
                    }
                else
                    {
                    if(vcterm.xs && (len == 1))
                        {
                        vcterm.mc = TRUE;
                        vca_cput(ch,attr);
                        vcterm.mc = FALSE;
                        }
                    else
                        vca_cput(ch,attr);
                    }
                }
            if((vcterm.ms != 1) && !vcterm.mc && (len > 1))
                {
                if((col+start) < (vcterm.cols-1))
                    {
                    ssptr = tscreen+(row*twidth)+((start+col-1) << 1) ;
                    if((*(ssptr+3) != *(ssptr+1)) )
                        flipattr((COUNT)*(ssptr+3));
                    dist_str(vcterm.ge,0);
                    graphattr = FALSE;
                    }
                else
                    {
                    if(vcterm.xs == 1)
                        {
                        termattr = NORM_ATTR;
                        graphattr = FALSE;
                        }
                    else
                        flipattr(NORM_ATTR);
                    }
                }
            }
        }
    }

TEXT *temptbuff = NULLTEXT;

VOID vcalmode(row,col,buffer,len)
COUNT *row,*col;
TEXT **buffer;
COUNT *len;
    {
    COUNT twidth;
    TEXT *sptr,*tptr;
    TEXT *vcalloc();
    VOID vcmem();
    VOID dist_str();
    VOID term_at();
    twidth = vcterm.cols << 1;
    if(temptbuff == NULLTEXT)
        temptbuff = vcalloc(1,twidth,NULLTEXT);
    sptr = tscreen+((*row) * twidth)+((*col) << 1);
    vcmem(sptr,*buffer,(*len) << 1);
    if(*col)
        {
        sptr -= 2;
        (*col)--;
        }
    term_at(*row,*col);
    dist_str(vcterm.ce,0);
    *len = vcterm.cols - *col;
    sptr = tscreen+((*row) * twidth)+((*col) << 1);
    vcmem(temptbuff,sptr,(*len) << 1);
    tptr = temptbuff;
    twidth = *len;
    while(twidth--)
        {
        *(sptr++) = SPACE;
        *(sptr++) = NORM_ATTR;
#ifdef NOUNSIGNED
        if(*tptr <= AT_OFF)
#else
        if(*tptr >= AT_OFF)
#endif
            {
            *tptr = SPACE;
            *(tptr+1) = NORM_ATTR;
            }
        tptr += 2;
        }
    *buffer = temptbuff;
    }

#endif
