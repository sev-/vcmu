/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:14
*
*   Name            xatsay.c  --  At location display string w/attribute
*
*   synopsis        xatsay(row,col,str,attr);
*                   COUNT row,col;   location to display string
*                   TEXT *str;     string to display
*                   COUNT attr;      attribute to display with
*
*   Description     This function displays a NULL terminated string
*                   at location row,col using attribute attr.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID xatsay(row,col,str,attr)
COUNT row,col;  /* Row and column to display string                 */
PFAST TEXT *str;/* String to display                                */
PFAST COUNT attr;/* Attribute to use                                */
    {
    VOID wxatsay();
    VOID at();
    COUNT ckspattr();
    VOID vcputc();
    VOID vcputs();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xatsay:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( attr == -1 )
#ifdef WINDOW
        if(wdoctrl->wno_opn && !override)
            attr=wdoctrl->wcurrent->say_at;
        else
#endif
            attr=attrsay;
#ifdef WINDOW
    if(wdoctrl->wno_opn && !override)
        {
        wxatsay(wdoctrl->wcurrent,row,col,str,attr);
        return;
        }
#endif
    if(vcterm.mc)
        {
        if(col == 0)
            {
            at(row,col);
            if(ckspattr(attr))
                {
                str++;
                vcputc((TEXT)AT_ON,attr);
                }
            }
        else
            {
            col--;
            at(row,col);
            vcputc((TEXT)AT_ON,attr);
            }
        }
    else
        at(row,col);
    vcputs(str,attr);
    if(vcterm.mc)
        vcputc((TEXT) AT_OFF,attr);
    }


