/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:17
*
*   Name            menunew.c  --  create new menu
*
*   Description     This function creates a menu having the 
*                   characteristics of previously defined menu 
*                   style
*
*   Return Value    Returns NULL if error or returns menu pointer
*                   if no error
*                    
*
**/

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

VCMENU *menunew(row,col,mnunam,hlpkey,style)
COUNT row,col;      /* Top row and column for menu                  */
TEXT *mnunam;       /* Title for menu                               */
TEXT *hlpkey;       /* Pointer to help for menu                     */
TEXT *style;        /* Pointer to name of style sheet               */
    {
    VCMENU *menuxnew();
    MENUSTYLE *styleptr,*getmstyle();
    if( (styleptr = getmstyle(style)) != (MENUSTYLE *)0 )
        {
        if( styleptr->smagic != MSTYLEMAGIC )
            return((VCMENU *)0);
        return( menuxnew(row,col,styleptr->swidth,mnunam,
                      styleptr->mnustyle,styleptr->snormattr,
                      styleptr->sbarattr,styleptr->sunavattr,
                      styleptr->sbordattr,styleptr->spermlvl,
                      hlpkey) );
        }
    else
        {
        return((VCMENU *)0);
        }
    }



