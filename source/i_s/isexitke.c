/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:56
*
*   Name            isexitke.c - is exit key
*                                   
*   Description     Returns if is exit key
*
*   Return Value    Returns TRUE is an exit key entered
*                                   
**/

#include <vcstdio.h>

COUNT isexitkey(key)
COUNT key;
    {
    COUNT retval = FALSE;
    if( key == spkey.fld_left ||
        key == spkey.fld_right ||
        key == spkey.fld_up ||
        key == spkey.fld_down ||
        key == spkey.fld_pgup ||
        key == spkey.fld_pgdn ||
        key == spkey.fld_end ||
        key == spkey.fld_home ||
        key == spkey.fld_ret ||
        key == spkey.abort ||
        key == spkey.done ||
        key >= 9000 )
        retval = TRUE;
    return(retval);
    }


