/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:25
*
*   Name            dayofwk.c  --  Day of Week
*
*   Description     Send a properly formated date and this returns
*                   a number for the day of week. Used with day_name()
*                   you could display the current day.
*
*   Return Value    Returns day of week
*
**/

#include <vcstdio.h>

COUNT dayofwk(str)
TEXT str[];         /* String in format DATESCAN                  */
    {
    COUNT yr,mo,da,ctmp,dtmp,mtmp,ytmp,n;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "dayofwk:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    yr=mo=da=0;
    sscanf(str,DATESCAN,&mo,&da,&yr);
    if(yr<100)
        yr += 1900; /* if year = 82, 082, or 0082 assume 1982  */
    if(yr<1000)
        yr += 2000; /* if year given as 182, assume 2182 */
    if(mo>2)
        {
        mtmp=mo-2;
        ytmp=yr;
        }
    else
        {
        mtmp=mo+10;
        ytmp=yr-1;
        }
    ctmp = ytmp/100;
    dtmp = ytmp-100*ctmp;
    n = ((13*mtmp-1)/5)+da+dtmp+(dtmp/4)+(ctmp/4)-ctmp-ctmp+77;
    return(n-7*(n/7));
    }

