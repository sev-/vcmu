/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 9/2/90 at 23:34:24
*
*   Name            vceditor.c  -  a stand alone editor application
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

#define DEFILE (TEXT *)"noname.fil"

struct VCEDWDO
    {                                   /* ------------------------ */
    struct VCEDWDO *vcedwnext;          /* Pointer to next file     */
    VCED *vcedwvced;                    /* Pointer to structure     */
    COUNT vcedwstat;                    /* Status of window         */
    };                                  /* ------------------------ */

struct VCEDFILE
    {                                   /* ------------------------ */
    struct VCEDFILE *vcedfnext;         /* Pointer to next file     */
    VCEDBUF *vcedfbuf;                  /* Pointer to structure     */
    TEXT *vcedfname;                    /* Name of file             */
    COUNT vcedfstat;                    /* Status of buffer         */
    LONG vcedftop;                      /* Last top of screen       */
    LONG vcedfcur;                      /* Last current line        */
    LONG vcedftlin;                     /* Last top of screen       */
    LONG vcedfclin;                     /* Last current line        */
    LONG vcedfarow;                     /* Anchor row               */
    DBDP vcedfalin;                     /* Anchor line              */
    COUNT vcedfchr;                     /* Current character        */
    COUNT vcedfachr;                    /* Anchor character         */
    COUNT vcedfoff;                     /* File offset              */
    };                                  /* ------------------------ */

struct VCEDFILE *vcedfiles = (struct VCEDFILE *)0; /* List of files */
struct VCEDWDO *vcedwdos = (struct VCEDWDO *)0;    /* List of window*/
TEXT vceddfil[40];                      /* Default file location    */
    
