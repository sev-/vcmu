/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:33
*
*   Name            keycomp - list key compare
*                                   
*   Description     This function compares to buffers
*
*   Return Value    Returns -1 for less, 0 for equal, 1 for greater
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

COUNT keycomp(bp1,bp2,dbkey)
TEXT *bp1;          /* Buffer pointer one                           */
TEXT *bp2;          /* Buffer pointer two                           */
struct DbmsKey *dbkey;  /* Pointer to struct of key segments        */
    {
    struct DbmsKey *curkey; /* Pointer to current key segments      */
    COUNT retval = 1;   /* -1 for less, 0 for equal ,1 for greater  */
    TEXT *ptr1,*ptr2;   /* Temporary pointer for compares           */
    COUNT *cp1,*cp2;    /* Temporary pointer for compares           */
    COUNT cnt;          /* Counting variable                        */
    if((bp1 == NULL) || (bp2 == NULL) || (dbkey == (struct DbmsKey *)0))
        {
        return(-2);
        }
    curkey = dbkey;
    while(curkey != (struct DbmsKey *)0)
        {
        if(curkey->dbkeytype == 1)
            {
            ptr1 = bp1+curkey->dbkeyofst;
            ptr2 = bp2+curkey->dbkeyofst;
            for(cnt=0;cnt < curkey->dbkeylen;cnt++)
                {
                if((*ptr1 != *ptr2) ||
                   (*ptr1 == '\0') || (*ptr2 == '\0'))
                    break;
                ptr1++;
                ptr2++;
                }
            if((cnt < curkey->dbkeylen) && (*ptr1 != *ptr2))
                {
                if(*ptr1 < *ptr2)
                    retval = -1;
                else
                    retval = 1;
                break;
                }
            }
        else
            {
            cp1 = (COUNT *)(bp1+curkey->dbkeyofst);
            cp2 = (COUNT *)(bp2+curkey->dbkeyofst);
            if( *cp1 != *cp2 )
                {
                if( *cp1 < *cp2 )
                    retval = -1;
                else
                    retval = 1;
                break;
                }
            }
        curkey = curkey->dbkeynext;
        }
    if(curkey == (struct DbmsKey *)0)
        retval = 0;
    return(retval);
    }
