/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 9/1/90 at 00:28:37
*
*   Name            dbms.h -- header file for dbms        
*                                   
*   Description     Header file for simple link list data base           
*
*                                   
**/                                 

#define DBMSINTREC BIT0
#define DBMSEQUREC BIT1
#define DBMSGTEREC BIT2
#define DBMSNXTREC BIT3
#define DBMSADDREC BIT4
#define DBMSDELREC BIT5 
#define DBMSFRSREC BIT6 
#define DBMSLSTREC BIT7 
#define DBMSPRVREC BIT8 
#define DBMSRWTREC BIT9 
#define DBMSCLSREC BIT10
#define DBMSMRKREC BIT11
#define DBMSSRDREC BIT12
#define DBMSERDREC BIT13
#define DBMSCNTREC BIT14
#define DBMSEWRREC BIT15

#define DBMSPUT BIT1
#define DBMSGET BIT2
#define DBMSFREE BIT3
#define DBMSCLEAR BIT4
#define DBMSSAVE BIT5

typedef LONG DBDP;  /* DataBase Data Pointer  */

struct listbuf
    {
    struct listbuf *listnext;
    struct listbuf *listprev;
    DBDP listloc;
    TEXT *listkey;
    };

struct DbmsKey
    {
    struct DbmsKey *dbkeynext;
    COUNT dbkeyofst;
    COUNT dbkeylen;
    COUNT dbkeytype;/* 1 for TEXT, 2 for INTEGER                    */
    };

struct DbmsGroup
    {
    struct DbmsKey *dbkeysegs;
    struct DbmsGroup *dbkeyngrp;
    struct DbmsGroup *dbkeypgrp;
    };

struct DbmsCashe
    {
    TEXT *dbmsbloc;
    struct DbmsCashe *dbmsnbuf;
    struct DbmsCashe *dbmspbuf;
    COUNT dbmstime;
    COUNT dbmsedit;
    COUNT dbmssave;
    DBDP dbmstart;
    };

struct DbmsInfo
    {
    struct DbmsInfo *dbmsnext;
    COUNT dbmsnbr;
    struct listbuf *dbmshead;
    struct listbuf *dbmstail;
    struct DbmsKey *dbmskey;
    struct listbuf *dbmscur;
    COUNT dbmssize;
    COUNT dbmspags;
    COUNT dbmsslots;
    LONG dbmsmemb;
    COUNT dbmsapags;
    struct DbmsCashe *dbmschead;
    struct DbmsCashe *dbmsctail;
    DBDP dbmsnslot;
    DBDP dbmsdslot;
    TEXT *dbmsfname;
    FILE *dbmsfile;
    COUNT dbmsfopn;
    COUNT dbmsdup;
    };

typedef struct  
    {
    FILE *fptr;
    LONG nloc;
    LONG lloc;
    UCOUNT fsize;
    TEXT *fname;
    } FILEINFO;

typedef struct DbmsInfo *DBP;
typedef struct DbmsCashe *DBC;

#ifndef DBMSVAR
extern struct DbmsInfo *dbmsinfo;
#endif
