/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:04
*
*   Name            wprep.c  --  Prepare all window variables
*
*   Description     This function prepares all the window variables
*                   allocates memory to save the screen. Opens the 
*                   cut and paste window if necessary.
*
*   Return Value    Returns pointer to wscreen
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

WPTR wprep()
    {
    TEXT *vcalloc();
    VOID wscrn_blank();
    VOID vcmem();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wprep:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if( (wdoctrl = (struct WDOCTRL *) vcalloc( 1,sizeof(*wdoctrl),
                                   vcdebug)) == (struct WDOCTRL *) 0)
        {
        vcerror = WCTRLMEM;
        return((WPTR) 0);
        }
    wdoctrl->wstdctrl = ACTIVE+BORDER+CURSOR;
    wdoctrl->wcookfunc = NULLFUNC;
    wdoctrl->wretlf = 1;
    wdoctrl->wbgdisplay = TRUE;
    if( (wscreen = vcalloc((UCOUNT) (vcterm.rows*vcterm.cols) << 1,
                      (UCOUNT) sizeof(TEXT),vcdebug)) == NULLTEXT)
        {
        vcerror = SCRMEM;
        return((WPTR) 0);
        }
    wscrn_blank();
#endif
#ifdef TERMINAL
    if( (tscreen = vcalloc((UCOUNT) (vcterm.rows*vcterm.cols) << 1,
                       (UCOUNT) sizeof(TEXT),vcdebug)) == NULLTEXT)
        {
        vcerror = TSCRMEM;
        return((WPTR) 0);
        }
#ifdef WINDOW
    vcmem(tscreen,wscreen,(vcterm.rows*vcterm.cols) << 1);
#else
    eraterm(normattr);
#endif
#endif
#ifdef CUTPASTE
    return(wsetup(NULLTEXT,0,0,0,vcterm.rows-1,vcterm.cols-1,32,normattr,
                        0,attrsay,attrag,attrnag,0,NULLTEXT,0,0));
#endif
    return((WPTR) wscreen);
    }

