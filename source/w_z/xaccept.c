/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:06
*
*   Name            xaccept.c  --  Accept an entry into a string
*
*   Description     This function accepts an input into str using
*                   pic. Input is done immediately and the function
*                   returns the key press that caused the function
*                   to exit.
*
*   Return Value    Returns the key pressed that caused the exit
*                    
*
**/

#define VCERROR_DEFS
#define VCGET_DEFS

#include <vcstdio.h>

COUNT xaccept(str,pic,tblval)
TEXT str[];         /* String to accept entry into                  */
TEXT pic[];         /* Picture used during input                    */
COUNT tblval;       /* Table Control value                          */
    {
    COUNT ret;
    COUNT row,col;
    GETTABLE *table;
    COUNT clrtbl();
    GETTABLE *tblalloc();
    COUNT xreadgets();
    COUNT xxatget();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xaccept:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(wdoctrl->wno_opn && !override)
        {
        row = wdoctrl->wcurrent->r_pos;
        col = wdoctrl->wcurrent->c_pos;
        }
    else
        {
        row = vcrow;
        col = vccol;
        }
    table = tblalloc(vcdebug,tblval,NULLFUNC);
    xxatget(table,(WPTR) 0,row,col,str,pic,NULLFUNC,NULLTEXT,NULLTEXT,-1,-1);
    ret = xreadgets(table);
    clrtbl(table);
    return(ret);
    }
