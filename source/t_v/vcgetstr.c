/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:57
*
*   Name            vcgetstr.c  --  get string value
*
*   Description     This function retrieves the termcap information
*                   for the string.
*
*   Return Value    Returns pointer to the area where information is
*                   stored.
*
**/

#include <vcstdio.h>

#ifdef TERMCAP

TEXT *vcgetstr(id,area)
TEXT *id;           /* Pointer to name of string value              */
TEXT **area;        /* Pointer to pointer to area to put information*/
    {
    TEXT *ptr,chr,*start;
    TEXT trash[4],*findset();
    COUNT ahtoi();
    COUNT aotoi();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcgetstr:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    start = *area;
    if(id == NULLTEXT)
        return(NULLTEXT);
    if( (ptr = findset(id)) == NULLTEXT)
        return(NULLTEXT);
    ptr += 2;
    if ( *(ptr++) == '@')
        return(NULLTEXT);
    while( *ptr != ':')
        {
        switch(*ptr)
            {
            case '\\' :
                ptr++;
                switch(*ptr)
                    {
                    case 'n' :
                        ptr++;
                        chr = '\n';
                        break;
                    case 't' :
                        ptr++;
                        chr = '\t';
                        break;
                    case 'v' :
                        ptr++;
                        chr = '\v';
                        break;
                    case 'b' :
                        ptr++;
                        chr = '\b';
                        break;
                    case 'r' :
                        ptr++;
                        chr = '\r';
                        break;
                    case 'f' :
                        ptr++;
                        chr = '\f';
                        break;
                    case 'E' :
                        ptr++;
                        chr = ' ' - 5;
                        break;
                    case '^' :
                        ptr++;
                        chr = '^';
                        break;
                    case '\'' :
                        ptr++;
                        chr = '\'';
                        break;
                    case '\"' :
                        ptr++;
                        chr = '\"';
                        break;
                    case '\\' :
                        ptr++;
                        chr = '\\';
                        break;
                    case ':' :
                        ptr++;
                        chr = ':';
                        break;
                    case 'x' :
                        ptr++;
                        trash[0] = *(ptr++);
                        trash[1] = *(ptr++);
                        trash[2]= '\0';
                        chr = ahtoi(&trash[0]);
                        break;
                    default :
                        trash[0] = *(ptr++);
                        trash[1] = *(ptr++);
                        trash[2] = *(ptr++);
                        trash[3]= '\0';
                        chr = aotoi(&trash[0]);
                        break;
                    }
                break;
            case '^' :
                ptr++;
                if( *ptr < 'a' )
                    chr = *(ptr++) - 'A' + 1;
                else
                    chr = *(ptr++) - 'a' + 1;
#ifdef PRIMOS
                chr |= 128;
#endif
                break;
            default :
                chr = *(ptr++);
                break;
            }   
        **area = chr;
        *area += 1;
        }
    **area = '\0';
    *area += 1;
    return(start);
    }

#endif
 
