/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:25
*
*   Name            gettime.c  --  get system time
*
*   Description     gets the system time and returns it in the
*                   string {tim}. time is in the format
*                   hh:mm:ss.dd
*
*   Return Value    VOID
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

#define SCANVALUE "%2d:%2d:%2d.00"

VOID GETTIME(tim)
TEXT tim[];         /* String to place time                         */
    {
#ifdef UNIX
    LONG sec;
    COUNT n;
    struct tm *ts;
    struct tm *localtime();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "gettime:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    time(&sec);
    ts=localtime(&sec);
    sprintf(tim,SCANVALUE,ts->tm_hour,ts->tm_min,ts->tm_sec);
    n=0;
    while(tim[n])
        {
        if(tim[n]==' ')
            tim[n]='0';
        n++;
        }
#endif 
#ifdef IBM
    struct VCREGS iregs,oregs;
    COUNT n;
    VOID vcint();
    iregs.ax = 0x2c00;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "gettime:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    vcint(0x21,&iregs,&oregs);
    sprintf(tim,"%2d:%2d:%2d.%2d",(oregs.cx & 0xff00) / 0xff,oregs.cx & 0x00ff,
      (oregs.dx & 0xff00) / 0xff,oregs.dx & 0x00ff);
    n=0;
    while(tim[n])
        {
        if(tim[n]==' ')
            tim[n]='0';
        n++;
        }
#endif
#ifdef VMS
    int time_val;
    COUNT n;
    struct tm *ts;
    struct tm *localtime();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "gettime:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    time(&time_val);
    ts=localtime(&time_val);
    sprintf(tim,SCANVALUE,ts->tm_hour,ts->tm_min,ts->tm_sec);
    n=0;
    while(tim[n])
        {
        if(tim[n]==' ')
            tim[n]='0';
        n++;
        }
#endif 
#ifdef PRIMOS
    int time_val;
    COUNT n;
    struct tm *ts;
    struct tm *localtime();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "gettime:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    time(&time_val);
    ts=localtime(&time_val);
    sprintf(tim,SCANVALUE,ts->tm_hour,ts->tm_min,ts->tm_sec);
    n=0;
    while(tim[n])
        {
        if(tim[n]==' ')
            tim[n]='0';
        n++;
        }
#endif 
#ifdef OS2
    DATETIME td;
    COUNT n;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "gettime:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    DosGetDateTime(&td);
    sprintf(tim,"%2d:%2d:%2d.%2d",td.hours,td.minutes,td.seconds,
                                   td.hundredths);
    n=0;
    while(tim[n])
        {
        if(tim[n]==' ')
            tim[n]='0';
        n++;
        }
#endif 
    }
