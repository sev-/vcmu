/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 9/1/90 at 00:28:32
*                
*   Name            vctcap.h  --  termcap information variables
*
*   Description     Global variable used by functions vctinit(),
*                   ttinit(), and demos mktcc() and vc2tcc().
*
*
**/

extern TEXT *tstrctrl[];
extern TEXT *tspattr[];
extern TEXT *tnumctrl[];
extern TEXT *tboolctrl[];
extern TEXT *tborderctrl[];

struct keyload
    {
    TEXT *tcap;
    COUNT def;
    COUNT value;
    };

extern struct keyload kload[];

#define NUMNUMBERS 18
#define NUMSTRINGS 28
#define NUMSPECIAL 32
#define NUMPRECOMP 3


