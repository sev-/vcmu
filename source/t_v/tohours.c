/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:35
*
*   Name            tohours.c  --  convert days and hours to hours
*
*   Description     Converts time from the format of days and hours
*                   to the format of hours and decimal. the days and
*                   hours could have be gotten by timeadd()
*
*   Return Value    Returns number of hours
*
**/

#include <vcstdio.h>

#ifdef USESHORT
#define SCANVALUE "%hd:%hd:%hd.%hd"
#define SPRTVAL "%hd"
#else
#define SCANVALUE "%d:%d:%d.%d"
#define SPRTVAL "%d"
#endif

COUNT tohours(days,hhmmssxx)
COUNT days;         /* Number of days                               */
TEXT hhmmssxx[];    /* Time in format hh:mm:ss.dd                   */
    {
    COUNT h,m,s,d,n,ret;
    TEXT hr[8],frac[5];
    LONG hundreds;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "tohours:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    h=m=s=d=ret=0;
    sscanf(hhmmssxx,SCANVALUE,&h,&m,&s,&d);
    hundreds  = (m * 60) + s;     /* s = total mins + secs in secs     */
    hundreds  = hundreds * 100;   /* s = secs*100 to ease decimal calc */
    hundreds  = hundreds / 3600;  /* s = 100ths of hour     */
    h = h + (days * 24);
    while(h>9999)
        {
        ret++;
        h -= 10000;
        }
    sprintf(hr,SPRTVAL,h);
    sprintf(frac,"%ld",hundreds);
    sprintf(hhmmssxx,"%4.4s.%2.2s",hr,frac);
    n=0;
    while(hhmmssxx[n])
        {
        if(hhmmssxx[n]==' ')
            hhmmssxx[n]='0';
        n++;
        }
    return(ret);
    }
