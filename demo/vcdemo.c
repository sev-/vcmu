/**
*
*   Vitamin C Multi-User version 1.%R%
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .%L% on %G% at %U%
*
*   Name            vcdemo -- Vitamin C demo program
*
*   Description     Vitamin C demo                                
*
*   Return Value                       
*                                    
**/                                 

#define VCKEY_DEFS                      /* Keyboard defines         */
#define VCGET_DEFS                      /* Get defines              */
#define SEL_DEFS                        /* Selection Set defines    */
#include <vcstdio.h>                    /* Include stdio            */

struct                                  /* Struct for variables     */
    {                                   /*                          */
    long date;                          /* Dates stored as longs    */
    char name[31];                      /* Character Strings        */
    char address[31];                   /*     "        "           */
    char city[16];                      /*     "        "           */
    char state[3];                      /* Uppercase only           */
    char zip[11];                       /* Numbers with pictures    */
    char phone[15];                     /* Fields with separators   */
    float cost;                         /* Float values             */    
    int users;                          /* Integer values           */
    char operating[2];                  /* Selection Sets           */
    long lval;                          /* Long data types          */
    double dval;                        /* Double data types        */
    short sval;                         /* short data types         */
    } ed;

TEXT *oper[] =                          /* Selection Set            */
    {
    (TEXT *)"12 27 4 Operating System",(TEXT *)"",/* Position 14,25 */
    (TEXT *)"PC/MS DOS",(TEXT *)"1",            /* First selection  */
    (TEXT *)"Unix System V",(TEXT *)"2",        /* Second   "       */
    (TEXT *)"Xenix V",(TEXT *)"3",              /* Third    "       */
    (TEXT *)"Digital VMS",(TEXT *)"4",          /* Fourth   "       */
    NULL
    };

