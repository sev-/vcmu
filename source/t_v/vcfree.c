/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:50
*
*   Name            vcfree.c --  free allocated memory
*
*   Description     Frees allocated memory using free     
*                   
*   Return Value    VOID
*       
**/

#include <vcstdio.h>

VOID vcfree(location,calledby)
TEXT *location;     /* Location of allocated memory to free         */
TEXT *calledby;     /* Program calling this function                */
    {
    TEXT buf[80];
    VOID terror();
    VOID free();
    TEXT *strcpy();
    TEXT *strcat();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcfree:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(location == NULLTEXT)
        {
        strcpy(buf,"Trying to free null from : ");
        if(calledby != NULLTEXT)
            strcat(buf,calledby);
        terror("Trying to free null location");
        }
    free(location);
    }


