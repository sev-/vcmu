/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:43
*
*   Name            hlpsort.c  --  sort help keywords
*
*   Description     Sorts the keywords in the HLP_STR
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID hlpsort(hstru,siz)
struct HLP_STR *hstru; /* Pointer to help structure                 */
COUNT siz;          /* Number of keywords                           */
    {
    FAST COUNT n,x;
    TEXT tmpword[40],*strcpy();
    LONG tmploc;
    COUNT strcmp();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "hlpsort:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    for(n=1;n<=siz;n++)
        {
        for(x=n;x<=siz;x++)
            {
            if(strcmp(hstru[x].keyword,hstru[n].keyword)<0)
                {
                strcpy(tmpword,hstru[n].keyword);
                tmploc = hstru[n].filloc;
                strcpy(hstru[n].keyword,hstru[x].keyword);
                hstru[n].filloc = hstru[x].filloc;
                strcpy(hstru[x].keyword,tmpword);
                hstru[x].filloc = tmploc;
                }
            }
        }
    }


