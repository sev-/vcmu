/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 9/2/90 at 14:29:17
*
*   Name            vcend.c  --  End Vitamin C
*
*   Description     If {restore} = 1 this function closes any open windows.
*                   It also makes sure that the cursor is on the screen 
*                   when finished
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID vcend(restore)
COUNT restore;      /* Close open windows = 1                       */
    {
#ifdef WINDOW
    FAST WPTR wp;
#endif
#ifdef TERMINAL
    COUNT flow = FALSE;
#endif
    COUNT wclose();
    VOID vccurs();
    VOID vcaddrc();
    VOID flipattr();
    VOID sendpstr();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcend:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
#ifdef TERMINAL
    if(vctio == 5)
        flow = vcpee();
#endif
    if(restore == 1)
        {
        wp = wdoctrl->wdtail;
        while(wp != (WPTR) 0)
            {
            wclose(wp);
            wp = wdoctrl->wdtail;
            }
        }
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
#endif
    vccurs(ON);
    vccurs(NORMCURSOR);
    vcaddrc(vcterm.rows-1,0);
#ifdef TERMINAL
    if(vctio == 5)
        flipattr(normattr);
    if(vcterm.es != NULLTEXT)
        sendpstr(vcterm.es);
    if((vcterm.ge != NULLTEXT) && graphattr)    /* If graphics on   */
        dist_str(vcterm.ge,0);          /* Turn graphics off        */
#endif
#ifdef TERMONLY
    set_normal();
#endif
    }
