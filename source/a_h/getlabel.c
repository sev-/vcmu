/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:17
*
*   Name            getlabel.c -- Get the Keys name
*
*   Description     Reads the key label structure and returns
*                   label for a key.    
*                   
*   Return Value    Pointer to the label of a key or NULL if
*                   no label is found                
*
**/

#include <vcstdio.h>

TEXT *getlabel(lblptr,key)
struct KEYLBL *lblptr; /* Pointer to structure of labels            */
COUNT key;          /* Key value to find label for                  */
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "getlabel:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    while(lblptr->klblval != -1)
        {
        if(lblptr->klblval == key)
            return(lblptr->klblptr);
        lblptr++;
        }
    return(NULLTEXT);
    }
