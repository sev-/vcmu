/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:11
*                
*   Name            ckspterm.c  --  Check for special terminal 
*
*   Description     This function sets up special terminal variable
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID ckspterm(termptr)
struct termctrl *termptr;
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "ckspterm:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    termptr->sp = 0;
    if( (termptr->sp5on != NULLTEXT) ||
        (termptr->sp6on != NULLTEXT) ||
        (termptr->sp7on != NULLTEXT) ||
        (termptr->spcon != NULLTEXT) ||
        (termptr->spdon != NULLTEXT) ||
        (termptr->speon != NULLTEXT) ||
        (termptr->spfon != NULLTEXT) )
        termptr->sp |= 0xf0e0;
    if( (termptr->sp1on != NULLTEXT) ||
        (termptr->sp3on != NULLTEXT) ||
        (termptr->sp6on != NULLTEXT) ||
        (termptr->sp8on != NULLTEXT) ||
        (termptr->spaon != NULLTEXT) ||
        (termptr->spcon != NULLTEXT) ||
        (termptr->spfon != NULLTEXT) )
        termptr->sp |= 0xa54a;
    if( (termptr->sp8on != NULLTEXT) ||
        (termptr->sp9on != NULLTEXT) ||
        (termptr->spaon != NULLTEXT) ||
        (termptr->spbon != NULLTEXT) ||
        (termptr->spcon != NULLTEXT) ||
        (termptr->spdon != NULLTEXT) ||
        (termptr->speon != NULLTEXT) ||
        (termptr->spfon != NULLTEXT) )
        termptr->sp |= 0xff00;
    if( (termptr->sp3on != NULLTEXT) ||
        (termptr->sp4on != NULLTEXT) ||
        (termptr->sp7on != NULLTEXT) ||
        (termptr->spaon != NULLTEXT) ||
        (termptr->spbon != NULLTEXT) ||
        (termptr->speon != NULLTEXT) ||
        (termptr->spfon != NULLTEXT) )
        termptr->sp |= 0xcc98;
    }


