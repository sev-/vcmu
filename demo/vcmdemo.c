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
*   Name            vcmdemo 
*                                   
*   Description     Menu Demo program
*
*   Return Value    None
*                                   
**/                                 

#define VCM_DEFS            /* Include Menu Defines and structures      */
#include <vcstdio.h>

/************************************************************************/
/*************************  Global Varibles *****************************/
/************************************************************************/

TEXT *globstr;
COUNT globint=37;
COUNT newint=1;
COUNT copycutstat=0;
COUNT boldflag=0;
COUNT italicflag=0;
COUNT underlineflag=0;
COUNT outlineflag=0;
COUNT shadowflag=0;
COUNT leftparaflag=1;
COUNT rightparaflag=0;
COUNT centerparaflag=0;
COUNT justifyparaflag=0;

/************************************************************************/
/***********************  Extern Declarations ***************************/
/************************************************************************/

extern WPTR vctimwdo;
extern COUNT vctimrow,vctimcol,vctimattr;
WPTR wxopen(),wopen();

main(argc,argv)
COUNT argc;
TEXT *argv[];
    {
    COUNT subfunc(),intfunc(),toggle();     /* Declare Functions for    */
    COUNT parafunc(),normal(),copy(),cut(); /* addresses                */
    COUNT vcmhf3(),dummyfun(),pastefunc();  /*                          */
    VOID clock12();                         /* Declare loop function    */
    WPTR sw;                                /* Window for status line   */
    PFI setloop();                          /* Function declaration     */
    VCMENU *menuxnew(),*menunew();          /* Function declaration     */
    VCMENU *mainmenu,                       /* Declare menu pointer     */
          *filesmenu,                       /*   "      "      "        */
          *editmenu,                        /*   "      "      "        */
          *searchmenu,                      /*   "      "      "        */
          *charmenu,                        /*   "      "      "        */
          *paramenu;                        /*   "      "      "        */
    MENUITEM *menuxitem();                  /* Function declaration     */
/***************/
    vcstart(CLRSCRN);                        /* Start Vitamin C          */
    sw = wxopen(vcterm.rows-1,0,vcterm.rows-1,  /* Open one line window */
                vcterm.cols -1,NULL,ACTIVE,0,0);/* on last line of scrn */
    wdoctrl->wbgdisplay = TRUE;             /* Check for backgrd print  */
    statlin(sw,0,1,-1);                     /* Set status window        */
    timeloc(sw,0,70,DEFAULT);               /* Set clock location       */
    setloop(clock12);                       /* Set clock as loop func.  */

    /********************************************************************/
    /***************************  Menu Styles ***************************/
    /********************************************************************/

    addmstyle("STDHORIZ",HORIZONTAL | TITLECENTER | AUTOMENU,80,
                 vc.cyan+vc.bold+vc.bg*vc.blue,          /* Normal      */
                 vc.blue+vc.bg*vc.white,                 /* Bar         */
                 vc.cyan+vc.bg*vc.blue,                  /* Unavailable */
                 vc.white+vc.blue*vc.bg,                 /* Border      */
                 0);                                     /* Permlvl     */
    addmstyle("STDVERT",VERTICAL,AUTO,
                 vc.cyan+vc.bold+vc.bg*vc.blue,          /* Normal      */
                 vc.blue+vc.bg*vc.white,                 /* Bar         */
                 vc.cyan+vc.bg*vc.blue,                  /* Unavailable */
                 vc.white+vc.blue*vc.bg,                 /* Border      */
                 0);                                     /* Permlvl     */

    /********************************************************************/
    /***************************  Open Menus ****************************/
    /********************************************************************/

    mainmenu = menunew(0,0,"Vitamin C - Sample Menus",
                                            "NO HELP","STDHORIZ");   
    filesmenu = menunew(2,1,NULL,"NO HELP","STDVERT");
    editmenu = menunew(2,8,NULL,"NO HELP","STDVERT");
    searchmenu = menunew(2,14,NULL,"NO HELP","STDVERT");
    charmenu = menunew(2,22,NULL,"NO HELP","STDVERT");
    paramenu = menunew(2,33,NULL,"NO HELP","STDVERT");

    /********************************************************************/
    /**************************  Add Menu Items *************************/
    /********************************************************************/

    menuxitem(mainmenu,"Files",NULL,0,NULLFUNC,(TEXT *)filesmenu,
            "Create, open, save, and print files","NO HELP",MENU);
    menuxitem(mainmenu,"Edit",NULL,0,NULLFUNC,(TEXT *)editmenu,
            "Cut, paste, undo, etc.","NO HELP",MENU);
    menuxitem(mainmenu,"Search",NULL,0,NULLFUNC,(TEXT *)searchmenu,
            "Find, replace, etc.","NO HELP",MENU);
    menuxitem(mainmenu,"Character",NULL,0,NULLFUNC,(TEXT *)charmenu,
            "Sizes and styles","NO HELP",MENU);
    menuxitem(mainmenu,"Paragraph",NULL,0,NULLFUNC,(TEXT *)paramenu,
            "Formats, tabs, etc.","NO HELP",MENU);

    /************************** Files Menu Items ************************/

    menuxitem(filesmenu,"New",NULL,0,dummyfun,NULL,NULL,"NO HELP",STRPARM);
    menuxitem(filesmenu,"Open",NULL,0,dummyfun,NULL,NULL,"NO HELP",STRPARM);
    menuxitem(filesmenu,"Save",NULL,0,NULLFUNC,NULL,NULL,"NO HELP",STRPARM);
    menuxitem(filesmenu,"Save As",NULL,0,NULLFUNC,NULL,NULL,"NO HELP",
                                        STRPARM);
    menuxitem(filesmenu,NULL,NULL,0,NULLFUNC,NULL,NULL,NULL,SEPARATOR);
    menuxitem(filesmenu,"Printer Set-up",NULL,0,NULLFUNC,NULL,NULL,
                                        "NO HELP",STRPARM);
    menuxitem(filesmenu,"Print One",NULL,0,NULLFUNC,NULL,NULL,"NO HELP",
                                         STRPARM);
    menuxitem(filesmenu,"Print",NULL,0,NULLFUNC,NULL,NULL,"NO HELP",STRPARM);

    /*************************** Edit Menu Items ************************/

    menuxitem(editmenu,"Undo",NULL,0,NULLFUNC,NULL,
            "Undo previous operation","NO HELP",STRPARM);
    menuxitem(editmenu,NULL,NULL,0,NULLFUNC,NULL,NULL,NULL,SEPARATOR);
    menuxitem(editmenu,"Paste",NULL,0,pastefunc,NULL,
            "Paste data from scrap into document","NO HELP",
            UNAVAILABLE);
    menuxitem(editmenu,"Cut",NULL,0,copy,NULL,
            "Copy marked block to scrap","NO HELP",STRPARM);
    menuxitem(editmenu,"Copy",NULL,0,cut,NULL,
            "Delete marked block to scrap","NO HELP",STRPARM);

    /*************************** Search Menu Items **********************/

    menuxitem(searchmenu,"Find",NULL,0,NULLFUNC,NULL,"Search for text",
                "NO HELP",STRPARM);
    menuxitem(searchmenu,"Replace",NULL,0,NULLFUNC,NULL,
                "Search for text and replace","NO HELP",STRPARM);
    menuxitem(searchmenu,"Next",NULL,0,NULLFUNC,NULL,
                "Search for next ocurrence","NO HELP",STRPARM|UNAVAILABLE);
    menuxitem(searchmenu,"Previous",NULL,0,NULLFUNC,NULL,
                "Search for previous ocurrence","NO HELP",STRPARM|UNAVAILABLE);

    /************************ Character Menu Items **********************/

    menuxitem(charmenu,"Normal",NULL,0,normal,NULL,NULL,"NO HELP",STRPARM);
    menuxitem(charmenu,"",NULL,0,NULLFUNC,NULL,NULL,"NO HELP",SEPARATOR);
    menuxitem(charmenu,"Bold",NULL,0,toggle,&boldflag,NULL,"NO HELP",CHECKED);
    menuxitem(charmenu,"Italic",NULL,0,toggle,&italicflag,NULL,"NO HELP",
                CHECKED);
    menuxitem(charmenu,"Underline",NULL,0,toggle,&underlineflag,NULL,
                "NO HELP",CHECKED);
    menuxitem(charmenu,"Outline",NULL,0,toggle,&outlineflag,NULL,
                "NO HELP",CHECKED);
    menuxitem(charmenu,"Shadow",NULL,0,toggle,&shadowflag,NULL,
                "NO HELP",CHECKED);
    menuxitem(charmenu,"",NULL,0,NULLFUNC,NULL,NULL,NULL,SEPARATOR);
    menuxitem(charmenu,"Formats",NULL,0,NULLFUNC,NULL,NULL,"NO HELP",STRPARM);

    /*************************** Paragraph Menu Items *******************/

    menuxitem(paramenu,"Left",NULL,0,parafunc,&leftparaflag,NULL,"NO HELP",
                CHECKED);
    menuxitem(paramenu,"Right",NULL,0,parafunc,&rightparaflag,NULL,
                "NO HELP",CHECKED);
    menuxitem(paramenu,"Center",NULL,0,parafunc,&centerparaflag,NULL,
                "NO HELP",CHECKED);
    menuxitem(paramenu,"Justify",NULL,0,parafunc,&justifyparaflag,NULL,
                "NO HELP",CHECKED);
    menuxitem(paramenu,NULL,NULL,0,NULLFUNC,NULL,NULL,NULL,SEPARATOR);
    menuxitem(paramenu,"MARGINS",NULL,0,NULLFUNC,NULL,
                "Set paragraph format and margins","NO HELP",STRPARM);
    menuxitem(paramenu,NULL,NULL,0,NULLFUNC,NULL,NULL,NULL,SEPARATOR);
    menuxitem(paramenu,"TABS",NULL,0,NULLFUNC,NULL,
                "Set and clear tab stops","NO HELP",STRPARM);

    vcmhk3=vcmhf3;                  /* Setup hook function              */
    instruction();                  /* Print instructions               */
    vcmenu(mainmenu);               /* Call menus using first menu      */
    vcend(CLOSE);                   /* Close Windows and clean up       */
    }


