/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .1 on 9/1/90 at 12:31:00
*
*   Name            Editor application  --  Standard header file
*
*   Description     
*
**/

                            /* Maximum number of key for record     */
#define VCEDMAXREC 250

#define MAXUNDO 100         /* Maximum undo commands                */
#define MAXLIN 1024         /* Maximum line to evaluate             */
#define CUTBUFS  3          /* Maximum number to cut buffers        */
#define BKSPNODEL           /* Backspace does not delete in OverWrit*/

/* Buffer control values */
#define VCEDFBUF BIT1
#define VCED2BUF BIT2
#define VCEDFFIL BIT3
#define VCED2FIL BIT4
#define VCEDREQ  BIT5

/* Editor control values */
#define VCEDNOSHOW BIT0
#define VCEDOVER BIT1
#define VCEDSTATUS BIT2

/* Editor update values */
#define VCEDUPDLINE BIT0
#define VCEDUPDCHAR BIT1
#define VCEDUPDEOL BIT2
#define VCEDUPDPLINE BIT3
#define VCEDUPDPCHAR BIT4
#define VCEDUPDPEOL BIT5
#define VCEDUPDALL BIT6

                            /* ------- Editor Mail Values --------- */   
                            /* These cause vcedit to exit           */
#define VCEDSAVE  9999
#define VCEDABORT 9998
                            /* These are used by vceditor           */
#define VCEDNEWWDO 9996
#define VCEDNEXTWDO 9995
#define VCEDNEWFIL 9994
#define VCEDNEXTFIL 9993
                            /* These are used by undo / redo        */
#define VCEDREDO 4444
#define VCEDUNDO 3333

#define VCEDUNRWT 1
#define VCEDUNINS 2
#define VCEDUNDEL 3
#define VCEDUNADD 4
#define VCEDUNWRK 5

typedef struct
    {                       /* ------------------------------------ */
    COUNT linlen;           /* Default line length                  */
    COUNT pages;            /* Number of pages to keep in memory    */
    COUNT slots;            /* Number of slots per page             */
    COUNT softret;          /* Soft return character                */
    COUNT hardret;          /* Hard return character                */
    COUNT justret;          /* Justified return (future use)        */
    COUNT realtabs;         /* Use real tabs                        */
    COUNT tabsize;          /* Tab size                             */
    COUNT tabchr;           /* Tab character                        */
    COUNT tabspace;         /* Tab space character                  */
    COUNT shiftleft;        /* Shift left and right value           */
    COUNT shiftup;          /* Shift up and down value              */
    COUNT dftrmar;          /* Default right margin                 */
    COUNT dftlmar;          /* Default left margin                  */
    COUNT dispctrl;         /* Display control characters           */
    COUNT bckupfil;         /* Make file backup                     */
    } VCEDVAL;              /* ------------------------------------ */

typedef struct
    {                       /* ------------------------------------ */
    DBDP lnext;             /* Next line                            */
    DBDP lprev;             /* Previous line                        */
    COUNT lstatus;          /* Line status byte                     */
    COUNT lused;            /* Number of characters used            */
    COUNT lsize;            /* Size of allocated line               */
    TEXT ltext[1];          /* Actual line of information           */
    } VCEDLINE;             /* ------------------------------------ */

typedef struct 
    {                       /* ------------------------------------ */
    TEXT *bfname;           /* File name for buffer                 */
    TEXT *bfbuffer;         /* Write back to buffer                 */
    COUNT bflinelen;        /* Line length of this file             */
    DBP bfdnum;             /* Database Number for buffer           */
    DBDP bffline;           /* First line of file                   */
    DBDP bfbline;           /* Bottom line of file                  */
    LONG bfnlines;          /* Number of lines                      */
    COUNT bfctrl;           /* Current control values               */
    COUNT bfchange;         /* Has buffer been changed              */
    COUNT bfperm;           /* File permission when opened          */
    } VCEDBUF;              /* ------------------------------------ */

