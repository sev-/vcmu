/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:01
*
*   Name            setattr.c  --  Set global attributes
*
*   Description     This changes the global variables that control
*                   default attributes when windows are not being
*                   used. The defines for the attributes are in the
*                   header file. if incorrect mode is given a -1
*                   is returned.
*
*   Return Value    Returns oldattr or -1 if error
*
**/

#include <vcstdio.h>

COUNT setattr(mode,attr)
COUNT mode;         /* Which attribute to change                    */
COUNT attr;         /* New attribute                                */
    {
    FAST COUNT oldattr;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "setattr:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    switch(mode)
        {
        case AGET:
#ifdef WINDOW
            if(wdoctrl->wno_opn && !override)
                {
                oldattr=wdoctrl->wcurrent->get_at;
                wdoctrl->wcurrent->get_at = attr;
                }
            else
                {
#endif
                oldattr=attrag;
                attrag=attr;
#ifdef WINDOW
                }
#endif
            break;
        case NAGET:
#ifdef WINDOW
            if(wdoctrl->wno_opn && !override)
                {
                oldattr=wdoctrl->wcurrent->nget_at;
                wdoctrl->wcurrent->nget_at = attr;
                }
            else
                {
#endif
                oldattr=attrnag;
                attrnag=attr;
#ifdef WINDOW
                }
#endif
            break;
        case SAY:
#ifdef WINDOW
            if(wdoctrl->wno_opn && !override)
                {
                oldattr=wdoctrl->wcurrent->say_at;
                wdoctrl->wcurrent->say_at = attr;
                }
            else
                {
#endif
                oldattr=attrsay;
                attrsay=attr;
#ifdef WINDOW
                }
#endif
            break;
        default:
            oldattr=(-1);
        }
    return(oldattr);
    }


