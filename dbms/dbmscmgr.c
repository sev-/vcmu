/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:44
*
*   Name            dbmscmgr -- data base cashe manager                     
*                                   
*   Description     This program finds or puts the data into the
*                   file system or memory
*
*   Return Value    Returns pointer where to place information
*                   and sets the database address
*
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

TEXT *dbmscmgr(dbp,dbdpp,mode)
DBP dbp;
DBDP *dbdpp;
COUNT mode;         /* Operation                                    */
    {
    TEXT *bufptr = NULL;/* Buffer pointer for creating buffers      */
    DBDP *dptr;                         /* Pointer for deleting     */
    DBC dbmsgpage();/* Get pointer to proper cashe control in mem   */
    DBC casheinfo;
    DBC curcashe;
    TEXT *dbmscbuf();
    VOID dbmscpage();
    VOID dbmsipage();
    VOID dbmswpage();
    COUNT askmsg();
    VOID vcfree();
    COUNT vcdelfil();
    switch(mode)
        {
        case DBMSGET:
            if( (casheinfo = dbmsgpage(dbp,*dbdpp)) != (DBC) 0)
                bufptr = dbmscbuf(dbp,casheinfo,*dbdpp);
            break;
        case DBMSPUT:
/*            if(dbp->dbmsdslot != (DBDP) 0)  /* If any deleted rec   */
/*                {                       /*                          */
/*                if((casheinfo = dbmsgpage(dbp,dbp->dbmsdslot)) != (DBC) 0)
/*                    {                   /*                          */
/*                    *dbdpp = dbp->dbmsdslot;/* Assign slot          */
/*                    bufptr = dbmscbuf(dbp,casheinfo,*dbdpp); /* Get */
/*                    dptr = (DBDP *)bufptr;  /* Point to buffer      */
/*                    dbp->dbmsdslot = *dptr; /* Set next delete slot */
/*                    }                   /*                          */
/*                }                       /*                          */
/*            else                        /* Create new slot          */
/*                {                       /*                          */
                if( (casheinfo = dbmsgpage(dbp,dbp->dbmsnslot)) == (DBC)0)
                    {
                    if(dbp->dbmsapags <= dbp->dbmspags)
                        dbmscpage(dbp);
                    else
                        {
                        dbmswpage(dbp);
                        dbmsipage(dbp);
                        }
                    casheinfo = dbp->dbmschead;
                    }
                if( (bufptr = dbmscbuf(dbp,casheinfo,dbp->dbmsnslot)) == NULL)
                    askmsg("debug","null in cmgr",0);
                *dbdpp = dbp->dbmsnslot;
                dbp->dbmsnslot++;
/*                } */
            casheinfo->dbmssave++;
            break;
        case DBMSFREE:
/*            if( (casheinfo = dbmsgpage(dbp,*dbdpp)) != (DBC) 0)
                {                       /*                          */
/*                bufptr = dbmscbuf(dbp,casheinfo,*dbdpp); /* Fnd buf */
/*                casheinfo->dbmssave++;  /* Make sure this saved     */
/*                dptr = (DBDP *)bufptr;  /* Point to first of buffer */
/*                *dptr = dbp->dbmsdslot; /* Save previous slot       */
/*                dbp->dbmsdslot = *dbdpp;/* Set this to next avail   */
/*                }                       /*                          */
            break;
        case DBMSCLEAR:
            if(dbp->dbmsfile != (FILE *)0)
                {
                vcfclose(dbp->dbmsfile);
                vcdelfil(dbp->dbmsfname);
                vcfree(dbp->dbmsfname,vcdebug);
                }
            dbp->dbmsfile = (FILE *)0;
            dbp->dbmsfname = NULLTEXT;
            curcashe = dbp->dbmschead;
            dbp->dbmsnslot = 0l;
            while(curcashe != (DBC)0)
                {
                casheinfo = curcashe->dbmsnbuf;
                vcfree(curcashe,vcdebug);
                curcashe = casheinfo;
                }
            dbp->dbmschead = (DBC)0;
            dbp->dbmsctail = (DBC)0;
            dbp->dbmsapags = 0;
            break;
        case DBMSSAVE:
            if( (casheinfo = dbmsgpage(dbp,*dbdpp)) != (DBC) 0)
                casheinfo->dbmssave++;
            break;
        }
    return(bufptr);
    }

TEXT *dbmscbuf(dbp,casheinfo,dbdp)
DBP dbp;
DBC casheinfo;
DBDP dbdp;
    {
    COUNT offset;
    offset = (COUNT)(dbdp - casheinfo->dbmstart);
    return((TEXT *)(casheinfo->dbmsbloc + (offset * dbp->dbmssize)));
    }

