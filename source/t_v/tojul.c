/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:37
*
*   Name            tojul.c  --  to julian number
*
*   Description     Converts a date to a julian date
*
*   Return Value    Return julian number for day
*
**/

#include <vcstdio.h>

LONG tojul(sdat)
TEXT sdat[];
    {
    LONG yr,mo,da,ctmp,dtmp,mtmp,ytmp;
    LONG result1,result2,result3;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "tojul:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    yr=mo=da=0;
#ifdef YEARFIRST
    sscanf(sdat,DATESCAN,&yr,&mo,&da);
#endif
#ifdef DAYFIRST
    sscanf(sdat,DATESCAN,&da,&mo,yr);
#endif
#ifdef MONTHFIRST
    sscanf(sdat,DATESCAN,&mo,&da,&yr);
#endif
    if(yr<100)
        yr += 1900; /* if year = 82, 082, or 0082 assume 1982  */
    if(yr<1000)
        yr += 2000; /* if year given as 182, assume 2182 */
    if(mo>2)
        {
        mtmp=mo-3;
        ytmp=yr;
        }
    else
        {
        mtmp=mo+9;
        ytmp=yr-1;
        }
    ctmp = (ytmp/100);
    dtmp=ytmp-(100*ctmp);
    result1 = 146097L*ctmp/4;
    result2 = (1461*dtmp)/4;
    result3 = (153*mtmp+2)/5;
    return( (long) result1 + da + result2 + 1721119L + result3 );
    }