/************************************************************************/
/**************************  Hook Function ******************************/
/************************************************************************/
/*                                                                      */
/* This is executed after a key is press inside the menu system. One of */
/* the methods for customizing menus.                                   */
/*                                                                      */
/************************************************************************/

COUNT vcmhf3(m)
VCMENU *m;                                  /* Pointer to current menu  */
    {
    if( (m->mstyle & VERTICAL) &&               /* If the current menu  */
        (m->mcalledby->mstyle & HORIZONTAL) )   /* was called by a hort.*/
       {                                        /* menu                 */
       if( m->mkeyhit == vckey.cur_right )  /* If the user hit cursor   */
            {                               /*  right                   */  
            m->mresult=ESCAPE;              /* Set menu to exit         */
            ungetone( vckey.cur_right );    /* Put cur_right on key buf.*/
            ungetone( vckey.ret );          /* Put return on key buffer */
            return(TRUE);                   /* Tell menu to goto top of */
            }                               /* loop and the m->result   */   
        else                                /* will cause exit          */
            {                               /*                          */
            if(m->mkeyhit == vckey.cur_left)  /* If the user hit cursor */
                {                             /*  left                  */
                m->mresult=ESCAPE;          /* Set menu to exit         */
                ungetone( vckey.cur_left ); /* Put cur_left on key buf. */
                ungetone( vckey.ret );      /* Put return on key buffer */
                return(TRUE);               /* Tell menu to goto top of */
                }                           /* loop and forgets the key */
            }                               /* entered and exits        */
        }                                   /*                          */
    return(0);                              /* return with no changes   */
    }