DBC dbmsgpage(dbp,slot)
DBP dbp;
LONG slot;
    {
    DBC curcashe = (DBC)0;
    VOID dbmsctoh();
    VOID dbmswpage();
    VOID dbmsrpage();
    if( (curcashe = dbp->dbmschead) == (DBC)0)
        return(curcashe);
    while(curcashe != (DBC )0)
        {
        if((curcashe->dbmstart <= slot) &&
           ((curcashe->dbmstart + dbp->dbmsslots) >= slot))
            break;
        curcashe = curcashe->dbmsnbuf;
        }
    if( (curcashe == (DBC)0) && (slot < dbp->dbmsnslot) )
        {
        dbmswpage(dbp);
        dbmsrpage(dbp,slot);
        curcashe = dbp->dbmschead;
        }
    if(curcashe != (DBC)0)
        dbmsctoh(dbp,curcashe);
    return(curcashe);
    }

VOID dbmswpage(dbp)
DBP dbp;
    {
    COUNT dbmsfopn();
    VOID terror();
    if(dbmsfopn(dbp) && dbp->dbmsctail->dbmssave)
        {
        if(fseek(dbp->dbmsfile,(LONG)(dbp->dbmsctail->dbmstart *
                                   dbp->dbmssize),0))
            terror("Error Seeking - Disk Full?");
        if(!(fwrite(dbp->dbmsctail->dbmsbloc,dbp->dbmssize*
                                  (dbp->dbmsslots+1),1,dbp->dbmsfile)))
            terror("Error Writing - Disk Full?");
        }
    }

VOID dbmsrpage(dbp,slot)
DBP dbp;
DBDP slot;
    {
    COUNT dbmsfopn();
    COUNT page;
    DBDP fslot;
    VOID dbmsctoh();
    if(dbmsfopn(dbp))
        {
        if(dbp->dbmsslots)
            {
            page = (COUNT) (slot / (dbp->dbmsslots+1));
            fslot = (DBDP) (page * (dbp->dbmsslots+1));
            }
        else
            {
            page = (COUNT)slot;
            fslot = slot;
            }
        fseek(dbp->dbmsfile,(LONG)(fslot * dbp->dbmssize),0);
        fread(dbp->dbmsctail->dbmsbloc,dbp->dbmssize*(dbp->dbmsslots+1),
                                              1,dbp->dbmsfile);
        dbp->dbmsctail->dbmstart = fslot;
        dbp->dbmsctail->dbmssave = FALSE;
        dbmsctoh(dbp,dbp->dbmsctail);
        }
    }

VOID dbmscpage(dbp)
DBP dbp;
    {
    TEXT *vcalloc();
    DBC casheinfo;
    VOID dbmsctoh();
    casheinfo = (DBC) vcalloc(1,sizeof(*casheinfo),vcdebug);
    casheinfo->dbmstart = dbp->dbmsnslot;
    casheinfo->dbmssave = FALSE;
    casheinfo->dbmsnbuf = (DBC)0;
    casheinfo->dbmspbuf = (DBC)0;
    casheinfo->dbmsbloc = vcalloc((dbp->dbmsslots+1),dbp->dbmssize,vcdebug);
    dbmsctoh(dbp,casheinfo);
    dbp->dbmsapags++;
    }

VOID dbmsipage(dbp)
DBP dbp;
    {
    DBC casheinfo;
    VOID dbmsctoh();
    casheinfo = dbp->dbmsctail;
    casheinfo->dbmstart = dbp->dbmsnslot;
    casheinfo->dbmssave = FALSE;
    dbmsctoh(dbp,casheinfo);
    }

VOID dbmsctoh(dbp,casheinfo)
DBP dbp;
DBC casheinfo;
    {
    if( dbp->dbmschead == (DBC)0)
        {
        dbp->dbmschead = casheinfo;
        dbp->dbmsctail = casheinfo;
        }
    if(casheinfo != dbp->dbmschead)
        {
        if(casheinfo == dbp->dbmsctail)
            {
            if(casheinfo->dbmspbuf != (DBC)0)
                dbp->dbmsctail = casheinfo->dbmspbuf;
            }
        if(casheinfo->dbmsnbuf != (DBC)0)
            casheinfo->dbmsnbuf->dbmspbuf = casheinfo->dbmspbuf;
        if(casheinfo->dbmspbuf != (DBC)0)
            casheinfo->dbmspbuf->dbmsnbuf = casheinfo->dbmsnbuf;
        casheinfo->dbmsnbuf = dbp->dbmschead;
        dbp->dbmschead->dbmspbuf = casheinfo;
        casheinfo->dbmspbuf = (DBC)0;
        dbp->dbmschead = casheinfo;
        }
    }

COUNT dbmsfopn(dbp)
DBP dbp;
    {
    FILE *vcfopen();
    TEXT *mktemp();
    TEXT template[9];
    TEXT *vcalloc();
    TEXT *strcpy();
    VOID terror();
    if(dbp->dbmsfile == (FILE *)0)
        {
        strcpy(template,"rpXXXXXX");
        dbp->dbmsfname = vcalloc(1,9,vcdebug);
        strcpy(dbp->dbmsfname,mktemp(template));
        if( (dbp->dbmsfile = vcfopen(dbp->dbmsfname,"w+b")) == (FILE *) 0)
            terror("Error opening DBMS file");
        }
    return(TRUE);
    }


