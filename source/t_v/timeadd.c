/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:28
*
*   Name            timeadd.c  --  add two times
*
*   Description     returns the sum of t1 and t2. Times should be 
*                   in the format hh:mm:ss.dd. the sum of t1 and
*                   t2 are returned in t1 and the days as a return
*                   value
*
*   Return Value    Returns number of days
*
**/

#include <vcstdio.h>

#ifdef USESHORT
#define SCANVALUE "%hd:%hd:%hd.%hd"
#else
#define SCANVALUE "%d:%d:%d.%d"
#endif

COUNT timeadd(t1,t2)
TEXT t1[];          /* Time one                                     */
TEXT t2[];          /* Time two                                     */
    {
    UCOUNT h1,h2,m1,m2,s1,s2,d1,d2,n;
    COUNT days;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "timeadd:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    h1=h2=m1=m2=s1=s2=d1=d2=days=0;
    sscanf(t1,SCANVALUE,&h1,&m1,&s1,&d1);
    sscanf(t2,SCANVALUE,&h2,&m2,&s2,&d2);
    d1 += d2;
    while(d1>99)
        {
        s1 += 1;
        d1 -= 100;
        }
    s1 += s2;
    while(s1>59)
        {
        m1 += 1;
        s1 -= 60;
        }
    m1 += m2;
    while(m1>59)
        {
        h1 += 1;
        m1 -= 60;
        }
    h1 += h2;
    days = h1 / 24;
    h1 = h1 % 24;
    sprintf(t1,SCANVALUE,h1,m1,s1,d1);
    n=0;
    while(t1[n])
        {
        if(t1[n]==' ')
            t1[n]='0';
        n++;
        }
    return(days);
    }

