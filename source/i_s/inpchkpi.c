/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:43
*
*   Name            inpchkpi.c - input check picture
*                                   
*   Description     Sets up the input check picture 
*
*   Return Value    VOID
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

VOID inpchkpic(gi)
GETITEM *gi;
    {
    COUNT found = FALSE;
    TEXT *pic1,*pic2;
    COUNT flag;
    pic1 = gi->g_picture;
    pic2 = gi->gtmppic;
    flag = (*gi->gtmpfld == '1') ? 1 : 0;
    while(*pic1 != '\0')
        {
        if((*pic1 == '~') || (*pic1 == '*') 
                         || (*pic1 == '#'))
            {
            if(!found)
                gi->gcndx = (COUNT)(pic1 - gi->g_picture);
            found = TRUE;
            if(flag)
                {
                if(*pic1 == '~')
                    *pic2 = 'X';
                else
                    *pic2 = *pic1;
                }
            else
                *pic2 = ' ';
            }
        else
            *pic2 = *pic1;
        pic1++;
        pic2++;
        }
    }


