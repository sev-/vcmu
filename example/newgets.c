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
*   Name            newgets.c
*                                   
*   Description     Test new get functions
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT put_name(),put_id(),goto_name(),goto_id();

main()
    {
    TEXT password[10];      /* Password variable                    */
    double number;          /* Double variable                      */
    TEXT name[40];          /* Name variable                        */
    TEXT address[60];       /* Address variable                     */
    TEXT city[15];          /* City variable                        */
    TEXT field[10];         /* For goto field                       */
    TEXT place1[10];        /* Variable to insert                   */
    TEXT place2[10];        /* Variable to insert                   */
    TEXT fname1[10];        /* Field name                           */
    TEXT fname2[10];        /* Field name                           */
    COUNT fid1,fid2;        /* Field id                             */
    COUNT offset;           /* Offset into field                    */
    COUNT nofset;           /* Offset into field                    */
    WPTR wptr,wxopen();     /* Window pointer for main window       */
    vcstart(CLRSCRN);                   /* Start and clear screen   */
    wptr = wxopen(0,0,vcterm.rows-1,vcterm.cols-1,/* Open a window  */
		    vcterm.tmname,SHADOW+BORDER+ACTIVE+CENTER+CURSOR,0,0);
    statlin(wptr,wrows(wptr)-2,5,-1);   /* Setup Status line        */
    empty(password,10);                 /* Empty variables          */
    empty(name,40);                     /*   "      "               */
    empty(address,60);                  /*   "      "               */
    empty(city,15);                     /*   "      "               */
    empty(field,10);                    /*   "      "               */
    empty(place1,10);                   /*   "      "               */
    empty(place2,10);                   /*   "      "               */
    empty(fname1,10);                   /*   "      "               */
    empty(fname2,10);                   /*   "      "               */
    offset = 0;                         /*   "      "               */
    nofset = 0;                         /*   "      "               */
    fid1 = fid2 = 0;                    /*   "      "               */
    atsay(1,5,"Password:");             /* Display prompts          */
    atsay(3,5,"Name:");                 /*    "       "             */
    atsay(5,5,"Address:");              /*    "       "             */
    atsay(7,5,"City:");                 /*    "       "             */
    atsay(11,5,"Place");                /*    "       "             */
    atsay(11,21,"into field name");     /*    "       "             */
    atsay(13,5,"Goto field name");      /*    "       "             */
    atsay(13,31,"column");              /*    "       "             */
    atsay(15,5,"Place");                /*    "       "             */
    atsay(15,21,"into field number");   /*    "       "             */
    atsay(17,5,"Goto field number");    /*    "       "             */
    atsay(17,26,"column");              /*    "       "             */
    atsay(19,5,"Enter Number");         /*    "       "             */
    /* ------------------------------------------------------------ */
    /*                      Enter Input Routines                    */
    /* ------------------------------------------------------------ */
    vcxxfld(1,15,password,"xxxxxxxxx",(COUNT)FLDPASSWD,FLDSTRING+FLDLTOR,
            "Password",NULLFUNC,
            "Enter Password",NULLTEXT,-1,NULLTEXT,1);
    vcxxfld(3,11,name,NULLTEXT,-1,FLDSTRING+FLDLTOR,"Name",NULLFUNC,
            "Enter Name",NULLTEXT,-1,NULLTEXT,1);
    vcxxfld(5,14,address,NULLTEXT,-1,FLDSTRING+FLDLTOR,"Address",NULLFUNC,
            "Enter Address",NULLTEXT,-1,NULLTEXT,2);
    vcxxfld(7,11,city,NULLTEXT,-1,FLDSTRING+FLDLTOR,"City",NULLFUNC,
            "Enter City",NULLTEXT,-1,NULLTEXT,3);
    vcxxfld(11,11,place1,NULLTEXT,-1,FLDSTRING+FLDLTOR,"Place1",NULLFUNC,
            "Enter Value",NULLTEXT,-1,NULLTEXT,4);
    vcxxfld(11,37,fname1,NULLTEXT,-1,FLDSTRING+FLDLTOR,"Fname1",put_name,
            "Enter Field Name",NULLTEXT,-1,NULLTEXT,5);
    vcxxfld(13,21,fname2,NULLTEXT,-1,FLDSTRING+FLDLTOR,"Fname2",NULLFUNC,
            "Enter Field Name",NULLTEXT,-1,NULLTEXT,6);
    vcxxfld(13,38,&offset,"##",FLDSPACE,FLDINT+FLDRTOL,"Offset",goto_name,
            "Enter Offset",NULLTEXT,-1,NULLTEXT,7);
    vcxxfld(15,11,place2,NULLTEXT,-1,FLDSTRING+FLDLTOR,"Place2",NULLFUNC,
            "Enter Value",NULLTEXT,-1,NULLTEXT,8);
    vcxxfld(15,40,&fid1,"##",-1,FLDINT+FLDRTOL,"Fid1",put_id,
            "Enter Field Id",NULLTEXT,-1,NULLTEXT,9);
    vcxxfld(17,23,&fid2,"##",FLDSPACE,FLDINT+FLDRTOL,"Fid2",NULLFUNC,
            "Enter Field Id",NULLTEXT,-1,NULLTEXT,10);
    vcxxfld(17,33,&nofset,"##",FLDBLANK+FLDSPACE+FLDZEROS,FLDINT+FLDRTOL,
            "Nofset",goto_id,"Enter Offset",NULLTEXT,-1,NULLTEXT,11);
    vcxxfld(19,18,&number,"-######.##",FLDBLANK+FLDSPACE+FLDASSUME,
            FLDDOUBLE+FLDRTOL,"Number",NULLFUNC,
            "Enter Number",NULLTEXT,-1,NULLTEXT,11);
    vcfldgo((GETTABLE *)0,"Place1",0);  /* Start at field Place1    */
    readgets();                         /* Read gets                */
    vcend(CLOSE);                       /* End and close all windows*/
    }                                   /* ------------------------ */

