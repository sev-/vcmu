/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:19
*
*   Name            vcnoterm.c  --  terminal init no termcap
*
*   Description     This function sets up the terminal from
*                   internal structures
*
*   Return Value    Returns -1 if error
*
**/

#include <vcstdio.h>
#include <vctsetup.h>

#ifdef VCTERMDEF

#define NUMSTRINGS 28
#define NUMSPECIAL 32
#define NUMPRECOMP 3

COUNT vcnoterm(useterm)
TEXT *useterm;              /* Name of terminal to use or NULL      */
    {                       /* ------------------------------------ */
    struct termctrl *termptr;   /* Termctrl structure to init       */
    struct KEYLBL *lblptr;
    TEXT tmpbuf[40],*tmptr,*vcgetenv();
    TEXT *area,**tstr;
    UCOUNT size;
    struct KEYTBLNODE *kptr;
    struct KEYTBLNODE *tblstart;
    COUNT cnt;
    COUNT atoi();
    TEXT *vcalloc();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcnoterm:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif

    termptr = (struct termctrl *)&vcterm.tmname;

    /*--------------------------------------------------------------*/
    /*-------------------Get Terminal String Values-----------------*/
    /*--------------------------------------------------------------*/

    area = vctermarea;
    size = (COUNT)termptr->tmname;    
    if(size == (UCOUNT) 65535l )
        termptr->tmname = NULLTEXT;
    else
        termptr->tmname = area+size;
    tstr = &termptr->ae;
    cnt = NUMSTRINGS;
    while(cnt--)
        {
        size = (COUNT)(*tstr);
        if(size == (UCOUNT) 65535l)
            (*tstr) = NULLTEXT;
        else
            (*tstr) = area+size;
        tstr++;
        }
    cnt = NUMSPECIAL;
    tstr = &termptr->sp0on;
    while(cnt--)
        {
        size = (COUNT)(*tstr);
        if(size == (UCOUNT) 65535l)
            (*tstr) = NULLTEXT;
        else
            (*tstr) = area+size;
        tstr++;
        }
    tstr = &termptr->cursor.before;
    cnt = NUMPRECOMP;
    while(cnt--)
        {
        size = (COUNT)(*tstr);
        if(size == (UCOUNT) 65535l)
            (*tstr) = NULLTEXT;
        else
            (*tstr) = area+size;
        tstr++;
        }
    tstr = &termptr->color.before;
    cnt = NUMPRECOMP;
    while(cnt--)
        {
        size = (COUNT)(*tstr);
        if(size == (UCOUNT) 65535l)
            (*tstr) = NULLTEXT;
        else
            (*tstr) = area+size;
        tstr++;
        }

    /*--------------------------------------------------------------*/
    /*-------------------Setup Key Label Structure------------------*/
    /*--------------------------------------------------------------*/

    lblptr = vclblarea;
    termptr->firstkeylbl = lblptr;
    while(TRUE)
        {
        if(lblptr->klblval == (COUNT) 65535l)
            break;
        size = (COUNT)lblptr->klblptr;
        if(size == (UCOUNT) 65535l)
            lblptr->klblptr = NULLTEXT;
        else
            lblptr->klblptr = area+size;
        lblptr++;
        }
    lblptr->klblval = -1;
    lblptr->klblptr = NULLTEXT;

    /*--------------------------------------------------------------*/
    /*-------------------Get Terminal Keyboard Table----------------*/
    /*--------------------------------------------------------------*/

    tblstart = vckeytbl;
    kptr = vckeytbl;
    termptr->table = vckeytbl;
    while(TRUE)
        {
        if(kptr->key == (COUNT) 65535l)
            break;
        size = (COUNT)kptr->nxtkey;
        if(size == (UCOUNT) 65535l)
            kptr->nxtkey = (struct KEYTBLNODE *)0;
        else
            kptr->nxtkey = tblstart + size;
        size = (COUNT)kptr->othkey;
        if(size == (UCOUNT) 65535l)
            kptr->othkey = (struct KEYTBLNODE *) 0;
        else
            kptr->othkey = tblstart + size;
        kptr++;
        }        

    /*--------------------------------------------------------------*/
    /*---------------------------Finished---------------------------*/
    /*--------------------------------------------------------------*/

    if(termptr->zk == 1)
        vckeyrdy = FALSE;
    if(termptr->zc == -1)
        termptr->zc = 1;
    if(termptr->zt == -1)
        termptr->zt = 1;
    if((tmptr = vcgetenv("COLUMNS")) != NULLTEXT)
        termptr->cols = atoi(tmptr);
    if((tmptr = vcgetenv("LINES")) != NULLTEXT)
        termptr->rows = atoi(tmptr);
    if((tmptr = vcgetenv("VCIN")) != NULLTEXT)
        {
        vcinput = vcalloc(1,strlen(tmptr),vcdebug);
        strcpy(vcinput,tmptr);
        }
    if((tmptr = vcgetenv("VCOUT")) != NULLTEXT)
        {
        vcoutput = vcalloc(1,strlen(tmptr),vcdebug);
        strcpy(vcoutput,tmptr);
        }
    tmptr = useterm;
    return(1);
    }

#endif

