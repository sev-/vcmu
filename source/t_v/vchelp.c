/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:07
*
*   Name            vchelp.c  --  get help 
*
*   Description     look for help for selected field if found
*                   open window and display pausing between each 
*                   page. when finished close window. This is the
*                   high level help program that calls the others
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID vchelp()
    {
    WPTR hlpwdo;
    COUNT key;
    WPTR wxxopen();
    VOID wrd_scrn();
    COUNT hfind();
    VOID hprint();
    VOID atsay();
    COUNT getone();
    COUNT wclose();
    COUNT wshow();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vchelp:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(hlphk1 != NULLFUNC)
        if((*hlphk1)())
            return;
    if(!wdoctrl->wno_opn) /* if no windows are open read the screen       */
        wrd_scrn();
    if( (hlpwdo = wxxopen(hlptrow,hlptcol,hlpbrow,hlpbcol,hlptitle,
                    hlpctrl,hlpdepth,hlpwidth,hlpcolor,' ')) == (WPTR) 0)
        terror("Error opening help window");
    if(hfind(hlptxt))
        hprint(hlpwdo);
    else
        {
        atsay(0,1,"No Help Found.   End...");
        wshow(hlpwdo);
        while(TRUE)
            {
            key = getone();
            if(hlphk2 != NULLFUNC)
                key = (*hlphk2)(key);
            if(key == spkey.xhkey)
                break;
            }
        }
    hlptrow = hlpwdo->upper_r;
    hlptcol = hlpwdo->upper_c;
    hlpbrow = hlpwdo->lower_r;
    hlpbcol = hlpwdo->lower_c;
    wclose(hlpwdo);                     /* close window, restore screen */
    }

