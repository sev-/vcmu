/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:14
*
*   Name            longpre.c  --  Long pre-function
*
*   Description     This is the long pre-function.
*                   translates the number to string.
*
*   Return Value    Returns -1 if error
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

#define DEFLONGSIZ 14

COUNT longpre(gi)
GETITEM *gi;        /* Get item to convert                          */
    {
    TEXT *vcalloc(),*tmppic();
    COUNT len;
    LONG *lp;
    TEXT buf[64];
    COUNT strlen();
    VOID empty();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "longpre:";
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
        len = DEFLONGSIZ;
        if((gi->gtmpfld = vcalloc(1,len,vcdebug)) != NULLTEXT)
            gi->gtmppic = tmppic(gi->gtmpfld,'#');
        }
    if(gi->gtmpfld == NULLTEXT)
        return(-1);
    lp = (LONG *)gi->g_field;
    sprintf(buf,"%ld",*lp);
    empty(gi->gtmpfld,len);
    len--;
    strncpy(gi->gtmpfld,buf,min(len,strlen(buf)));
    gi->g_length = len;
    gi->gmaxwid = 0;
    if(gi->gdispsiz == -1)
        gi->gdispsiz = len;
    else
        gi->gdispsiz = min(len,gi->gdispsiz);
    return(0);
    }


