/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:45
*
*   Name            inpchkto.c - input check toggle
*                                   
*   Description     Turns on or toggles check value for field
*
*   Return Value    VOID
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

VOID inpchktog(gp,flag)
GETITEM *gp;
COUNT flag;
    {
    switch(flag)
        {
        case ON:
            *gp->gtmpfld = '1';
            break;
        case OFF:
            *gp->gtmpfld = '0';
            break;
        case TOGGLE:
            if(*gp->gtmpfld == '1')
                 *gp->gtmpfld = '0';
             else
                 *gp->gtmpfld = '1';
            break;
        }
    }


