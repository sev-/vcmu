/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:13
*
*   Name            clrfld.c  --  clear a area to spaces
*
*   Description     This function clears the an area of length {len}
*                   to spaces starting at the current location
*                   (vcrow,vccol) with the attribute {attrb}
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID clrfld(len,attrb)
COUNT len;          /* Length to clear                              */
COUNT attrb;        /* Attribute to use to clear                    */
    {
    COUNT wputchr();
    VOID wplace_cur();
    VOID vcputc();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "clrfld:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if(wdoctrl->wno_opn && !override)
        {
        cur_switch = FALSE;
        while(len--)
            wputchr(wdoctrl->wcurrent,' ',attrb);
        cur_switch = TRUE;
        wplace_cur(wdoctrl->wcurrent);
        }
    else
#endif
        while(len--)
            vcputc(' ',attrb);
    }


