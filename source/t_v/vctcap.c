/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:01
*                
*   Name            tctcap.c  --  termcap information variables
*
*   Description     Global variable used by functions tctinit(),
*                   ttinit(), and demos mktcc() and tc2tcc().
*
*
**/

#include <vcstdio.h>

#ifdef VMS
COUNT tcldtc()
    {
    return(TRUE);
    }
#endif

TEXT *tstrctrl[] =
    {
    (TEXT *)"ae",(TEXT *)"as",(TEXT *)"bc",(TEXT *)"bo",(TEXT *)"be",
    (TEXT *)"ic",(TEXT *)"cd",(TEXT *)"ce",(TEXT *)"CF",(TEXT *)"cl",
    (TEXT *)"CO",(TEXT *)"cm",(TEXT *)"ct",(TEXT *)"es",(TEXT *)"ie",
    (TEXT *)"is",(TEXT *)"it",(TEXT *)"ke",(TEXT *)"ks",(TEXT *)"GE",
    (TEXT *)"GS",(TEXT *)"pc",(TEXT *)"se",(TEXT *)"so",(TEXT *)"ue",
    (TEXT *)"us",(TEXT *)"ve",(TEXT *)"vs",
    NULLTEXT
    };

TEXT *tspattr[] =
    {
    (TEXT *)"a0",(TEXT *)"a1",(TEXT *)"a2",(TEXT *)"a3",(TEXT *)"a4",
    (TEXT *)"a5",(TEXT *)"a6",(TEXT *)"a7",(TEXT *)"a8",(TEXT *)"a9",
    (TEXT *)"b0",(TEXT *)"b1",(TEXT *)"b2",(TEXT *)"b3",(TEXT *)"b4",
    (TEXT *)"b5",(TEXT *)"A0",(TEXT *)"A1",(TEXT *)"A2",(TEXT *)"A3",
    (TEXT *)"A4",(TEXT *)"A5",(TEXT *)"A6",(TEXT *)"A7",(TEXT *)"A8",
    (TEXT *)"A9",(TEXT *)"B0",(TEXT *)"B1",(TEXT *)"B2",(TEXT *)"B3",
    (TEXT *)"B4",(TEXT *)"B5",
    NULLTEXT
    };

TEXT *tnumctrl[] =
    {
    (TEXT *)"li",(TEXT *)"co",(TEXT *)"sg",(TEXT *)"ug",(TEXT *)"cg",
    (TEXT *)"GG",(TEXT *)"bb",(TEXT *)"ig",(TEXT *)"zd",(TEXT *)"zk",
    (TEXT *)"zc",(TEXT *)"zt",
    NULLTEXT
    };

TEXT *tboolctrl[] =
    {
    (TEXT *)"am",(TEXT *)"bs",(TEXT *)"ms",(TEXT *)"xs",NULLTEXT
    };

TEXT *tborderctrl[] =
    {
    (TEXT *)"GV",(TEXT *)"GH",(TEXT *)"G2",(TEXT *)"G1",(TEXT *)"G3",
    (TEXT *)"G4",(TEXT *)"GL",(TEXT *)"GR",(TEXT *)"GU",(TEXT *)"GD",
    (TEXT *)"GC",(TEXT *)"GA",(TEXT *)"GB",(TEXT *)"GF",(TEXT *)"GI",
    (TEXT *)"GJ",(TEXT *)"GK",(TEXT *)"GM",(TEXT *)"GN",(TEXT *)"GO",
    (TEXT *)"GP",(TEXT *)"gv",(TEXT *)"gh",(TEXT *)"g2",(TEXT *)"g1",
    (TEXT *)"g3",(TEXT *)"g4",(TEXT *)"gl",(TEXT *)"gr",(TEXT *)"gu",
    (TEXT *)"gd",(TEXT *)"gc",(TEXT *)"ga",(TEXT *)"gb",(TEXT *)"gc",
    (TEXT *)"gi",(TEXT *)"gj",(TEXT *)"gk",(TEXT *)"gm",(TEXT *)"gn",
    (TEXT *)"go",(TEXT *)"gp",
    NULLTEXT
    };

struct keyload
    {
    TEXT *tcap;
    COUNT def;
    COUNT value;
    };

#ifdef PRIMOS
#define TCAPOFSET 128
#define TCAPRETVAL 138
#else
#define TCAPOFSET 0
#define TCAPRETVAL 13
#endif

struct keyload kload[] =
    {
    (TEXT *)"kz",(COUNT)27 + TCAPOFSET,(COUNT)4000,
    (TEXT *)"kb",(COUNT)8  + TCAPOFSET,(COUNT)4001,
    (TEXT *)"cr",(COUNT)0  + TCAPRETVAL,(COUNT)4002,
    (TEXT *)"bk",(COUNT)2  + TCAPOFSET,(COUNT)4003,
    (TEXT *)"ta",(COUNT)9  + TCAPOFSET,(COUNT)4004,
    (TEXT *)"bt",(COUNT)17 + TCAPOFSET,(COUNT)4005,
    (TEXT *)"kl",(COUNT)19 + TCAPOFSET,(COUNT)4006,
    (TEXT *)"kr",(COUNT)4  + TCAPOFSET,(COUNT)4007,
    (TEXT *)"ku",(COUNT)5  + TCAPOFSET,(COUNT)4008,
    (TEXT *)"kd",(COUNT)24 + TCAPOFSET,(COUNT)4009,
    (TEXT *)"kh",(COUNT)23 + TCAPOFSET,(COUNT)4010,
    (TEXT *)"EN",(COUNT)26 + TCAPOFSET,(COUNT)4011,
    (TEXT *)"PU",(COUNT)18 + TCAPOFSET,(COUNT)4012,
    (TEXT *)"PD",(COUNT)3  + TCAPOFSET,(COUNT)4013,
    (TEXT *)"ki",(COUNT)22 + TCAPOFSET,(COUNT)4014,
    (TEXT *)"kk",(COUNT)7  + TCAPOFSET,(COUNT)4015,
    (TEXT *)"LI",(COUNT)14 + TCAPOFSET,(COUNT)4016,
    (TEXT *)"LD",(COUNT)25 + TCAPOFSET,(COUNT)4017,
    (TEXT *)"kp",(COUNT)28 + TCAPOFSET,(COUNT)4018,
    (TEXT *)"ek",(COUNT)29 + TCAPOFSET,(COUNT)4019,
    (TEXT *)"ck",(COUNT)15 + TCAPOFSET,(COUNT)4020,
    (TEXT *)"pk",(COUNT)16 + TCAPOFSET,(COUNT)4021,
    (TEXT *)"mk",(COUNT)0  + TCAPOFSET,(COUNT)4022,
    (TEXT *)"nk",(COUNT)0  + TCAPOFSET,(COUNT)4023,
    (TEXT *)"ok",(COUNT)0  + TCAPOFSET,(COUNT)4024,
    NULLTEXT,0,0
    };