typedef struct
    {                       /* ------------------------------------ */
    WPTR edwptr;            /* Window pointer if active             */
    WPTR edswptr;           /* Pointer to status window (if used)   */
    COUNT edkey[3];         /* Last three keys pressed              */
    COUNT edmode;           /* Editor mode                          */
    COUNT edmail;           /* Slot for inter program communication */
    COUNT edsline;          /* Status line clear flag               */
    VCEDBUF *edbuffer;      /* Pointer to buffer for file           */
    COUNT edrmar;           /* Right margin                         */
    COUNT edlmar;           /* Left margin                          */
    DBDP edtline;           /* Top line of buffer in window         */
    DBDP edcline;           /* Current line                         */
    COUNT edcchar;          /* Current character                    */
    COUNT edoffset;         /* Offset of file in window             */
    LONG edtrow;            /* Row in file of top line              */
    LONG edcrow;            /* Row location of current line         */
    DBDP edaline;           /* Anchor line                          */
    DBDP edarow;            /* Anchor row                           */
    COUNT edachar;          /* Anchor character                     */
    COUNT edrval;           /* Repeat value                         */
    COUNT edupval;          /* Update value for screen              */
    COUNT edurow;           /* Upper row for window                 */
    COUNT educol;           /* Upper column for window              */
    COUNT edlrow;           /* Lower row for window                 */
    COUNT edlcol;           /* Lower column for window              */
    COUNT edctrl;           /* Control value for window             */
    TEXT *edtitle;          /* Title for window (if needed)         */
    } VCED;                 /* ------------------------------------ */

struct VCEDUNLINE
    {                       /* ------------------------------------ */
    struct VCEDUNLINE *undolast;    /* Pointer to next line         */
    COUNT undooper;         /* Operation for this line              */
    DBDP undoline;          /* Address of this line                 */
    DBDP undoprev;          /* Address of prev line                 */
    DBDP undonext;          /* Address of next line                 */
    VCEDBUF *undolbuf;      /* Buffer for this line                 */
    DBDP undolloc;          /* Address of line in undo buffer       */
    };                      /* ------------------------------------ */

typedef struct
    {                       /* ------------------------------------ */
    COUNT undohead;         /* Head of undo list                    */
    COUNT undotail;         /* Tail of undo list                    */
    COUNT undoactive;       /* Set to true during undo operation    */
    VCEDBUF *undobuf;       /* Pointer to buffer for undo           */
    struct VCEDUNLINE *undostruct[MAXUNDO];/* Undo list             */
    VCED *undovced[MAXUNDO];/* Control structure before command     */
    } VCEDUNSTR;            /* ------------------------------------ */

struct VCEDCUTBUF
    {                       /* ------------------------------------ */
    struct VCEDCUTBUF *cutnext;     /* Next line in cut buffer      */
    DBDP cutlloc;           /* Address of line in undo buffer       */
    };                      /* ------------------------------------ */

typedef struct
    {                       /* ------------------------------------ */
    VCEDBUF *cutbuf;        /* Pointer to buffer for undo           */
    TEXT *cutwork;          /* Work buffer for operations           */
    struct VCEDCUTBUF *cuthead[CUTBUFS];   /* Head of cut buffers   */
    struct VCEDCUTBUF *cuttail[CUTBUFS];   /* Tail of cut buffers   */
    } VCEDCUTSTR;           /* ------------------------------------ */

typedef struct 
    {                       /* ------------------------------------ */
    TEXT *cmdname;          /* Textual name for command             */
    COUNT cmdkey;           /* Key pressed that executes command    */
    PFI cmdloc;             /* Function to execute                  */
    } VCEDCMD;              /* ------------------------------------ */

#ifndef VCEDVARS

extern VCEDVAL vcedval;
extern VCEDCMD vcedcmds[];
extern TEXT vcedfbuf[];
extern TEXT vcedibuf[];

#ifdef VCEDFULL
extern VCEDUNSTR *vcedustr;
extern VCEDCUTSTR *vcedscrap;
extern COUNT vcedrecstat;
extern COUNT vcedrkeys[];
extern COUNT vcedcrkey;
#endif

#endif
