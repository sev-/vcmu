/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:09
*
*   Name            chkspattr -- Check if special attr
*
*   Description     Checks attr to see if attribute requires a
*                   space.     
*
*   Return Value    Returns 0 if not special
*
**/

#include <vcstdio.h>

COUNT ckspattr(attr)
COUNT attr;         /* Attribute to check if special                */
    {
    UCOUNT attr2bit();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "ckspattr:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef NOUNSIGNED
    if(attr < 0)
        attr += 256;
#endif
    return(attr2bit(attr) & vcterm.sp);
    }

UCOUNT attr2bit(attr)
COUNT attr;
    {
    UCOUNT retval=0;
    switch(attr)
        {
        case 1:
            retval = BIT1;
            break;
        case 7:
            retval = BIT2;
            break;
        case 9:
            retval = BIT3;
            break;
        case 15:
            retval = BIT4;
            break;
        case 112:
            retval = BIT5;
            break;
        case 113:
            retval = BIT6;
            break;
        case 120:
            retval = BIT7;
            break;
        case 129:
            retval = BIT8;
            break;
        case 135:
            retval = BIT9;
            break;
        case 137:
            retval = BIT10;
            break;
        case 143:
            retval = BIT11;
            break;
        case 240:
            retval = BIT12;
            break;
        case 241:
            retval = BIT13;
            break;
        case 248:
            retval = BIT14;
            break;
        case 249:
            retval = (UCOUNT) 32768l;
            break;
        }
    return(retval);
    }

