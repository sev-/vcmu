/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:59
*
*   Name            seqgetstd.c  --  Sequences gets standard
*
*   Description     This is the function that is called by default
*                   to sequence gets to appear in order that they
*                   are issued
*
*   Return Value    Returns -1 if error
*
**/

#define VCERROR_DEFS
#define VCGET_DEFS
#include <vcstdio.h>

COUNT seqgetstd(gtp)
GETTABLE *gtp;
    {
    GETITEM *gp,*prevget = (GETITEM *)0;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "seqgetstd:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( gtp == (GETTABLE *)0 )
        {
        vcerror= SEQBADGTBL;
        return(-1);    /* no get table pointer passed */
        }
    if( gtp->tmagic != GETTBLMAGIC )
        {
        vcerror= SEQBADGTBL;
        return(-1);  /* This isn't a get table node! */
        }
    gtp->tcurnode=gp=gtp->thead;
    while( gp )
        {
        gp->gleft = prevget;
        gp->gright = gp->gnext;
        gp->gup = prevget;
        gp->gdown = gp->gnext;
        prevget = gp;
        gp = gp->gnext;
        }
    return(0);
    }


