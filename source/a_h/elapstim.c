/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:43
*
*   Name            elapstim.c  --  Subtract two times
*
*   Description     Returns the difference between starting time
*                   and ending time. Times should be in the format
*                   hh:mm:ss.dd
*
*   Return Value    Returns difference between to times
*
**/

#include <vcstdio.h>

#ifdef USESHORT
#define SCANVALUE "%hd:%hd:%hd.%hd"
#define SVALUE "%2hd:%2hd:%2hd.%2hd"
#else
#define SCANVALUE "%d:%d:%d.%d"
#define SVALUE "%2d:%2d:%2d.%2d"
#endif

COUNT elapstim(start,end)
TEXT start[];       /* Starting time                                */
TEXT end[];         /* Ending time                                  */
    {
    COUNT h1,h2,m1,m2,s1,s2,d1,d2;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "elapstim:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    h1=h2=m1=m2=s1=s2=d1=d2=0;
    sscanf(end,SCANVALUE,&h1,&m1,&s1,&d1);
    sscanf(start,SCANVALUE,&h2,&m2,&s2,&d2);
    if(h1>23 || m1>59 || s1>59 || d1>99)
        return(-2);   /* end time not valid   */
    if(h2>23 || m2>59 || s2>59 || d2>99)
        return(-1);   /* start time not valid */
    if(d1<d2)
        {
        s1 -= 1;
        d1 += 100;
        }
    d1 -= d2;
    if(s1<s2)
        {
        m1 -= 1;
        s1 += 60;
        }
    s1 -= s2;
    if(m1<m2)
        {
        h1 -= 1;
        m1 += 60;
        }
    m1 -= m2;
    if(h1<h2)
        h1 += 24;
    h1 -= h2;
    sprintf(start,SVALUE,h1,m1,s1,d1);
    d2=0;
    while(start[d2])
        {
        if(start[d2]==' ')
            start[d2]='0';
        d2++;
        }
     return(0);
     } 