/************************************************************************/
/*********************** Dummy Function for Demo ************************/
/************************************************************************/

COUNT dummyfun(m)
VCMENU *m;
    {
    return(0);
    }

/************************************************************************/
/************************* Toggle Option Flags **************************/
/************************************************************************/

COUNT toggle(m)
VCMENU *m;
    {
    toglchkvar(m);                          /* Toggle current option    */
    return(REFRESH);                        /* Redraw current menu      */
    }

/************************************************************************/
/*********************** Toggle Paragraph Function **********************/
/************************************************************************/
/*                                                                      */
/* Assures that only one of the paragraph formats is selected at a time */
/*                                                                      */
/************************************************************************/

COUNT parafunc(m)
VCMENU *m;                                  /* Pointer to current menu  */
    {                                       /*                          */
    MENUITEM *mi,*getmnuitm();              /* Menu variable and decl.  */
    if( *m->mcuritmptr->eparm.pnumptr != 0 )/* If item already checked  */
        return(0);                          /*  return                  */
    mi = getmnuitm(m,"Left");               /* Get pointer to first item*/
    while( (mi != (MENUITEM *) 0)  &&       /* Loop until separator or  */
            !(mi->ectrl & SEPARATOR) )      /* end of link list         */
       {                                    /*                          */
       *mi->eparm.pnumptr = 0;              /* Set checked value to off */
       mi = mi->enext;                      /* Look at next menu item   */
       }                                    /*                          */
    *m->mcuritmptr->eparm.pnumptr = 1;      /* Set the current item on  */
    return(REFRESH);                        /* Redraw the menu          */
    }

