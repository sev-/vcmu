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
*   Name            gettest.c
*                                   
*   Description     Test new get options
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

TEXT name[40];              /* Name variable                        */

main()
    {
    TEXT address[60];       /* Address variable                     */
    TEXT city[15];          /* City variable                        */
    TEXT phone[11];         /* Phone Number                         */
    COUNT nbr;              /* Number to use to display length      */
    WPTR wptr,wxopen();     /* Declare window functions and variable*/
    COUNT prtval();         /* Validation function                  */
    vcstart(CLRSCRN);                   /* Start and clear screen   */
    wptr = wxopen(0,0,vcterm.rows-1,vcterm.cols-1,/* Open a window  */
                    vcterm.tmname,BORDER+ACTIVE+CENTER+CURSOR,0,0);
    statlin(wptr,wrows(wptr)-2,5,-1);   /* Setup Status line        */
    empty(name,40);                     /*   "      "               */
    empty(address,60);                  /*   "      "               */
    empty(city,15);                     /*   "      "               */
    empty(phone,11);                    /*   "      "               */
    strcpy(phone,"1234567890");         /* Set Default value        */
    atsay(3,5,"Name:");                 /* Print prompts            */
    atsay(5,5,"Address:");              /*    "     "               */
    atsay(7,5,"City:");                 /*    "     "               */
    atsay(9,5,"Phone:");                /*    "     "               */
    /* ------------------------------------------------------------ */
    /*                      Enter Input Routines                    */
    /* ------------------------------------------------------------ */
    vcxxfld(3,11,name,NULLTEXT,FLDNOALLOC+FLDBLANK,FLDSTRING+FLDLTOR,"Name",
            prtval,"Enter Name",NULLTEXT,-1,NULLTEXT,1);
    vcxxfld(5,14,address,NULLTEXT,FLDTRIM,FLDSTRING+FLDLTOR,"Address",
            NULLFUNC,"Enter Address",NULLTEXT,-1,NULLTEXT,2);
    vcxxfld(7,11,city,NULLTEXT,FLDCLEAR,FLDSTRING+FLDLTOR,"City",NULLFUNC,
            "Enter City",NULLTEXT,-1,NULLTEXT,3);
    vcxxfld(9,11,phone,"(999) 999-9999",FLDNOPIC,FLDSTRING+FLDLTOR,"Phone",
            NULLFUNC,"Enter Phone",NULLTEXT,-1,NULLTEXT,4);
    readgets();                         /* Read gets                */
    nbr = strlen(address);              /* Find length of address   */
    atsay(11,5,"Length of Address = "); /* Print prompt             */
    atsaynum(11,25,&nbr,"###",FLDINT);  /* Print length             */
    nbr = strlen(city);                 /* Find length of City      */
    atsay(13,5,"Length of City = ");    /* Print prompt             */
    atsaynum(13,22,&nbr,"###",FLDINT);  /* Print length             */
    atsay(15,5,"Phone Contains");       /* Print prompt             */
    atsay(15,21,phone);                 /* Print phone variable     */
    getone();                           /* Pause to look at screen  */
    vcend(CLOSE);                       /* End and close all windows*/
    }                                   /* ------------------------ */

COUNT prtval(fld,table)
TEXT *fld;                  /* Value of current field               */
GETTABLE *table;            /* Pointer to current gettable          */
    {                       /* ------------------------------------ */
    askmsg("Name Contains",name,0);     /* Display orginal location */
    return(GOOD);                       /* Return field valid       */
    }                                   /* ------------------------ */
