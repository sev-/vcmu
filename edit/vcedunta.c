/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:52:02
*
*   Name            vcedunta.c - untab
*                                   
*   Description     Low level function to remove tabs
*
*   Return Value    Returns pointer to new string location
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

TEXT *vceduntab(tloc,cnt)
TEXT *tloc;                 /* String compress tabs                 */
COUNT *cnt;                 /* Current length of buffer             */
    {                       /* ------------------------------------ */
    TEXT *ptr;              /* Working buffer pointer               */
    TEXT *dest;             /* Working buffer pointer               */
    COUNT used = 0;         /* Number of characters used on line    */
    ptr = tloc;                         /* Point to top of line     */
    dest = vcedfbuf;                    /* Point to destination     */
    while((*cnt)--)                     /* While more characters    */
        {                               /*                          */
        if(*ptr == vcedval.tabspace)    /* If not tabspace          */
            ptr++;                      /* Skip tabspace            */
        else                            /*                          */
            {                           /*                          */
            *(dest++) = *(ptr++);       /* Move character           */
            used++;                     /* Increment number used    */
            }                           /*                          */
        }                               /*                          */
    *cnt = used;                        /* Assign number used       */
    return(&vcedfbuf[0]);               /* Return new string loc.   */
    }                                   /* ------------------------ */

