/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:03
*
*   Name            wclrfld.c  --  clear a area to spaces
*
*   Description     This function clears the an area of length {len}
*                   to spaces starting at the current location
*                   (vcrow,vccol) with the attribute {attrb}
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID wclrfld(wptr,len,attrb)
WPTR wptr;          /* Pointer to window to clear                   */
COUNT len;          /* Length to clear                              */
COUNT attrb;        /* Attribute to use to clear                    */
    {
    COUNT wputchr();
    VOID wplace_cur();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wclrfld:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    cur_switch = FALSE;
    while(len--)
        wpuvchr(wptr,' ',attrb);
    cur_switch = TRUE;
    wplace_cur(wdoctrl->wcurrent);
#endif
    }


