/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:33
*
*   Name            std2cord - Standard to coordinate     
*                                   
*   Description     Convert from screen standard coordinates             
*
*   Return Value    Returns adjusted coordinate
*                                   
**/                                 

#include <vcstdio.h>

COUNT std2cord(cord)
COUNT cord;         /* Value to check                               */
    {
    COUNT retval;
    if(cord < 5000)
        return(cord);
    if(cord <= 6000)
        {
        retval = cord - 6000;
        retval += vcterm.rows-1;
        }
    else
        {
        retval = cord - 7000;
        retval += vcterm.cols-1;
        }
    return(retval);
    }

