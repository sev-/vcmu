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
*   Name            button.c
*                                   
*   Description     Test new button and window defines
*
**/

#define VCGET_DEFS
#define VCM_DEFS
#include <vcstdio.h>

COUNT inpcheck(),initchk(),lightchk();
COUNT inpbuton(),initbut(),lightbut();
COUNT inpblock(),initblk(),lightblk();
COUNT togact();

struct STR_WSTYLE wdostyles[] =
    {
    (TEXT *)"test_style",BORDER+ACTIVE+BD2+CURSOR,32,
        GREEN WITH BLACK,WHITE WITH BLACK,
        GREEN WITH BLACK,BLACK WITH WHITE,
        CYAN WITH BLACK,CYAN WITH BLACK,
        GREEN WITH BLACK,WHITE WITH BLACK,
        GREEN WITH BLACK,BLACK WITH WHITE,
    NULL,0,0,0,0,0,0,0,0,0,0,0,0
    };

struct STR_WDEF wdodefs[] =
    {
    (TEXT *)"test_wdo",(TEXT *)"test_style",
        (TEXT *)"Window Style Information",(TEXT *)"Right",
        (TEXT *)"Left Title",(TEXT *)"This is the Bottom",5,0,16,79,0,0,0,0,
    NULL,NULL,NULL,NULL,NULL,NULL,-1,-1,-1,-1,0,0,0,0
    };

TEXT *radio[] = 
    {
    (TEXT *)"Standard",
    (TEXT *)"Center",
    (TEXT *)"Pulldown",
    (TEXT *)"Tldown",
    NULLTEXT
    };

TEXT *borders[] =
    {
    (TEXT *)"None",
    (TEXT *)"BD0",
    (TEXT *)"BD1",
    (TEXT *)"BD2",
    (TEXT *)"BD3",
    NULLTEXT
    };

