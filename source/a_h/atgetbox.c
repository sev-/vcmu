/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:45
*
*   Name            atgetbox.c  --  Place an box entry in que
*
*   Description     Adds an entry for a box into the get table
*
*   Return Value    Returns -1 if error
*
**/

#include <vcstdio.h>

COUNT atgetbox(ur,uc,lr,lc,num,attr)
COUNT ur,uc;        /* Upper left row and column                    */
COUNT lr,lc;        /* Lower right row and column                   */
COUNT num;          /* Window number 1-Double 2-Single 3-Combo      */
COUNT attr;         /* Attribute to use for display                 */
    {
    COUNT xatgetsay();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "atgetbox:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(xatgetsay(NULLTEXT,NULLTEXT,ur,uc,NULLTEXT,attr,lr,lc,num));
    }


