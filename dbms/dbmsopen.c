/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:24
*
*   Name            dbmsopen - database create          
*                                   
*   Description     This creates new record in the data base       
*
*   Return Value    Returns pointer to database control structure
*                   or NULL if error
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

DBP dbmsopen(nbr,size,ofset,len,type)
COUNT nbr;
COUNT size;
COUNT ofset;
COUNT len;
COUNT type;
    {
    DBP dbmsxopn();
    return(dbmsxopn(nbr,size,ofset,len,type,3,4));
    }
