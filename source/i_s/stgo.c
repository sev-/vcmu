/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:34
*
*   Name            stgo.c  --  set to go
*
*   Description     This function precompiles the cursor addressing
*                   equation.
*
*   Return Value    Returns -1 if error
*
**/

#include <vcstdio.h>

#ifdef TERMCAP

COUNT stgo(txtpc,cm)
TEXT *txtpc;                /* Precompile passed as test ptr        */
TEXT *cm;                   /* Pointer to string to translate       */
    {                       /* ------------------------------------ */
    struct PRECOMP *pc;     /* Pointer to location for precompile   */
    TEXT *bf,*bt,*af,*tb;
    TEXT *vcalloc();
    COUNT amount,loop=1;
    COUNT strlen();
    TEXT *strcpy();
    VOID vcfree();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "stgo:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( (cm == NULLTEXT) || (*cm == '\0') )
        return(0);
    pc = (struct PRECOMP *) txtpc;
    pc->col_first = 0;
    pc->rofset = 0;
    pc->cofset = 0;
    tb = vcalloc(200,sizeof(TEXT),vcdebug);
    bf = tb;
    while(loop && (*cm != '\0'))
        {
        switch(*cm)
            {
            case '%':
                cm++;
                switch(*cm)
                    {
                    case 'r':
                        pc->col_first = 1;
                        break;
                    case 'i' :
                        pc->cofset += 1;
                        pc->rofset += 1;
                        break;
                    case 'd':
                        pc->rformat = 1;
                        loop = 0;
                        break;
                    case '2' :
                        pc->rformat = 2;
                        loop = 0;
                        break;
                    case '3' :
                        pc->rformat = 3;
                        loop = 0;
                        break;
                    case '.' :
                        pc->rformat = 4;
                        loop = 0;
                        break;
                    case '+' :
                        cm++;
                        pc->rofset += *cm;
                        pc->rformat = 4;
                        loop = 0;
                        break;
                    case '%' :
                        *(tb++) = '%';
                        break;
                    default :
                        return(-1);
                    }
                cm++;
                break;
            default :
                *(tb++) = *(cm++);
                break;
            }
        }
    *(tb++) = '\0';
    bt = tb;
    loop=1;
    while(loop && (*cm != '\0'))
        {
        switch(*cm)
            {
            case '%':
                cm++;
                switch(*cm)
                    {
                    case 'r':
                        pc->col_first = 1;
                        break;
                    case 'i' :
                        pc->cofset += 1;
                        pc->rofset += 1;
                        break;
                    case 'd':
                        pc->cformat = 1;
                        loop = 0;
                        break;
                    case '2' :
                        pc->cformat = 2;
                        loop = 0;
                        break;
                    case '3' :
                        pc->cformat = 3;
                        loop = 0;
                        break;
                    case '.' :
                        pc->cformat = 4;
                        loop = 0;
                        break;
                    case '+' :
                        cm++;
                        pc->cofset += *cm;
                        pc->cformat = 4;
                        loop = 0;
                        break;
                    case '%' :
                        *(tb++) = '%';
                        break;
                    default :
                        return(-1);
                    }
                cm++;
                break;
            default :
                *(tb++) = *(cm++);
                break;
            }
        }
    *(tb++) = '\0';
    af = tb;
    loop=1;
    while(*cm != '\0')
        {
        switch(*cm)
            {
            case '%':
                cm++;
                switch(*cm)
                    {
                    case '%' :
                        *(tb++) = '%';
                        break;
                    default :
                        return(-1);
                    }
                cm++;
                break;
            default :
                *(tb++) = *(cm++);
                break;
            }
        }
    *tb = '\0';
    amount = tb - bf + 1;
    tb = vcalloc(amount,sizeof(TEXT),vcdebug);
    if(strlen(bf))
        {
        strcpy(tb,bf);
        pc->before = tb;
        }
    else
        pc->before = NULLTEXT;
    if(pc->before != NULLTEXT)
        tb += strlen(pc->before)+1;
    if(strlen(bt))
        {
        strcpy(tb,bt);
        pc->between = tb;
        }
    else
        pc->between = NULLTEXT;
    if(pc->between != NULLTEXT)
        tb += strlen(pc->between)+1;
    if(strlen(af))
        {
        strcpy(tb,af);
        pc->after = tb;
        }
    else
        pc->after = NULLTEXT;
    vcfree(bf,vcdebug);
    return(0);
    }
#endif


