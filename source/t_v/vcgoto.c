/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:05
*
*   Name            vcgoto.c  --  terminal at
*
*   Description     This function uses the precompiled information
*                   to give the cursor addressing string.
*
*   Return Value    Returns -1 if error
*
**/

#include <vcstdio.h>

#ifdef TERMCAP

TEXT *vcgoto(pc,col,row)
struct PRECOMP *pc;
COUNT col,row;
    {             
    COUNT trash;
    TEXT str[8];
    TEXT *strcpy();
    COUNT itoap();
    TEXT *strcat();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcgoto:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(pc->col_first)
        {
        trash = row;
        row = col;
        col = trash;
        }
    row += pc->rofset;
    col += pc->cofset;
    retbuf[0] = '\0';
    if(pc->before != NULLTEXT)
        strcpy(retbuf,pc->before);
    switch(pc->rformat)
        {
        case 1 :
        case 2 :
        case 3 :
            itoap(row,str,pc->rformat);
            strcat(retbuf,str);
            break;
        case 4 :
            if(row)
                str[0] = (TEXT) row;
            else
                str[0] = (TEXT) AT_ON;
            str[1] = '\0';
            strcat(retbuf,str);
            break;
        }            
    if(pc->between != NULLTEXT)
        strcat(retbuf,pc->between);
    switch(pc->cformat)
        {
        case 1 :
        case 2 :
        case 3 : 
            itoap(col,str,pc->cformat);
            strcat(retbuf,str);
            break;
        case 4 :
            if(col)
                str[0] = (TEXT) col;
            else
                str[0] = (TEXT) AT_ON;
            str[1] = '\0';
            strcat(retbuf,str);
            break;
        }            
    if(pc->after != NULLTEXT)
        strcat(retbuf,pc->after);
    return(retbuf);                
    }  

#endif



