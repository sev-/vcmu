/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 9/1/90 at 00:28:33
*
*   Name            vcterm.h  --  
*
*   Description     
*
*
**/


struct WTERM
    {                       /* ------------------------------------ */
    TEXT *wtname;           /* Terminal name                        */
    COUNT rows;             /* Rows on terminal                     */
    COUNT cols;             /* Columns on terminal                  */
    COUNT sg;               /* Blank characters left by so or se    */
    COUNT ug;               /* Blank characters left by ue or us    */
    COUNT cg;               /* Characters left blank by ct (n)cg    */
    COUNT gg;               /* Characters taken by GS and GE (GG)   */
    COUNT bb;               /* Characters taken by bl & be (n)bb    */
    COUNT ig;               /* Character taken by it & ie (n)ig     */
    COUNT zd;               /* Delay used on keyrdy reads  (zd)     */
    COUNT zk;               /* Disable keyrdy function (zk)         */
    COUNT zc;               /* Character to wait on read (zc)       */
    COUNT zt;               /* Time to wait on key read (zt)        */
    COUNT am;               /* Terminal has automatic margins       */
    COUNT bs;               /* Terminal can backspace with ^H       */
    COUNT ms;               /* Can move in Standout (or any mode)   */
    COUNT xs;               /* Standout not erased by overwrite(hp) */
    COUNT mc;               /* Magic Cookie problem                 */ 
    UCOUNT sp;              /* Terminal has attr that requires space*/
    struct KEYTBLNODE *wthead;   /* Head of screen translate table  */
    struct KEYTBLNODE *wvcurrent;/* Current node screen table       */
    struct PRECOMP wvcursor;/* Cursor Addressing Pre Compile(cm)    */
    struct PRECOMP wvcolor; /* Color Monitor Pre Compile (ct)       */
    struct KEYLBL *wtkeylbl;/* Pointer to first key label           */
    struct BODR wtborder[3];/* Border structure for terminal        */
    TEXT *wtkeyblk[60];     /* Key translate table                  */
    COUNT wtattrst;         /* Current attribute status             */
    COUNT wtgraphon;        /* Graphics Mode (On = 1 | Off = 0)     */
    COUNT wtcharset;        /* Current Character set                */
    COUNT wtstack[30][3];   /* Stack used to store characters       */
    COUNT wtcurpos;         /* Current stack location               */
    COUNT wtfirst;          /* First value (of cm and ct controls)  */
    COUNT wtsecond;         /* Second value (of cm and ct controls) */
    COUNT wtstatus;         /* Current status of ct and cm controls */
    COUNT wtoffset;         /* Offset used at varies times in cm trn*/
    };                      /* ------------------------------------ */
