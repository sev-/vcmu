/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:12
*
*   Name            getdate.c  --  get system date
*
*   Description     gets the system date and returns it in the
*                   string {dat} in the format DATESCAN ("mm/dd/yy" 
*                   default) and returns the century
*
*   Return Value    Returns century 
*
**/

#include <vcstdio.h>

#ifdef UNIX
#include <time.h>
#include <sys/types.h>
#endif

#ifdef VMS
#include <time.h>
#endif

#ifdef PRIMOS
#include <time.h>
#endif

COUNT GETDATE(dat)
TEXT dat[];         /* String to place date                         */
    {
#ifdef UNIX
    LONG sec;
    COUNT n;
    COUNT century = 19; 
    struct tm *ts;
    struct tm *localtime();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "getdate:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    time(&sec);
    ts=localtime(&sec);
#ifdef YEARFIRST
    sprintf(dat,DATEPRINT,ts->tm_year,ts->tm_mon+1,ts->tm_mday);
#endif
#ifdef DAYFIRST
    sprintf(dat,DATEPRINT,ts->tm_mday,ts->tm_mon+1,ts->tm_year);
#endif
#ifdef MONTHFIRST
    sprintf(dat,DATEPRINT,ts->tm_mon+1,ts->tm_mday,ts->tm_year);
#endif
    n=0;
    while(dat[n])
        {
        if(dat[n]==' ')
            dat[n]='0';
        n++;
        }
    if(ts->tm_year < 80)
        century = 20;
    return(century);
#endif 
#ifdef IBM
    struct VCREGS iregs,oregs;
    COUNT n,century,year;
    VOID vcint();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "getdate:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    iregs.ax = 0x2a00;
    vcint(0x21,&iregs,&oregs);
    century = oregs.cx/100;
    year = oregs.cx - (century*100);
#ifdef YEARFIRST
    sprintf(dat,DATEPRINT,year,(oregs.dx & 0xff00) / 0xff,oregs.dx & 0x00ff);
#endif
#ifdef DAYFIRST
    sprintf(dat,DATEPRINT,oregs.dx & 0x00ff,(oregs.dx & 0xff00) / 0xff,
                                                           year);
#endif
#ifdef MONTHFIRST
    sprintf(dat,DATEPRINT,(oregs.dx & 0xff00) / 0xff,oregs.dx & 0x00ff,
                                                           year);
#endif
    n=0;
    while(dat[n])
        {
        if(dat[n]==' ')
            dat[n]='0';
        n++;
        }
    return(century);
#endif
#ifdef VMS
    struct tm *ts;
    int time_val;
    COUNT n;
    COUNT century = 19;
    time(&time_val);
    ts = localtime(&time_val);
#ifdef YEARFIRST
    sprintf(dat,DATEPRINT,ts->tm_year,ts->tm_mon+1,ts->tm_mday);
#endif
#ifdef DAYFIRST
    sprintf(dat,DATEPRINT,ts->tm_mday,ts->tm_mon+1,ts->tm_year);
#endif
#ifdef MONTHFIRST
    sprintf(dat,DATEPRINT,ts->tm_mon+1,ts->tm_mday,ts->tm_year);
#endif
    n=0;
    while(dat[n])
        {
        if(dat[n]==' ')
            dat[n]='0';
        n++;
        }
    if(ts->tm_year < 80)
        century = 20;
    return(century);
#endif 
#ifdef PRIMOS
    struct tm *ts,*localtime();
    int time_val;
    COUNT n;
    COUNT century = 19;
    time(&time_val);
    ts = localtime(&time_val);
#ifdef YEARFIRST
    sprintf(dat,DATEPRINT,ts->tm_year,ts->tm_mon+1,ts->tm_mday);
#endif
#ifdef DAYFIRST
    sprintf(dat,DATEPRINT,ts->tm_mday,ts->tm_mon+1,ts->tm_year);
#endif
#ifdef MONTHFIRST
    sprintf(dat,DATEPRINT,ts->tm_mon+1,ts->tm_mday,ts->tm_year);
#endif
    n=0;
    while(dat[n])
        {
        if(dat[n]==' ')
            dat[n]='0';
        n++;
        }
    if(ts->tm_year < 80)
        century = 20;
    return(century);
#endif 
#ifdef OS2
    DATETIME td;
    COUNT century;
    COUNT year;
    COUNT n;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "getdate:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    DosGetDateTime(&td);
    year = td.year % 100;
    century = td.year - year;
#ifdef YEARFIRST
    sprintf(dat,DATEPRINT,year,td.month,td.day);
#endif
#ifdef DAYFIRST
    sprintf(dat,DATEPRINT,td.day,td.month,year);
#endif
#ifdef MONTHFIRST
    sprintf(dat,DATEPRINT,td.month,td.day,year);
#endif
    n=0;
    while(dat[n])
        {
        if(dat[n]==' ')
            dat[n]='0';
        n++;
        }
    return(century);
#endif 
    }

