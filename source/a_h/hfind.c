/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:40
*
*   Name            hfind.c  --  find keyword in help file
*
*   Description     Looks through index for keyword if found it
*                   position the help file on the keyword and returns
*                   1 if not found returns 0
*
*   Return Value    Returns 1 if found 0 if not found
*
**/

#include <vcstdio.h>

COUNT hfind(keyword)
TEXT *keyword;      /* Pointer to keyword                           */
    {
    FAST TEXT *c;
    FAST COUNT n;
    TEXT *tallcaps();
    COUNT strncmp();
    struct HLP_STR *hp;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "hfind:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    c = tallcaps(keyword);
    hp = hlpndx;
    for(n=1,hp++;(n <= (COUNT)(hlpndx->filloc)) && strncmp(c,hp->keyword,11);
                               n++,hp++);
    if(n > (COUNT)(hlpndx->filloc))
        return(0); /* key word not found */
#ifdef VMS
    fseek(hlpfil,(int)hp->filloc,0);
#else
#ifdef PRIMOS
    fseek(hlpfil,(int)hp->filloc,0);
#else
    fseek(hlpfil,hp->filloc,0);
#endif
#endif
    return(1);  /* key word found. File positioned */
    }


