/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:47
*
*   Name            tvccurs.c  --  Terminal cursor
*
*   Description     This program sets the terminal cursor to the
*                   requested status if possible.
*                   
*   Return Value    Return 0 if didn't set cursor
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

VOID tvccurs(code)
PFAST COUNT code;   /* Mode ON :OFF :ON_ALT  :OFF_ALT               */
    {
    VOID dist_str();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "tvccurs:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(code == ON)
        {
        if(bufon || (vccursor <= 2))
            return;
        if(vccursor == 3)
            {
            if(vcterm.co != NULLTEXT)
                dist_str(vcterm.co,0);
            if(vcterm.ve != NULLTEXT)
                dist_str(vcterm.ve,0);
            vccursor = 1;
            }
        else
            {
            if(vcterm.co != NULLTEXT)
                dist_str(vcterm.co,0);
            if(vcterm.vs != NULLTEXT)
                dist_str(vcterm.vs,0);
            vccursor = 2;
            }
        }
    if(code == OFF)
        {
        if(bufon || (vccursor > 2))
            return;
        if(vcterm.cf != NULLTEXT)
            dist_str(vcterm.cf,0);
        vccursor += 2;
        }
    if(code == NORMCURSOR)
        {
        if((vccursor == 1) || (vccursor == 3))
            return;
        if(vccursor <= 2 )
            {
            if(vcterm.ve != NULLTEXT)
                dist_str(vcterm.ve,0);
            vccursor = 1;
            }
        else
            vccursor = 3;
        }
    if(code == ALTCURSOR)
        {
        if((vccursor == 2) || (vccursor == 4))
            return;
        if(vccursor <= 2 )
            {
            if(vcterm.vs != NULLTEXT)
                dist_str(vcterm.vs,0);
            vccursor = 2;
            }
        else
            vccursor = 4;
        }
    return;
    }

#endif  


   
