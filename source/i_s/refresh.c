/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:42
*
*   Name            refresh.c  --  refresh window screen
*
*   Description     Writes the whole screen back from the memory
*                   screen.
*
*   Return Value    Returns -1 if error
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef TERMINAL

COUNT refresh()
    {
    FAST COUNT rowcnt=0;
    COUNT twidth;
    FAST TEXT *sptr;
    TEXT *temp_scrn,*vcalloc();
    VOID vcmem();
    VOID xerase();
    VOID at();
    VOID vca_put();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "refresh:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    temp_scrn = wscreen;
    override = TRUE;
#else
    if( (temp_scrn = vcalloc((UCOUNT) (vcterm.rows*vcterm.cols) << 1,
                       (UCOUNT) sizeof(TEXT),vcdebug)) == NULLTEXT)
        {
        vcerror = TSCRMEM;
        return(-1);
        }
#endif
    vcmem(temp_scrn,tscreen,(UCOUNT)(vcterm.rows*vcterm.cols) << 1);
    xerase(normattr);
    sptr = temp_scrn;
    twidth = vcterm.cols << 1;
    while(rowcnt < vcterm.rows)
        {
        vca_put(rowcnt,0,sptr,vcterm.cols);
        sptr += twidth;
        rowcnt++;
        }
#ifdef WINDOW
    override = FALSE;
#else
    vcfree(temp_scrn,vcdebug);
#endif
    at(vcrow,vccol);
    return(0);
    }

#endif
