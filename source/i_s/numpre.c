/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:31
*
*   Name            numpre.c  --  Standard number pre-function
*
*   Description     This is the standard number pre function.
*                   translates the number to string.
*
*   Return Value    Returns -1 if error
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

#define REALDFTSIZ 21

COUNT numpre(gi)
GETITEM *gi;        /* Get item to convert                          */
    {
    TEXT *vcalloc(),*tmppic(),*p;
    COUNT len,prec = 0;
    double *dp;
    TEXT buf[64];
    COUNT strlen();
    VOID empty();
    COUNT rtolprec();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "numpre:";
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
        len = REALDFTSIZ;
        if((gi->gtmpfld = vcalloc(1,len,vcdebug)) != NULLTEXT)
            gi->gtmppic = tmppic(gi->gtmpfld,'#');
        }
    if(gi->gtmpfld == NULLTEXT)
        return(-1);
    prec = rtolprec(gi->gtmppic);
    dp = (double *)gi->g_field;
    sprintf(buf,"%.*lf",prec,*dp);
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


