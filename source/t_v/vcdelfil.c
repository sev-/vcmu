/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:20
*
*   Name            vcdelfil.c  --  delete a disk file
*
*   Description     This function deletes a file
*
*   Return Value    Returns -1 if error
*                    
*
**/

#include <vcstdio.h>

COUNT vcdelfil(nam)
TEXT *nam;
    {
#ifdef MSC
    COUNT unlink();
    return( unlink(nam) );
#endif
#ifdef UNIX
    int unlink();
    return((COUNT) unlink(nam) );
#endif
#ifdef VMS
    int delete();
    return((COUNT) delete(nam));
#endif
#ifdef PRIMOS
    int delete();
    return((COUNT) delete(nam));
#endif
    }