main(argc,argv)
int argc;                               /* Number of arg.           */
TEXT **argv;                            /* Command line arg.        */
    {                                   /* ------------------------ */
    struct VCEDFILE *curfile;           /* Current buffer           */
    struct VCEDFILE *tmpfile;           /* Temporary buffer         */
    struct VCEDWDO *curwdo;             /* Current window           */
    struct VCEDWDO *tmpwdo;             /* Temporary window         */
    COUNT key;                          /* Key returned             */
    COUNT changed;                      /* If files changed         */
    WPTR wptr;                          /* Status window            */
    VCEDBUF *vcedload();                /* Declare functions        */
    VCED *vcedopen();                   /*    "        "            */
    WPTR wxopen();                      /*    "        "            */
    TEXT *vcalloc();                    /*    "        "            */
    vcstart(CLRSCRN);                   /* Start Vitamin C          */
    setkeytrap(NULLFUNC);               /* Stop keytrap function    */
#ifdef UNIX                             /* If compiled with UNIX    */
    vcsignal();                         /* Start signal processing  */
#endif                                  /*                          */
    setaskmsg(vcterm.rows-1,0,vcterm.rows-1,min(39,(vcterm.cols-2)),
                -1,0,NULLTEXT);         /* Setup askmsg location    */
    wptr = wxopen(vcterm.rows-1,0,vcterm.rows-1,        /* Open stat*/
                     vcterm.cols-2,NULLTEXT,ACTIVE,0,0);/* Window   */
    if(argc < 2)                        /* If no file on line       */
        {                               /*                          */
        if(vcedaskfil() == spkey.abort) /* If escape entered        */
            {                           /*                          */
            vcend(CLOSE);               /* Close windows            */
            exit(0);                    /* Leave editor             */
            }                           /*                          */
        if(isblank(vceddfil))           /* If entered blank         */
            strcpy(vceddfil,DEFILE);    /* Copy default file name   */
        curfile = (struct VCEDFILE *)vcalloc(1,sizeof(*curfile),vcdebug);
        curfile->vcedfname  = vceddfil; /* Assign file name         */
        curfile->vcedfstat = 0;         /* Not opened yet           */
        curfile->vcedfnext = vcedfiles; /* Assign next buffer       */
        vcedfiles = curfile;            /* Make head of list        */
        }                               /*                          */
    else                                /*                          */
        {                               /*                          */
        argc--;                         /* Subtract for prog. name  */
        argv++;                         /* Point to first name      */
        while(argc)                     /* While more files on line */
            {                           /*                          */
            curfile = (struct VCEDFILE *)vcalloc(1,sizeof(*curfile),vcdebug);
            curfile->vcedfname  = *argv;/* Assign file name         */
            curfile->vcedfstat = 0;     /* Not opened yet           */
            curfile->vcedftop = 0;      /* Start on first line      */
            curfile->vcedfcur = 0;      /* Start on first line      */
            curfile->vcedfnext = vcedfiles;  /* Assign next buffer  */
            vcedfiles = curfile;        /* Make head of list        */
            argc--;                     /* Subtract arg.            */
            argv++;                     /* Next arg                 */
            }                           /*                          */
        }                               /*                          */
    curfile = vcedfiles;                /* Start at last file       */
    while(curfile->vcedfnext != (struct VCEDFILE *)0)   /* Goto top */
        curfile = curfile->vcedfnext;   /* Look at next             */
    vcedwdos = (struct VCEDWDO *)vcalloc(1,sizeof(*vcedwdos),vcdebug);
    vcedwdos->vcedwnext = (struct VCEDWDO *)0;  /* No next window   */
    curwdo = vcedwdos;                  /* Start with first window  */
    curfile->vcedfbuf = vcedload(curfile->vcedfname,NULLTEXT,VCEDFFIL);
    curfile->vcedfstat = TRUE;          /* File has been opened     */
    curwdo->vcedwvced = vcedopen(0,0,vcterm.rows-2,vcterm.cols-1,
                    curfile->vcedfname,-1,VCEDSTATUS,
                    curfile->vcedfbuf,-1,-1,wptr);  /* Open window  */
    curwdo->vcedwstat = TRUE;           /* Window is open           */
#ifdef VCEDFULL
    vcedunstart(curwdo->vcedwvced);     /* Start undo buffers       */
    vcedblkstart(curwdo->vcedwvced);    /* Start copy buffers       */
#endif
    while(TRUE)                         /* While still editing      */
        {                               /*                          */
        vcedit(curwdo->vcedwvced);      /* Edit current window      */
        if(curwdo->vcedwvced->edmail == VCEDNEWFIL) /* Wants new fil*/
            {                           /*                          */
            key = vcedaskfil();         /* Get file name            */
            if((key != spkey.abort) &&  /* If abort not entered     */
               !isblank(vceddfil)  )    /* And is not empty         */
                {                       /*                          */
                curfile = vcedfiles;    /* Start at end of files    */
                while(curfile != (struct VCEDFILE *)0) /* While more*/
                    {                   /*                          */
                    if(curfile->vcedfstat)  /* If file opened       */
                        if(curfile->vcedfbuf == curwdo->vcedwvced->edbuffer)
                            break;      /* If this is it break      */
                    curfile = curfile->vcedfnext;   /* Next file    */
                    }                   /*                          */
                curfile->vcedftop = curwdo->vcedwvced->edtrow;
                curfile->vcedfcur = curwdo->vcedwvced->edcrow;
                curfile->vcedftlin = curwdo->vcedwvced->edtline;
                curfile->vcedfclin = curwdo->vcedwvced->edcline;
                curfile->vcedfarow = curwdo->vcedwvced->edarow;
                curfile->vcedfalin = curwdo->vcedwvced->edaline;
                curfile->vcedfchr = curwdo->vcedwvced->edcchar;
                curfile->vcedfachr = curwdo->vcedwvced->edachar;
                curfile->vcedfoff = curwdo->vcedwvced->edoffset;
                tmpfile = (struct VCEDFILE *)vcalloc(1,sizeof(*tmpfile),
                                                    vcdebug);
                tmpfile->vcedfname  = vceddfil;/* Assign file name  */
                tmpfile->vcedfstat = 0; /* Not opened yet           */
                tmpfile->vcedftop = 0;  /* Start on first line      */
                tmpfile->vcedfcur = 0;  /* Start on first line      */
                tmpfile->vcedfnext = vcedfiles;  /* Assign nxt buf  */
                vcedfiles = tmpfile;    /* Make head of list        */
                tmpfile->vcedfbuf = vcedload(tmpfile->vcedfname,
                                                NULLTEXT,VCEDFFIL);
                tmpfile->vcedfstat = TRUE;  /* File opened          */
                tmpfile->vcedftop = 0;      /* Starting values      */
                tmpfile->vcedfcur = 0;      /*    "       "         */
                tmpfile->vcedftlin = tmpfile->vcedfbuf->bffline;
                tmpfile->vcedfclin = tmpfile->vcedfbuf->bffline;
                tmpfile->vcedfarow = 0l;    /* Starting values      */
                tmpfile->vcedfalin = (DBDP)0;/*   "       "         */
                tmpfile->vcedfchr = 0;      /*    "       "         */
                tmpfile->vcedfachr = 0;     /*    "       "         */
                tmpfile->vcedfoff = 0;      /*    "       "         */
                curwdo->vcedwvced->edbuffer = tmpfile->vcedfbuf;
                curwdo->vcedwvced->edcrow = tmpfile->vcedfcur;
                curwdo->vcedwvced->edtrow = tmpfile->vcedftop;
                curwdo->vcedwvced->edtline = tmpfile->vcedftlin;
                curwdo->vcedwvced->edcline = tmpfile->vcedfclin;
                curwdo->vcedwvced->edaline = tmpfile->vcedfalin;
                curwdo->vcedwvced->edarow = tmpfile->vcedfarow;
                curwdo->vcedwvced->edcchar = tmpfile->vcedfchr;
                curwdo->vcedwvced->edachar = tmpfile->vcedfachr;
                curwdo->vcedwvced->edoffset = tmpfile->vcedfoff;
                vcfree(curwdo->vcedwvced->edwptr->title,vcdebug);
                curwdo->vcedwvced->edwptr->title = vcalloc(1,
                     strlen(curwdo->vcedwvced->edbuffer->bfname)+1,vcdebug);
                strcpy(curwdo->vcedwvced->edwptr->title,
                        curwdo->vcedwvced->edbuffer->bfname);
                curwdo->vcedwvced->edupval = VCEDUPDALL; /* Upate   */
                }                       /*                          */
            curwdo->vcedwvced->edmail = 0;  /* Clear mail           */ 
            }                           /*                          */
        if(curwdo->vcedwvced->edmail == VCEDNEXTFIL)    /* Next buf */
            {                           /*                          */
            curfile = vcedfiles;        /* Start at end of files    */
            while(curfile != (struct VCEDFILE *)0)  /* While more   */
                {                       /*                          */
                if(curfile->vcedfstat)  /* If file opened           */
                    if(curfile->vcedfbuf == curwdo->vcedwvced->edbuffer)
                        break;          /* If this is it break      */
                curfile = curfile->vcedfnext;   /* Next file        */
                }                       /*                          */
            if(curfile != (struct VCEDFILE *)0) /* If found         */
                {                       /*                          */
                if(curfile->vcedfnext != (struct VCEDFILE *)0)
                    tmpfile = curfile->vcedfnext;   /* Assign next  */
                else                    /*                          */
                    tmpfile = vcedfiles;/* Must loop to top         */
                }                       /*                          */
            if(tmpfile->vcedfbuf != curwdo->vcedwvced->edbuffer)
                {                       /* If buffer should change  */
                curfile->vcedftop = curwdo->vcedwvced->edtrow;
                curfile->vcedfcur = curwdo->vcedwvced->edcrow;
                curfile->vcedftlin = curwdo->vcedwvced->edtline;
                curfile->vcedfclin = curwdo->vcedwvced->edcline;
                curfile->vcedfarow = curwdo->vcedwvced->edarow;
                curfile->vcedfalin = curwdo->vcedwvced->edaline;
                curfile->vcedfchr = curwdo->vcedwvced->edcchar;
                curfile->vcedfachr = curwdo->vcedwvced->edachar;
                curfile->vcedfoff = curwdo->vcedwvced->edoffset;
                if(!tmpfile->vcedfstat) /* If not open              */
                    {                   /*                          */
                    tmpfile->vcedfbuf = vcedload(tmpfile->vcedfname,
                                                    NULLTEXT,VCEDFFIL);
                    tmpfile->vcedfstat = TRUE;  /* File opened      */
                    tmpfile->vcedftop = 0;      /* Starting values  */
                    tmpfile->vcedfcur = 0;      /*    "       "     */
                    tmpfile->vcedftlin = tmpfile->vcedfbuf->bffline;
                    tmpfile->vcedfclin = tmpfile->vcedfbuf->bffline;
                    tmpfile->vcedfarow = 0l;    /* Starting values  */
                    tmpfile->vcedfalin = (DBDP)0;/*   "       "     */
                    tmpfile->vcedfchr = 0;      /*    "       "     */
                    tmpfile->vcedfachr = 0;     /*    "       "     */
                    tmpfile->vcedfoff = 0;      /*    "       "     */
                    }                   /*                          */
                curwdo->vcedwvced->edbuffer = tmpfile->vcedfbuf;
                curwdo->vcedwvced->edcrow = tmpfile->vcedfcur;
                curwdo->vcedwvced->edtrow = tmpfile->vcedftop;
                curwdo->vcedwvced->edtline = tmpfile->vcedftlin;
                curwdo->vcedwvced->edcline = tmpfile->vcedfclin;
                curwdo->vcedwvced->edaline = tmpfile->vcedfalin;
                curwdo->vcedwvced->edarow = tmpfile->vcedfarow;
                curwdo->vcedwvced->edcchar = tmpfile->vcedfchr;
                curwdo->vcedwvced->edachar = tmpfile->vcedfachr;
                curwdo->vcedwvced->edoffset = tmpfile->vcedfoff;
                vcfree(curwdo->vcedwvced->edwptr->title,vcdebug);
                curwdo->vcedwvced->edwptr->title = vcalloc(1,
                     strlen(curwdo->vcedwvced->edbuffer->bfname)+1,vcdebug);
                strcpy(curwdo->vcedwvced->edwptr->title,
                        curwdo->vcedwvced->edbuffer->bfname);
                curwdo->vcedwvced->edupval = VCEDUPDALL; /* Upate   */
                }                       /*                          */
            else                        /*                          */
                {                       /*                          */
                if(curwdo->vcedwvced->edswptr != (WPTR)0)  
                    watsay(curwdo->vcedwvced->edswptr,0,1,
                                    "No Other Buffers             ");
                curwdo->vcedwvced->edsline = 1;/* Clear status line */
                }                       /*                          */
            curwdo->vcedwvced->edmail = 0;  /* Clear mail           */ 
            }                           /*                          */
        if(curwdo->vcedwvced->edmail == VCEDNEWWDO)     /* New wdo  */
            {                           /*                          */
            curwdo->vcedwvced->edmail = 0;  /* Clear mail           */ 
            }                           /*                          */
        if(curwdo->vcedwvced->edmail == VCEDNEXTWDO)    /* Next wdo */
            {                           /*                          */
            curwdo->vcedwvced->edmail = 0;  /* Clear mail           */ 
            }                           /*                          */
        if(curwdo->vcedwvced->edmail == VCEDSAVE)   /* Save files   */
            {                           /*                          */
            curfile = vcedfiles;        /* Start at end of files    */
            while(curfile != (struct VCEDFILE *)0)  /* While more   */
                {                       /*                          */
                if(curfile->vcedfstat)  /* If file opened           */
                    vcedsave(curfile->vcedfbuf);/* Save file        */
                curfile = curfile->vcedfnext;   /* Next file        */
                }                       /*                          */
            break;                      /* Exit program             */
            }                           /*                          */
        if(curwdo->vcedwvced->edmail == VCEDABORT)  /* Abort editor */
            {                           /*                          */
            changed = FALSE;            /* Set no files changed     */
            curfile = vcedfiles;        /* Start at end of files    */
            while(curfile != (struct VCEDFILE *)0)  /* While more   */
                {                       /*                          */
                if(curfile->vcedfstat)  /* If file opened           */
                    if(curfile->vcedfbuf->bfchange) /* If file chg. */
                        changed = TRUE; /* Set flag                 */
                curfile = curfile->vcedfnext;   /* Next file        */
                }                       /*                          */
            if(changed)                 /* If any files changed     */
                {                       /* Ask if sure              */
                if(askmsg(NULLTEXT,"Abort - Are You Sure (Y/N) ",'n'))
                    break;              /* If sure abort program    */
                curwdo->vcedwvced->edmail = 0;  /* Clear abort mail */ 
                }                       /*                          */
            else                        /*                          */
                break;                  /* Exit editor              */
            }                           /*                          */
        }                               /*                          */
#ifdef VCEDFULL
    vcedunend(curwdo->vcedwvced);       /* Stop undo / redo         */
    vcedblkend(curwdo->vcedwvced);      /* Stop block operations    */
#endif
    curfile = vcedfiles;                /* Start at end of files    */
    while(curfile != (struct VCEDFILE *)0)  /* While more           */
        {                               /*                          */
        tmpfile = curfile->vcedfnext;   /* Next file                */
        if(curfile->vcedfstat)          /* If file opened           */
            vcedkill(curfile->vcedfbuf);/* Close buffer             */
        vcfree(curfile,vcdebug);        /* Free link                */
        curfile = tmpfile;              /* Next file                */
        }                               /*                          */
    curwdo = vcedwdos;                  /* Start at top             */
    while(curwdo != (struct VCEDWDO *)0)/* While more windows       */
        {                               /*                          */
        tmpwdo = curwdo->vcedwnext;     /* Next window              */
        if(curwdo->vcedwstat)           /* If window opened         */
            vcedclose(curwdo->vcedwvced);/* Close window            */
        vcfree(curwdo,vcdebug);         /* Free link                */
        curwdo = tmpwdo;                /* Next window              */
        }                               /*                          */
    vcend(CLOSE);                       /* Quit Vitamin C           */
    }                                   /* ------------------------ */

COUNT vcedaskfil()
    {                       /* ------------------------------------ */
    WPTR fwptr;             /* Current window                       */
    COUNT key;              /* Key returned from readgets           */
    WPTR wxopen();          /* Declare functions used               */
    TEXT *vcalloc();        /*    "        "      "                 */
    empty(vceddfil,30);                 /* Empty file name          */
    fwptr = wxopen(vcterm.rows-1,0,vcterm.rows-1,   /* Open window  */
            min(39,(vcterm.cols-1)),NULL,ACTIVE|SCROLL|CURSOR,0,0);
    atsay(0,1,"File to Edit:");         /* Prompt                   */
    atgetc(0,15,vceddfil,NULLTEXT,12,FLDBLANK+FLDSTRING,NULLTEXT);
    key = readgets();                   /* Get file name            */
    trim(vceddfil);                     /* Trim file name           */
    wclose(fwptr);                      /* Close window             */
    return(key);                        /* Return O.K.              */
    }                                   /* ------------------------ */


