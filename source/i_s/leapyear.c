/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:02
*
*   Name            leapyear.c  --  is leapyear ?
*
*   Description     Determines whether a year is a leap year or not
*
*   Return Value    Returns 1 if leapyear
*
**/

#include <vcstdio.h>

#ifdef USESHORT
#define SCANVALUE "%hd"
#else
#define SCANVALUE "%d"
#endif

COUNT leapyear(str)
TEXT str[];         /* Year in form "yy" or "yyyy"                  */
    {
    COUNT yr,lyr;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "leapyear:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    lyr=0;
    yr=0;
    sscanf(str,SCANVALUE,&yr);
    if(yr<100)
        yr += 1900; /* if year = 82, 082, or 0082 assume 1982  */
    if(yr<1000)
        yr += 2000; /* if year given as 182, assume 2182 */
    if(yr == (4*(yr/4)))
        lyr = 1;
    if(yr == (100*(yr/100)) )
        lyr = 0;
    if(yr == (400*(yr/400)) )
        lyr = 1;
    return(lyr);
    }

