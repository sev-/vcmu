/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:59
*
*   Name            valdate.c  --  check to see if valid date
*
*   Description     Check to see if date in string is valid. returns
*                   1 if invalid and 0 if valid
*
*   Return Value    Returns 1 if invalid or 0 if valid
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

#ifdef USESHORT
#define SCANVALUE "%hd"
#else
#define SCANVALUE "%d"
#endif

COUNT valdate(str) 
TEXT str[];
    {
    COUNT yr,mo,da;
    TEXT stryr[5];
    COUNT strcmp();
    VOID bell();
    COUNT leapyear();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "valdate:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    yr=mo=da=0;
    if(!hasdata(str,DATEEDIT))
        return(0);             /* Blank date is valid */
#ifdef YEARFIRST
    sscanf(str,DATESCAN,&yr,&mo,&da);
#endif
#ifdef DAYFIRST
    sscanf(str,DATESCAN,&da,&mo,&yr);
#endif
#ifdef MONTHFIRST
    sscanf(str,DATESCAN,&mo,&da,&yr);
#endif
    if(yr<100)
        yr += 1900; /* if year = 82, 082, or 0082 assume 1982  */
    if(yr<1000)
        yr += 2000; /* if year given as 182, assume 2182 */
    if(mo<1 || mo>12)
        {
        bell();
        return(1); /* NOT a valid month */
        }
    if(da < 1 || da > 31)
        {
        bell();
        return(4); /* NOT a valid day */
        }
    if( da > 30 && (mo == 9 || mo == 4 || mo == 6 || mo == 11) )
        {
        bell();
        return(4); /* NOT a valid day */
        }
    sprintf(stryr,SCANVALUE,yr);
    if(mo == 2 && da > 28)
        if(!leapyear(stryr) )
            {
            bell();
            return(4);      /* NOT a valid day */
            }
        else 
            if(da > 29)
                {
                bell();
                return(4);  /* Not a valid day */
                }
    return(0);  /* IS a valid year */
    }

