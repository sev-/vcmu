/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:29
*
*   Name            vcprokey.c  --  sample key trap function
*
*   Description     This function trap a key and check if it is 
*                   in a list if in the list calls the function
*                   associated with the key
*
*   Return Value    Returns the valued returned by the called
*                   function or the key
*                    
*
**/

#define VCPRO_DEFS
#include <vcstdio.h>

COUNT vcprokey(key)
COUNT key;
    {
    TEXT *ptr;
    VCPROKEY *scnprokey(),*kp;
    COUNT ungetone();
    kp=scnprokey(key);
    if( kp == (VCPROKEY *) 0 )
        return(key);
    if( kp->pro_func != NULLFUNC )
        return((*kp->pro_func)(key,kp->pro_aux));
    else
        {
        ptr = kp->pro_aux;
        if(ptr != NULLTEXT)
            {
            while(*ptr != '\0')
                ungetone(*(ptr++));
            return(9999);
            }
        }
    return(key);
    }

