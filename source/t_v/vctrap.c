/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:04
*
*   Name            vctrap.c --  Sample keytrap function
*
*   Description     Sample keytrap function used a default if
*                   not overriden    
*                   
*   Return Value    Returns 9999 to eat key or key value
*
**/

#include <vcstdio.h>

static COUNT inhelp=FALSE;
static COUNT inwadj=FALSE;

COUNT vctrap(input)
PFAST COUNT input;
    {
    FAST COUNT oldrow,oldcol;
    VOID at();
    COUNT wadjust();
    VOID wplace_cur();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vctrap:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( hlptxt && helpfunc && !inhelp && (input == spkey.hkey) )
        {
        oldrow=vcrow;
        oldcol=vccol;
        inhelp = TRUE;
        (*helpfunc)();    /* call help function    */
        inhelp = FALSE;
        at(oldrow,oldcol);
        input = 9999;
        }
#ifdef WINDOW
    if( wdoctrl->wno_opn && !inwadj && (input == spkey.wakey) )
        {
        inwadj = TRUE;
        wadjust(wdoctrl->wcurrent);  /* go adjust window   */
        wplace_cur(wdoctrl->wcurrent);
        inwadj = FALSE;
        input = 9999;
        }
#endif
    return(input);
    }


