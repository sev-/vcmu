/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:10
*
*   Name            setspattr.c  --  Sets special attribute 
*
*   Description     This program turns off a specified attribute
*                   
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

VOID setspattr(attr,flag)
COUNT attr;         /* Attribute to set                             */
COUNT flag;         /* Set attribute ON or OFF                      */
    {
    UCOUNT attr2bit(),val;
    TEXT **tp;
    VOID dist_str();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "setspattr:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(flag)
        tp = &vcterm.sp0on;
    else
        tp = &vcterm.sp0off;
    val = attr2bit(attr) >> 1;
    while(val)
        {
        val = val >> 1;
        tp++;
        }
    dist_str(*tp,0);
    sp_attr = 0;
    }
#endif