/************************************************************************/
/************************* Normal Toggle Function ***********************/
/************************************************************************/
/*                                                                      */
/*      Clears all other fonts when normal is selected                  */
/*                                                                      */
/************************************************************************/

COUNT normal(m)
VCMENU *m;                                  /* Pointer to current menu  */
    {                                       /*                          */
    MENUITEM *mi,*getmnuitm();              /* Menu variable and decl.  */
    mi=getmnuitm(m,"Bold");                 /* Get pointer to Bold item */
    while( (mi != (MENUITEM *) 0)  &&       /* Loop until separator or  */
            !(mi->ectrl & SEPARATOR) )      /* end of link list         */
       {                                    /*                          */
       *mi->eparm.pnumptr = 0;              /* Set checked value to off */
       mi = mi->enext;                      /* Look at next menu item   */
       }                                    /*                          */
    return(REFRESH);                        /* Redraw the menu          */
    }
 
/************************************************************************/
/*********************** Cut and Paste Functions ************************/
/************************************************************************/

COUNT cut(m)
VCMENU *m;                                  /* Pointer to current menu  */
    {                                       /*                          */
    copy(m);                                /* Call copy function       */
                                            /* Call other functions to  */
                                            /* "clear" area just copied */
    return(REFRESH);                        /* Refresh to menu          */
    }

COUNT pastefunc(m)
VCMENU *m;                                  /* Pointer to current menu  */
    {                                       /*                          */
    vcmavailstat(m->mcuritmptr,OFF);        /* Change availability      */
    copycutstat = 0;                        /* Change Status            */
    m->mcuritmptr = m->mcuritmptr->enext;   /* Set next item to current */
    return(REFRESH);                        /* Refresh to menu          */
    }

