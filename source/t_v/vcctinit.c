/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:14
*                
*   Name            vcctinit.c  --  terminal init program
*
*   Description     This function sets up the terminal from
*                   compiled termcap file
*
*   Return Value    Returns -1 if error
*
**/

#include <vcstdio.h>
#include <vctcap.h>

FILE *tcapfil = (FILE *)0;

COUNT vcctinit(useterm)
TEXT *useterm;              /* Name of terminal to use or NULL      */
    {                       /* ------------------------------------ */
    struct termctrl *termptr;   /* Termctrl structure to init       */
    struct vckeys *keyptr;      /* Tckey structure to init          */ 
    struct BODR *bordptr;       /* Border structure to init         */
    struct KEYLBL *lblptr;
    LONG findtofst(),ofset;
    TEXT tmpbuf[40],*tmptr,*vcgetenv();
    TEXT *area,**tstr;
    UCOUNT size;
    struct KEYTBLNODE *kptr;
    TEXT *tblstart;
    COUNT ssize;
    COUNT cnt;
    TEXT *vcalloc();
    TEXT *strcpy();
    VOID terror();
    COUNT vcfclose();
    VOID empty();
    COUNT atoi();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcctinit:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    termptr = (struct termctrl *)&vcterm.tmname;
    keyptr =  (struct vckeys *)&vckey.esc;
    bordptr = (struct BODR *)&border[0].up;
    /*--------------------------------------------------------------*/
    /*---------------------Get Terminal Name------------------------*/
    /*--------------------------------------------------------------*/
    if(useterm == NULLTEXT)
        {
#ifdef IBM
        strcpy(tmpbuf,"ibmpc");
#endif
#ifdef OS2
        strcpy(tmpbuf,"os2pc");
#endif
#ifdef TERMONLY
        strcpy(tmpbuf,"vt100");
#endif
        if((tmptr = vcgetenv("TERM")) != NULLTEXT)
            strcpy(tmpbuf,tmptr);
        }
    else
        strcpy(tmpbuf,useterm);
    if((ofset = findtofst(tmpbuf)) == (LONG) 0l)
        {
        strcat(tmpbuf,(TEXT *)" : Terminal not found in termcap.vcc");
        terror(tmpbuf);
        }

    fseek(tcapfil,ofset,0);

    /*--------------------------------------------------------------*/
    /*-------------------Setup Special Keys-------------------------*/
    /*--------------------------------------------------------------*/

    fread(keyptr,sizeof(*keyptr),1,tcapfil);

    /*--------------------------------------------------------------*/
    /*-------------------Get Border Characters----------------------*/
    /*--------------------------------------------------------------*/

    fread(bordptr,sizeof(*bordptr),2,tcapfil);

    /*--------------------------------------------------------------*/
    /*-------------------Get Terminal Number Values-----------------*/
    /*--------------------------------------------------------------*/

    fread(&termptr->rows,sizeof(COUNT),NUMNUMBERS,tcapfil);

    /*--------------------------------------------------------------*/
    /*-------------------Get Terminal String Values-----------------*/
    /*--------------------------------------------------------------*/

    fread(&size,sizeof(COUNT),1,tcapfil);
    area = vcalloc(size,sizeof(TEXT),vcdebug);
    fread(area,sizeof(TEXT),size,tcapfil);
    fread(&size,sizeof(COUNT),1,tcapfil);
    if(size == (UCOUNT) 65535l )
        termptr->tmname = NULLTEXT;
    else
        termptr->tmname = area+size;
    tstr = &termptr->ae;
    cnt = NUMSTRINGS;
    while(cnt--)
        {
        fread(&size,sizeof(COUNT),1,tcapfil);
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
        fread(&size,sizeof(COUNT),1,tcapfil);
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
        fread(&size,sizeof(COUNT),1,tcapfil);
        if(size == (UCOUNT) 65535l)
            (*tstr) = NULLTEXT;
        else
            {
            (*tstr) = vcalloc(size,sizeof(TEXT),vcdebug);
            fread((*tstr),sizeof(TEXT),size,tcapfil);
            }
        tstr++;
        }
    fread(&termptr->cursor.col_first,sizeof(COUNT),5,tcapfil);
    tstr = &termptr->color.before;
    cnt = NUMPRECOMP;
    while(cnt--)
        {
        fread(&size,sizeof(COUNT),1,tcapfil);
        if(size == (UCOUNT) 65535l)
            (*tstr) = NULLTEXT;
        else
            {
            (*tstr) = vcalloc(size,sizeof(TEXT),vcdebug);
            fread((*tstr),sizeof(TEXT),size,tcapfil);
            }
        tstr++;
        }
    fread(&termptr->color.col_first,sizeof(COUNT),5,tcapfil); 

    /*--------------------------------------------------------------*/
    /*-------------------Setup Key Label Structure------------------*/
    /*--------------------------------------------------------------*/

    fread(&cnt,sizeof(COUNT),1,tcapfil);
    if((lblptr = (struct KEYLBL *) vcalloc(cnt+1,sizeof(*lblptr),
                                            vcdebug)) == (struct KEYLBL *)0)
        {
        terror((TEXT *)"error key labels");
        }
    termptr->firstkeylbl = lblptr;
    while(cnt--)
        {
        fread(&lblptr->klblval,sizeof(COUNT),1,tcapfil);
        fread(&size,sizeof(COUNT),1,tcapfil);
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

    ssize = sizeof(struct KEYTBLNODE);
    fread(&cnt,sizeof(COUNT),1,tcapfil);
    tblstart = vcalloc(cnt,ssize,vcdebug);
    kptr = (struct KEYTBLNODE *)tblstart;
    termptr->table = (struct KEYTBLNODE *)tblstart;
    while(cnt--)
        {
        fread(&kptr->key,sizeof(COUNT),2,tcapfil);
        fread(&size,sizeof(COUNT),1,tcapfil);
        if(size == (UCOUNT) 65535l)
            kptr->nxtkey = (struct KEYTBLNODE *)0;
        else
            kptr->nxtkey = (struct KEYTBLNODE *)(tblstart+(ssize * size));
        fread(&size,sizeof(COUNT),1,tcapfil);
        if(size == (UCOUNT) 65535l)
            kptr->othkey = (struct KEYTBLNODE *) 0;
        else
            kptr->othkey = (struct KEYTBLNODE *)(tblstart+(ssize * size));
        kptr++;
        }        

    /*--------------------------------------------------------------*/
    /*---------------------------Finished---------------------------*/
    /*--------------------------------------------------------------*/
    if(tcapfil != (FILE *) 0)
       vcfclose(tcapfil);
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
    return(1);
    }

LONG findtofst(term)
TEXT *term;
    {
    FILE *vcfopen();
    COUNT magic;
    LONG lcnt;
    COUNT total_entries;
    VOID empty();
    COUNT fdternam();
    TEXT tname[40];
    TEXT path1buf[100],*tmpptr,*vcgetenv();
    LONG ofset;
    TEXT *strsset();
    TEXT *strcpy();
    VOID terror();
    strcpy(path1buf,"/etc/termcap.vcc");
    if((tmpptr = vcgetenv("VCCTERMCAP")) != NULLTEXT)
        strcpy(path1buf,tmpptr);
    if( ( tcapfil = vcfopen(path1buf,VCF_RB)) == (FILE *) 0)
        terror((TEXT *)"Cannot open termcap.vcc");
    fread(&magic,sizeof(COUNT),1,tcapfil);
    if(magic != 975)
        terror((TEXT *)"Compiled termcap file corrupt rebuild");
    fread(&lcnt,sizeof(LONG),1,tcapfil);
    fread(&total_entries,sizeof(COUNT),1,tcapfil);
    while(total_entries--)
        {
        empty(tname,40);
        ofset = 0l;
        fread(tname,sizeof(TEXT),40,tcapfil);
        fread(&ofset,sizeof(LONG),1,tcapfil);
        if( fdternam(tname,term) )
            break;
        }
    if(total_entries > 0)
        return(ofset);
    else
        return((LONG)0l);
    }