COUNT put_name(fld,table)
TEXT *fld;                  /* Value of current field               */
GETTABLE *table;            /* Pointer to current gettable          */
    {                       /* ------------------------------------ */
    TEXT *vcfldget();       /* Declare functions used               */
    TEXT *ttrim();          /*    "        "      "                 */
    vcfldput(table,ttrim(fld),vcfldget(table,"Place1",FLDLOCTEMP),
            FLDLOCTEMP+FLDLOCREAL+FLDLOCUPDATE);
    return(GOOD);                       /* Return field valid       */
    }                                   /* ------------------------ */

COUNT goto_name(fld,table)
TEXT *fld;                  /* Value of current field               */
GETTABLE *table;            /* Pointer to current gettable          */
    {                       /* ------------------------------------ */
    COUNT cnt;              /* Offset                               */
    TEXT *vcfldget();       /* Declare functions used               */
    TEXT *ttrim();          /*    "        "      "                 */
    if(table->tkeypress == spkey.fld_ret)   /* If return entered    */
        {                               /*                          */
        cnt = atoi(fld);                /* Convert offset           */
        vcfldgo(table,ttrim(vcfldget(table,"Fname2",FLDLOCTEMP)),cnt);
        }                               /* Get and go               */
    return(GOOD);                       /* Return field valid       */
    }                                   /* ------------------------ */

COUNT put_id(fld,table)
TEXT *fld;                  /* Value of current field               */
GETTABLE *table;            /* Pointer to current gettable          */
    {                       /* ------------------------------------ */
    COUNT fid;              /* Field id                             */
    TEXT *vcfldiget();      /* Declare functions used               */
    fid = atoi(fld);                    /* Convert field number     */
    vcfldiput(table,fid,vcfldiget(table,8,FLDLOCTEMP),
            FLDLOCTEMP+FLDLOCUPDATE);   /* Put value in temp loc    */
    return(GOOD);                       /* Return field valid       */
    }                                   /* ------------------------ */

COUNT goto_id(fld,table)
TEXT *fld;                  /* Value of current field               */
GETTABLE *table;            /* Pointer to current gettable          */
    {                       /* ------------------------------------ */
    COUNT cnt;              /* Offset                               */
    COUNT fid;              /* Field id                             */
    TEXT *vcfldiget();      /* Declare functions used               */
    if(table->tkeypress == spkey.fld_ret)   /* If return entered    */
        {                               /*                          */
        cnt = atoi(fld);                /* Convert offset           */
        fid = atoi(vcfldiget(table,10,FLDLOCTEMP));/* Convert field */
        vcfldigo(table,fid,cnt);        /* Go to field              */
        }                               /*                          */
    return(GOOD);                       /* Return field valid       */
    }                                   /* ------------------------ */