main()
    {
    TEXT date[9],ttltime[12];           /* Date and Total time      */ 
    TEXT offtime[12],ontime[12];        /* Starting and ending time */
    TEXT buf[81];                       /* Buffer for formatting    */
    COUNT day,month,year,century;       /* Numbers for date conv.   */
    WPTR mainwdo,timewdo;               /* Window pointer variables */
    SELSET *selset,*bldxset();          /* Selection Set variables  */
    VOID timeloop();                    /* Declare loop functioin   */
    VOID  allcaps();                    /* Declare Valdation func.  */
    COUNT valdate();                    /*    "        "      "     */
    COUNT vchelp();                     /* Declare help function    */
    FILE *fopen();                      /* Declare functions        */
    WPTR wxopen();                      /*    "       "             */
    LONG tojul();                       /*    "       "             */
    VOID terror(),empty();              /*    "       "             */
    COUNT tocaps(),vcstart();           /*    "       "             */
    PFI setkeytrap(),setloop();         /*    "       "             */
    COUNT wdokey(),hopen(),sethelp();   /*    "       "             */
    TEXT *strcpy();                     /*    "       "             */
    VOID box(),xatsay(),atsay();        /*    "       "             */
    COUNT getdate(),xatgetc();          /*    "       "             */
    VOID gettime(),xatget(),erase();    /*    "       "             */
    COUNT dayofwk(),elapstim();         /*    "       "             */
    COUNT hclose(),statlin();           /*    "       "             */
    VOID at(),vcend(),intdate();        /*    "       "             */
    COUNT readgets(),vctrap();          /*    "       "             */
    TEXT *day_name(),*month_name();     /*    "       "             */
    vcstart(CLRSCRN);                   /* Start Vitamin C          */
    spkey.fld_blank = 5002;             /* F3 = blank field         */
    spkey.fld_deof = 5003;              /* F4 = delete end of field */
    setkeytrap(vctrap);                 /* Set keytrap function     */
    mainwdo = wxopen(0,0,20,79,NULL,    /* Open borderless window   */
              CURSOR+NOADJ,0,0);        /* with a cursor, inactive  */
    wdokey(F2);                         /* Set Wdo-Adjust key to F2 */
    if(hopen("vcdemo.msg","vcdemo.ndx"))/* Open help files          */
        terror("Cannot open help files");   /* If error exit        */
    empty(ed.name,31);                  /* Blank and NULL terminate */
    empty(ed.address,31);               /*   "    "   "       "     */ 
    empty(ed.city,16);                  /*   "    "   "       "     */
    empty(ed.state,3);                  /*   "    "   "       "     */
    empty(ed.zip,11);                   /*   "    "   "       "     */ 
    empty(ed.phone,15);                 /*   "    "   "       "     */
    empty(ed.operating,2);              /*   "    "   "       "     */
    century=getdate(date);              /* Get current date         */    
    ed.date = tojul(date);              /* Convert date to julian   */
    selset = bldxset(oper);             /* Create Selection Set     */
    sethelp(vchelp);                    /* Set Help Function        */
    /*--------------------------------------------------------------*/
    /*          DRAW BOXES, DISPLAY FIELDS AND SCREEN SETUP         */
    /*--------------------------------------------------------------*/
    box(0,0,2,79,DOUBLE,vc.cyan);       /* Draw box from 0,0 to 2,79*/
    xatsay(1,25,                                    /* Print Msg    */
        "Vitamin C Demonstrator Program",    /* at 1,25 on   */
        vc.red+vc.bold);                            /* current wdo  */
    box(3,0,20,79,SINGLE,vc.green);     /* Draw another box         */
    atsay(4,64,"Date");                 /* Date prompt              */
    atsay(6,3,"Name:");                 /* Name prompt              */
    atsay(8,3,"Address:");              /* Address prompt           */
    atsay(10,3,"City:");                /* City prompt              */
    atsay(10,33,"State:");              /* State prompt             */
    atsay(10,48,"Zip:");                /* Zip prompt               */
    atsay(12,3,"Phone:");               /* Phone prompt             */         
    atsay(14,3,"Operating System:");    /* Operating system prompt  */
    atsay(14,28,"No. of Users:");       /* Number of users          */
    atsay(14,51,"Cost:");               /* Cost of Computer         */
    box(16,1,18,78,1,vc.dflt);          /* Data type box            */
    atsay(16,16,"Input Numeric Data Types (even user defined)");
    atsay(17,3,"Short:");               /* Short prompt             */
    atsay(17,28,"Long:");               /* Long prompt              */
    atsay(17,51,"Double:");             /* Double prompt            */
    xatsay(20,5,                         /* Print Instructions       */
        "<F1> Enter/Exit HELP    <F2> Move Help Window (when open)  <ESC> Exit",
        vc.white*vc.bg);
    gettime(ontime);                    /* Get the time             */
    strcpy(ttltime,ontime);             /* Copy time to ttltime     */
    intdate(date,&month,&day,&year);    /* Convert Date to integers */
    sprintf(buf,"Today Is: %s, %s %d, %d%d.",       /* Format to    */
        day_name(dayofwk(date)),month_name(month),  /* buffer day   */
        (int)day,(int)century,(int)year);           /* name & year  */
    timewdo = wxopen(21,0,23,79,NULL,   /* Open window for clock    */
              BORDER+ACTIVE+NOADJ,0,0); /* and date                 */
    wxatsay(timewdo,0,1,buf,vc.brown);  /* Print day on the screen  */
    wxatsay(timewdo,0,55,"Current Time:",vc.brown);  /* Time message*/
    timeloc(timewdo,0,69,vc.brown);     /* Set Time location        */
    setloop(timeloop);                  /* Set loop function        */
    timeloop();                         /* Call to print time       */
    wselect(mainwdo);                   /* Select Main Window       */
    statlin(NULL,4,3,msgattr);          /* Print status line at 4,3 */ 
    /*--------------------------------------------------------------*/
    /*   ENTER VARIABLES, LOCATIONS, VALIDATION, STATUS, AND HELP   */
    /*--------------------------------------------------------------*/
    xatgetc(4,70,&(ed.date),DATEEDIT,valdate,       /* Get date     */
        "Enter today's date in MM/DD/YY format.",   /*              */
        "DATE",vc.dflt,vc.dflt,vc.dflt,             /*              */
        FLDJULDATE+FLDBLANK+FLDNORET,NULLTEXT);     /*              */
    xatget(6,13,ed.name,                            /* Get name     */
        "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULLFUNC,  /*              */
        "Enter name as 'LASTNAME, FIRSTNAME'.",     /*              */
        "NAME",vc.dflt,vc.dflt);                    /*              */
    xatget(8,13,ed.address,                         /* Get Address  */
        "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULLFUNC,  /*              */
        "Enter street address.","ADDRESS",          /*              */
        vc.dflt,vc.dflt);                           /*              */
    xatget(10,13,ed.city,"xxxxxxxxxxxxxxx",NULLFUNC,/* Get city     */
        "Enter the city.","CITY",                   /*              */
        vc.dflt,vc.dflt);                           /*              */
    xatget(10,40,ed.state,"AA",NULLFUNC,            /* Get state    */
        "Enter a two letter state abbreviation.",   /*              */
        "STATE",vc.dflt,vc.dflt);                   /*              */
    xatget(10,53,ed.zip,"99999-9999",NULLFUNC,      /* Get zip      */
        "Enter a five or nine digit zip code.",     /*              */
        "ZIP",vc.dflt,vc.dflt);                     /*              */
    xatget(12,13,ed.phone,"(999) 999-9999",NULLFUNC,/* Get phone    */
        "Enter phone number and area code.",        /*              */
        "PHONE",vc.dflt,vc.dflt);                   /*              */
    xatgetc(14,21,ed.operating,"#",NULLFUNC,        /* Get oper.    */
        "Choose Operating System",                  /*              */
        "OPERATING",vc.dflt,vc.dflt,vc.dflt,        /*              */
        FLDSTRING+FLDBLANK+FLDNORET,(TEXT *)selset);/*              */
    xatgetc(14,42,&(ed.users),"###",NULLFUNC,       /* Get users    */
        "Enter the number of users.",               /*              */
        "USERS",vc.dflt,vc.dflt,vc.dflt,            /*              */
        FLDINT+FLDBLANK+FLDNORET,NULLTEXT);         /*              */
    xatgetc(14,57,&(ed.cost),"$###,###.##",NULLFUNC,/* Get cost     */
        "Enter Cost of Computer.",                  /*              */
        "COST",vc.dflt,vc.dflt,vc.dflt,             /*              */
        FLDFLOAT+FLDBLANK+FLDNORET,NULLTEXT);       /*              */
    xatgetc(17,10,&(ed.sval),"99",NULLFUNC,         /* Get short    */
        "Enter Short Number.",                      /*              */
        "DATATYPES",vc.dflt,vc.dflt,vc.dflt,        /*              */
        FLDSHORT+FLDBLANK+FLDNORET,NULLTEXT);       /*              */
    xatgetc(17,34,&(ed.lval),"#######",NULLFUNC,    /* Get long     */
        "Enter Long Number.",                       /*              */
        "DATATYPES",vc.dflt,vc.dflt,vc.dflt,        /*              */
        FLDLONG+FLDBLANK+FLDNORET,NULLTEXT);        /*              */
    xatgetc(17,59,&(ed.dval),"#######.##",NULLFUNC, /* Get Double   */
        "Enter Double Number.",                     /*              */
        "DATATYPES",vc.dflt,vc.dflt,vc.dflt,        /*              */
        FLDDOUBLE+FLDBLANK,NULLTEXT);               /*              */
    wshow(mainwdo);                     /* Show Main Window         */
                                        /*--------------------------*/
    readgets();                         /*     READ THE SCREEN      */
                                        /*--------------------------*/
    hclose();                           /* Close help files         */
    setloop(NULLFUNC);                  /* Loop function not wanted */
    gettime(offtime);                   /* Get ending time          */
    elapstim(ttltime,offtime);          /* Calculate difference     */
    ttltime[8] = '\0';                  /* Cut off tens of seconds  */
    offtime[8] = '\0';                  /* Cut off tens of seconds  */
    ontime[8] = '\0';                   /* Cut off tens of seconds  */
    sprintf(buf,"Begin Time: %s   End Time: %s   Elapsed Time: %s",
        ontime,offtime,ttltime);        /* Format string for output */
    wselect(timewdo);                   /* Select time window       */
    erase();                            /* Erase current window     */
    atsay(0,6,buf);                     /* At 0,6 display string    */
    getone();                           /* Wait for any key         */
    vcend(CLOSE);                       /* Exit and close windows   */ 
    }

/*------------------------------------------------------------------*/
/*--------------------- Simple Validation Program ------------------*/
/*------------------------------------------------------------------*/

COUNT tocaps(fld)
TEXT *fld;
    {
    VOID allcaps();
    allcaps(fld);
    return(GOOD);
    }