main(argc,argv)
COUNT argc;
TEXT *argv[];
    {
    COUNT retval;
    COUNT k1,k2,k3,k4,k5,k6;
    COUNT c1,c2,c3,c4;
    COUNT b1,b2,b3,b4,b5;
    COUNT cnt = 9001;
    TEXT name[31];
    TEXT *vcdebug=NULL;
    vcstart(CLRSCRN);
    empty(name,31);
    c1 = 1;
    c2 = c3 = c4 = 0;
    b1 = 1;
    b2 = b3 = b4 = b5 = 0;
    k1 = k2 = k3 = k4 = k5 = k6 = 0;
    datafunc[FLDCHECK >> 7] = inpcheck;
    datainit[FLDCHECK >> 7] = initchk;
    datalight[FLDCHECK >> 7] = lightchk;
    datafunc[FLDBLOCK >> 7] = inpblock;
    datainit[FLDBLOCK >> 7] = initblk;
    datalight[FLDBLOCK >> 7] = lightblk;
    datafunc[FLDBUTON >> 7] = inpbuton;
    datainit[FLDBUTON >> 7] = initbut;
    datalight[FLDBUTON >> 7] = lightbut;
    startstyle(wdostyles,wdodefs);
    wdefopen("test_wdo");
    box(0,1,2,48,0,-1);
    box(3,1,6,40,1,-1);
    box(6,42,9,76,0,-1);
    atsay(1,3,(TEXT *)"Window Style:");
    atsay(3,2,(TEXT *)"Controls:");
    atsay(4,3,(TEXT *)"[ ] ACTIVE");
    atsay(5,3,(TEXT *)"[ ] CURSOR");
    atsay(4,15,(TEXT *)"[ ] SCROLL");
    atsay(5,15,(TEXT *)"[ ] NOAUTO");
    atsay(5,27,(TEXT *)"[ ] NOADJ");
    atsay(4,27,(TEXT *)"[ ] COOKED");
    atsay(7,44,(TEXT *)"Window");
    atsay(8,45,(TEXT *)"Open:");
    atsay(7,52,(TEXT *)"( )STANDARD");
    atsay(8,52,(TEXT *)"( )PULLDOWN");
    atsay(7,65,(TEXT *)"( )CENTER");
    atsay(8,65,(TEXT *)"( )TLDOWN");
    vcxxfld(1,17,name,(TEXT *)"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",-1,FLDSTRING,
            (TEXT *)"name",NULLFUNC,NULL,NULL,-1,NULL,0);
    vcxxfld(1,54,&spkey.abort,(TEXT *)" Abort ",FLDBOLD+FLDBORDER,
            FLDBUTON+FLDINT,(TEXT *)"Abort",NULLFUNC,NULL,NULL,-1,NULLTEXT,0);
    vcxxfld(1,65,&cnt,(TEXT *)"Cursor",-1,FLDBUTON+FLDINT,
            (TEXT *)"Done",togact,NULL,NULL,-1,NULLTEXT,0);
    vcxxfld(4,4,&k1,(TEXT *)"~",FLDNORET,FLDCHECK+FLDINT,
            (TEXT *)" ",NULLFUNC,NULL,NULL,-1,NULL,0);
    vcxxfld(4,16,&k3,(TEXT *)"~",FLDNORET,FLDCHECK+FLDINT,
            (TEXT *)" ",NULLFUNC,NULL,NULL,-1,NULL,0);
    vcxxfld(4,28,&k5,(TEXT *)"~",FLDNORET,FLDCHECK+FLDINT,
            (TEXT *)" ",NULLFUNC,NULL,NULL,-1,NULL,0);
    vcxxfld(5,4,&k2,(TEXT *)"~",FLDNORET,FLDCHECK+FLDINT,
            (TEXT *)"Cursor",NULLFUNC,NULL,NULL,-1,NULL,0);
    vcxxfld(5,16,&k4,(TEXT *)"~",FLDNORET,FLDCHECK+FLDINT,
            (TEXT *)" ",NULLFUNC,NULL,NULL,-1,NULL,0);
    vcxxfld(5,28,&k6,(TEXT *)"~",FLDNORET,FLDCHECK+FLDINT,
            (TEXT *)" ",NULLFUNC,NULL,NULL,-1,NULL,0);
    vcxxfld(7,53,&c1,(TEXT *)"*",FLDSINGLE,FLDCHECK+FLDINT,
            (TEXT *)"Standard",NULLFUNC,NULL,NULL,-1,radio,0);
    vcxxfld(8,53,&c2,(TEXT *)"*",FLDSINGLE,FLDCHECK+FLDINT,
            (TEXT *)"Pulldown",NULLFUNC,NULL,NULL,-1,radio,0);
    vcxxfld(7,66,&c3,(TEXT *)"*",FLDSINGLE,FLDCHECK+FLDINT,
            (TEXT *)"Center",NULLFUNC,NULL,NULL,-1,radio,0);
    vcxxfld(8,66,&c4,(TEXT *)"*",FLDSINGLE,FLDCHECK+FLDINT,
            (TEXT *)"Tldown",NULLFUNC,NULL,NULL,-1,radio,0);
    vcxxfld(4,45,&b1,(TEXT *)"None",FLDSINGLE+FLDBORDER,FLDBLOCK+FLDINT,
            (TEXT *)"None",NULLFUNC,NULL,NULL,-1,borders,0);
    vcxxfld(4,54,&b2,(TEXT *)"0",FLDSINGLE+FLDBORDER,FLDBLOCK+FLDINT,
            (TEXT *)"BD0",NULLFUNC,NULL,NULL,-1,borders,0);
    vcxxfld(4,59,&b3,(TEXT *)"1",FLDSINGLE+FLDBORDER,FLDBLOCK+FLDINT,
            (TEXT *)"BD1",NULLFUNC,NULL,NULL,-1,borders,0);
    vcxxfld(4,64,&b4,(TEXT *)"2",FLDSINGLE+FLDBORDER,FLDBLOCK+FLDINT,
            (TEXT *)"BD2",NULLFUNC,NULL,NULL,-1,borders,0);
    vcxxfld(4,69,&b5,(TEXT *)"3",FLDSINGLE+FLDBORDER,FLDBLOCK+FLDINT,
            (TEXT *)"BD3",NULLFUNC,NULL,NULL,-1,borders,0);
    retval = readgets();
    vcend(CLOSE);
    }

COUNT togact(fld,table)
TEXT *fld;
GETTABLE *table;
    {
    GETITEM *vcfldfnd(),*gi;
    if(table->tkeypress > 9000)
        {
        gi = vcfldfnd(table,"Cursor",0,0);
        inpchktog(gi,TOGGLE);
        lightchk(gi);
        return(BAD);
        }
    else
        return(GOOD);
    }
