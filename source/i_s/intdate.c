/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:50
*
*   Name            intdate.c  --  convert date to integers
*
*   Description     Takes a date in the format DATESCAN and
*                   sets three integers to the values of month
*                   day and year.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID intdate(str,mo,da,yr)
TEXT str[];         /* Date in format DATESCAN                      */
COUNT *mo;          /* Pointer to integer for month                 */
COUNT *da;          /* Pointer to integer for day                   */
COUNT *yr;          /* Pointer to integer for year                  */
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "intdate:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    sscanf(str,DATESCAN,mo,da,yr);
    }

