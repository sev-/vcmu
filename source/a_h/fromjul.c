/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:06
*
*   Name            fromjul.c  --  Convert from julian date
*
*   Description     This function converts from a julian number
*                   to the form "mm/dd/yy". The return value should
*                   be tested to determine the exact year.  To get
*                   a julian number use tojul().
*
*   Return Value    Returns the century (i.e. the 19 in 1985)       
*
**/

#include <vcstdio.h>

COUNT fromjul(jul,outstr) 
LONG jul;           /* Julian number to convert                     */  
TEXT outstr[];      /* String to place answer                       */  
    {
    LONG yr,mo,da,mtmp;
    COUNT cnt;
    COUNT cent;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "fromjul:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    mtmp = jul - 1721119L;
    yr = (4*mtmp-1)/146097L;
    mtmp = 4*mtmp-1-146097L*yr;
    da = mtmp/4;
    mtmp = (4*da+3)/1461;
    da = 4 * da + 3 - 1461 * mtmp;
    da = (da+4)/4;
    mo = (5*da-3)/153;
    da = 5*da-3-153*mo;
    da = (da+5)/5;
    yr = 100 * yr + mtmp;
    if(mo<10)
        mo += 3;
    else
        {
        mo -= 9;
        yr++;
        }
    cent = (COUNT)yr/100;
    yr = yr - (cent*100);
#ifdef YEARFIRST
    sprintf(outstr,DATEPRINT,(int)yr,(int)mo,(int)da);
#endif
#ifdef DAYFIRST
    sprintf(outstr,DATEPRINT,(int)da,(int)mo,(int)yr);
#endif
#ifdef MONTHFIRST
    sprintf(outstr,DATEPRINT,(int)mo,(int)da,(int)yr);
#endif
    cnt=0;
    while(outstr[cnt])
        {
        if(outstr[cnt]==' ')
            outstr[cnt]='0';
        cnt++;
        }
    return((COUNT)cent);
    }

