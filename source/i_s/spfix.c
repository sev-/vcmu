/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:20
*
*   Name            spfix.c -- Space fix
*
*   Description     Fixes the memory image for terminals that 
*                   require spaces for attributes.
*
*   Return Value    VOID    
*
**/

#include <vcstdio.h>

VOID spfix()
    {
    FAST TEXT *sptr,curattr;
    COUNT status=0;
    COUNT attr_line=1;
    FAST COUNT col = 0;
    FAST COUNT row = 0;
    COUNT ckspattr();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "spfix:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    sptr=wscreen;
    curattr = *(sptr+1);
    while(row < vcterm.rows)
        {
        col = 0;
        if(attr_line)
            {
            curattr = *(sptr+1);
            status = 0;
            }
        if(ckspattr(curattr) && !status)
            {
            status = TRUE;
            *sptr = AT_ON;
            }
        while( col < vcterm.cols)
            {
            sptr += 2;
            col++;
            while((*(sptr+1) == curattr) && (col < vcterm.cols))
                {
                col++;
                sptr += 2;
                }
            if(col >= vcterm.cols)
                break;
            curattr = *(sptr+1);
            if(ckspattr(curattr))
                {
                if(status)
                    {
                    *sptr = AT_ON;
                    }
                else
                    {
                    status = TRUE;
                    if( *sptr != AT_ON)
                        {
                        *(sptr-1) = curattr;
                        *(sptr-2) = AT_ON;
                        }
                    }
                }
            else
                {
                if(status && (col < vcterm.cols))
                    {
                    status = FALSE;
                    if( *(sptr-2) != AT_OFF)
                        {
                        *sptr = AT_OFF;
                        *(sptr+1) = *(sptr-1);
                        }
                    }
                }
            }
        row++;
        }
    }