COUNT copy(m)
VCMENU *m;                                  /* Pointer to current menu  */
    {                                       /*                          */
    MENUITEM *gi,*getmnuitm();              /* Menu variables and decl. */
    WPTR wptr;                              /* Window pointer variable  */
    COUNT retval = 0;                       /* Return value             */
    if( copycutstat == 0 )                  /* If not already copyed    */
        {                                   /* Open window & print msg  */
        wptr = wopen(12,4,23,75," M E S S A G E ");
        atsay(1,1,"Until now, nothing had been 'cut' or 'copied' to our fictional");
        atsay(2,1,"applications 'clipboard' so there was nothing that we could paste.");
        atsay(3,1,"That's why the 'Paste' option had an UNAVAILABLE status.");
        atsay(5,1,"Since our application will now have something to paste from, it");
        atsay(6,1,"will make the 'Paste' option AVAILABLE.");
        atsay(8,1,"                 Press [RETURN] To Continue...");
        getone();                           /* Wait for a key           */
        wclose(wptr);                       /* Close window             */
        copycutstat = 1;                    /* Change Status            */
        gi = getmnuitm(m,"Paste");          /* Get pointer to Paste item*/
        vcmavailstat(gi,ON);                /* Change availability      */
        retval = REFRESH;                   /* Menu changed so refresh  */
        }                                   /*                          */
   return(retval);                          /* Return to menu           */
   }
      
/************************************************************************/
/****************** Change Availability of Menu Item ********************/
/************************************************************************/

vcmavailstat(mi,status)
MENUITEM *mi;                               /* Pointer to item to change*/
COUNT status;                               /* Turn ON, OFF or TOGGLE   */
    {                                       /*                          */
    switch( status )                        /* Switch status            */
        {                                   /*                          */
        case OFF:                           /* If unavailable requested */
            mi->ectrl |= UNAVAILABLE;       /* Set control to unavail.  */
            break;                          /* Exit                     */
        case ON:                            /* If available requested   */
            mi->ectrl &= ~UNAVAILABLE;      /* Set control to available */
            break;                          /* Exit                     */
        case TOGGLE:                        /* if toggle requested      */
            mi->ectrl ^= UNAVAILABLE;       /* Toggle menu control      */
            break;                          /* Exit                     */
        }
    }

/************************************************************************/
/************************* Clock Function *******************************/
/************************************************************************/
/*                                                                      */
/* This is setup as a loop function it is executed every second while   */
/* awaiting keyboard input                                              */
/*                                                                      */
/************************************************************************/

VOID clock12()
    {
    static TEXT oldtim[20];                 /* Location to store time   */
    TEXT newtim[20],outstr[10];             /* String for time & form.  */
    COUNT hrs,mins;                         /* Hours and minutes        */
    if( vctimwdo == (WPTR) 0)               /* If window not open       */
        return;                             /* Exit                     */
    gettime(newtim);                        /* Get current time         */
    if(strncmp(oldtim,newtim,5))            /* Compare to saved time    */
        {                                   /* if minutes have changed  */
        sscanf(newtim,"%d:%d",&hrs,&mins);  /* Separate in hrs and mins */
        if( hrs >= 12 )                     /* If after 12 o'clock      */
           sprintf(outstr,"%2d:%2d pm",(hrs-12)==0?12:hrs-12,mins);
        else                                /* If before 12 o'clock     */
           sprintf(outstr,"%2d:%2d am",(hrs==0)?12:hrs,mins);
        if(outstr[3] == ' ')                /* If space in fourth pos.  */
           outstr[3] = '0';                 /* Change space to zero     */
        strcpy(oldtim,newtim);              /* Save new time            */
        if( vctimattr == -1 )               /* If using default attr.   */
           watsay(vctimwdo,vctimrow,vctimcol,outstr);
        else                                /* Using selected attribute */
           wxatsay(vctimwdo,vctimrow,vctimcol,outstr,vctimattr);
        }
    }

/************************************************************************/
/***************************** Instruction ******************************/
/************************************************************************/

instruction()
    {
    wopen(3,55,10,75,"Instructions");       /* Open Window              */
    atsay(0,0," Use arrows keys");          /*     Display Messages     */
    atsay(1,0,"   and Return");             /*        "       "         */
    atsay(2,0," to select items");          /*        "       "         */
    atsay(4,0,"Press ESC to exit");         /*        "       "         */
    atsay(5,0,"   or backup");              /*        "       "         */
    }



