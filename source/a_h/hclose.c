/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:37
*
*   Name            hclose.c  --  close help file
*
*   Description     closes the help file and returns either a zero
*                   if hlpfil not open or the return of fclose()
*
*   Return Value    Returns 0 or fclose(hlpfil)
*
**/

#include <vcstdio.h>

COUNT hclose()
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "hclose:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(hlpfil)
        return(fclose(hlpfil));
    if(hlpndx != (struct HLP_STR *)0)
        {
        vcfree(hlpndx,vcdebug);
        hlpndx = (struct HLP_STR *)0;
        }
    return(0);
    }


