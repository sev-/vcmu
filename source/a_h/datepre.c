/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:22
*
*   Name            datepre.c  --  Standard date  pre-function
*
*   Description     This is the standard date pre-function.
*
*   Return Value    Returns -1 if error and set vcerror
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>
           
COUNT datepre(gi)
GETITEM *gi;        /* Get item to copy                             */
    {
    TEXT *vcalloc();
    LONG *dt;
    COUNT fromjul();
    TEXT *strcpy();
    COUNT gettype();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "datepre:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( (gi->gtmpfld=vcalloc(1,9,vcdebug)) == NULLTEXT)
        return(-1);
    dt = (LONG *)gi->g_field;
    fromjul(*dt,gi->gtmpfld);
    if(gi->g_picture && (gi->g_picture != NULLTEXT))
        gi->gtmppic = gi->g_picture;
    else
        {
        if((gi->gtmppic = vcalloc(1,9,vcdebug)) != NULLTEXT)
            {
            vcfree(gi->gtmpfld,vcdebug);
            return(-1);
            }
        strcpy(gi->gtmppic,DATEEDIT);
        }
    gi->gmaxwid = 0;
    if( gi->gdispsiz == -1)
        gi->gdispsiz = 8;
    else
        gi->gdispsiz = min(gi->gdispsiz,8);
    return(0);
    }

