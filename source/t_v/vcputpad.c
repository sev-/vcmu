/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:44
*
*   Name            vcputpad.c  --  add nulls for terminal delay
*
*   Description     This expands delay variable for string                   
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMONLY
extern COUNT vcbaud;
#else
COUNT vcbaud;
#endif

VOID vcputpad(str,lines,func)
PFAST TEXT *str;    /* Pointer to string to decode                  */
PFAST COUNT lines;  /* Number of lines affected                     */
PFI func;           /* Function to send to terminal                 */
    {
    TEXT buf[5];
    COUNT cnt = 0;
    COUNT delay_byte;
    COUNT full;
    TEXT outchr;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcputstr:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(vcdigit(*str))
        {
        while(vcdigit(*str))
            {
            buf[cnt++] = *str;
            if(cnt == 3)
                break;
            str++;
            }
        buf[cnt] = '\0';
        cnt = adtoi(buf);
        cnt *= lines;
        cnt *= 100;
        delay_byte = vcbaud / 90;
        if(vcterm.pc == NULLTEXT)
            outchr = '\0';
        else
            outchr = *(vcterm.pc);
        full = cnt / delay_byte;
        if(cnt % delay_byte)
            full++;
        while(full--)
            (*func)(outchr);
        if(*str == '*')
            str++;
        }
    while(*(str))
        (*func)(*(str++));
    }
