/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:53
*
*   Name            vcgetenv.c  --  get env variable
*
*   Description     This function gets the system variable
*
*   Return Value    Returns NULLTEXT if error
*
**/

#include <vcstdio.h>

#ifdef TERMCAP

TEXT *vcgetenv(buf)
TEXT *buf;          /* Name of Logical variable to find             */
    {
#ifdef PRIMOS
    TEXT tbuf[160];
    TEXT *gvget();
    strcpy(tbuf,".");
    strcat(tbuf,buf);
    return(gvget(tbuf));
#else
    TEXT *getenv();
    return(getenv(buf));
#endif
    }

#endif
