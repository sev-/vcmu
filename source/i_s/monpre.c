/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:24
*
*   Name            monpre.c  --  Money pre-function
*
*   Description     This is the money pre-function.
*                   translates the long to fixed decimal string.
*
*   Return Value    Returns -1 if error
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

#define DEFMONSIZ 10
#define DEFMONPIC (TEXT *)"$-###,###.##"

COUNT monpre(gi)
GETITEM *gi;                        /* Get item to convert          */
    {
    TEXT *vcalloc(),*tmppic();
    TEXT *ptr;
    COUNT cnt;
    COUNT len;
    COUNT tmp;
    COUNT prec;
    LONG *lp;
    TEXT buf[64];
    COUNT strlen();
    VOID empty();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "monpre:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( gi->g_picture != NULLTEXT )
        {
        len = strlen(gi->g_picture)+1;
        gi->gtmpfld = vcalloc(1,len,vcdebug);
        gi->gtmppic = gi->g_picture;
        }
    else
        {
        len = DEFMONSIZ;
        if((gi->gtmpfld = vcalloc(1,len,vcdebug)) != NULLTEXT)
            strcpy(gi->gtmppic,DEFMONPIC);
        }
    if(gi->gtmpfld == NULLTEXT)
        return(-1);
    prec = rtolprec(gi->gtmppic);
    lp = (LONG *)gi->g_field;
    sprintf(buf,"%ld",*lp);
    cnt = strlen(buf);
    if(cnt >= prec)
        {
        ptr = buf + cnt;
        *(ptr+1) = '\0';
        cnt = prec;
        while(cnt)
            {
            *ptr = *(ptr-1);
            ptr--;
            cnt--;
            }
        *ptr = '.';
        }
    else
        {
        ptr = buf + prec;
        *(ptr+1) = '\0';
        tmp = prec - cnt + 1;
        while(ptr != buf)
            {
            if(cnt)
                *ptr = *(ptr - tmp);
            else
                *ptr = '0';
            ptr--;
            cnt--;
            }
        *ptr = '.';
        }
    empty(gi->gtmpfld,len);
    len--;
    strncpy(gi->gtmpfld,buf,min(len,strlen(buf)));
    gi->g_length = len;
    gi->gmaxwid = prec;
    if(gi->gdispsiz == -1)
        gi->gdispsiz = len;
    else
        gi->gdispsiz = min(len,gi->gdispsiz);
    return(0);
    }


