/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:19
*
*   Name            colormon.c  --  Determine monitor
*
*   Description     This checks your equipment to determine if you
*                   have a monochrome or color monitor.
*
*   Return Value    Returns 0 for monochrome 1 for color
*
**/

#include <vcstdio.h>

COUNT colormon()
        {
#ifdef IBM
    COUNT equip();
    VOID vcpeek(),vcint();
    TEXT type;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "colormon:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
        switch(equip() & 48)
            {
            case 48 :
                return(0);      /* mono monitor                         */
            case 16 :
            case 32 :
                return(1);      /* color monitor                        */
            case 00 :           /* ega card                             */
                vcpeek(0x40,0x87,&type,1);
                if(type & 1)
                    return(-2);
                else
                    return(-1);
            }
        return(0);
#endif
#ifdef TERMONLY
#ifdef VCDEBUG
    vcdebug = (TEXT *) "colormon:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(vcterm.ct == NULLTEXT)
        return(0);
    else
        return(1);
#endif
#ifdef OS2
    VIOCONFIGINFO vioconfiginfo;
    COUNT retval;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "colormon:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    vioconfiginfo.cb = sizeof(vioconfiginfo);
    VioGetConfig(0,&vioconfiginfo,0);
    retval = vioconfiginfo.adapter;
    return(retval);
#endif
    }

#ifdef IBM
COUNT equip()
    {
    VOID vcint();
    struct VCREGS inregs,outregs;
    inregs.ax=0;
    vcint(0x11,&inregs,&outregs);
    return(outregs.ax);
    }
#endif


