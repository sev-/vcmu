/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:41
*
*   Name            hload.c  --  Load help index into memory
*
*   Description     Loads the help file index into memory and returns
*                   the number of keywords loaded
*
*   Return Value    Returns number of keywords loaded
*
**/

#include <vcstdio.h>

COUNT hload(fp)
FILE *fp;           /* Pointer to help file index                   */
    {
    FAST COUNT n;
    struct HLP_STR *tmp;
    TEXT *vcalloc();
    VOID vcfree();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "hload:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    tmp = (struct HLP_STR *)vcalloc(1,sizeof(*tmp),vcdebug);
    fread(tmp,sizeof(*tmp),1,fp);
    n = (COUNT) tmp->filloc;
    hlpndx = (struct HLP_STR *)vcalloc(n+1,sizeof(*tmp),vcdebug);
#ifdef VMS
    fseek(fp,0,0);
#else
#ifdef PRIMOS
    fseek(fp,0,0);
#else
    fseek(fp,0l,0);
#endif
#endif
    n = fread(hlpndx,sizeof(*tmp),n+1,fp) - 1;
    vcfree(tmp,vcdebug);
    return(n); 
    }


