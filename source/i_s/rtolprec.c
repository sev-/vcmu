/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:46
*
*   Name            rtolprec.c - precision check
*                                   
*   Description     Calculates decimal precision for a field
*
*   Return Value    Returns decimal precision
*                                   
**/

#include <vcstdio.h>

COUNT rtolprec(fld)
TEXT *fld;                  /* Field to check                       */
    {                       /* ------------------------------------ */
    COUNT retval = 0;       /* Return precision                     */
    COUNT evalpic();        /* Declare functions used               */
    while((*fld != '\0') && (*fld != vcdecimal))
        fld++;
    if(*fld == vcdecimal)
        {
        fld++;
        while((*fld != '\0') && evalpic(*fld))
            {
            fld++;
            retval++;
            }
        }
    return(retval);
    }
