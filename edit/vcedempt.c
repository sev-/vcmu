/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:30
*
*   Name            vcedempt.c - editor empty
*                                   
*   Description     Emptys a work buffer to all NULLS
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedempty(str,len)
TEXT *str;                  /* String to empty                      */
COUNT len;                  /* Length of string                     */
    {                       /* ------------------------------------ */
    while(len--)                        /* While more               */
        *(str++) = '\0';                /* Blank string             */
    return(0);                          /* Return O.K.              */
    }                                   /* ------------------------ */    


