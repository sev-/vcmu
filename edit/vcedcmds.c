/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:23
*
*   Name            vcedcmds.c - vced command structure
*                                   
*   Description     Tced command structure
*
**/

#include <vcstdio.h>
#include <vcdbms.h>
#define VCEDVARS
#include <vced.h>

extern COUNT vcedmvleft();
extern COUNT vcedmvright();
extern COUNT vcedmvup();
extern COUNT vcedmvdown();
extern COUNT vcedexit();
extern COUNT vcedprtbuf();
extern COUNT vcedinstog();
extern COUNT vcedbksp();
extern COUNT vceddelete();
extern COUNT vcedtol();
extern COUNT vcedeol();
extern COUNT vcedtogstat();
extern COUNT vcedreturn();
extern COUNT vcedabort();
extern COUNT vcedhelp();
extern COUNT vcedpgup();
extern COUNT vcedpgdn();
extern COUNT vcedtab();
extern COUNT vcedbktab();
extern COUNT vcedsbuf();
extern COUNT vcedtof();
extern COUNT vcedeof();
extern COUNT vcedhome();
extern COUNT vcedend();

#ifdef VCEDFULL
extern COUNT vcedgoto();
extern COUNT vcedundo();
extern COUNT vcedredo();
extern COUNT vcedreplace();
extern COUNT vcedrnext();
extern COUNT vcedmark();
extern COUNT vcedpaste();
extern COUNT vcedmerge();
extern COUNT vcednxtfil();
extern COUNT vcednewfil();
extern COUNT vcedrecord();
extern COUNT vcedplay();
extern COUNT vcedlndel();
extern COUNT vcedfind();
extern COUNT vcedfnext();
#endif

VCEDCMD vcedcmds[] =
    {
    (TEXT *)"abort",        4000,vcedabort,
    (TEXT *)"backspace",    4001,vcedbksp,
    (TEXT *)"backtab",      4005,vcedbktab,
    (TEXT *)"begin_of_line",4010,vcedhome,
    (TEXT *)"begin_of_file",5010,vcedhome,
    (TEXT *)"cursor_down",  4009,vcedmvdown,
    (TEXT *)"cursor_left",  4006,vcedmvleft,
    (TEXT *)"cursor_right", 4007,vcedmvright,
    (TEXT *)"cursor_up",    4008,vcedmvup,
    (TEXT *)"delete_char",  4015,vceddelete,
    (TEXT *)"delete_char",   127,vceddelete,
#ifdef VCEDFULL
    (TEXT *)"delete_line",  4017,vcedlndel,
#endif
    (TEXT *)"end_of_line",  4011,vcedend,
    (TEXT *)"end_of_file",  5011,vcedend,
    (TEXT *)"exit",         5009,vcedexit,
#ifdef VCEDFULL
    (TEXT *)"find",         5006,vcedfind,
    (TEXT *)"find_next",    5007,vcedfnext,
    (TEXT *)"goto",         5005,vcedgoto,
#endif
    (TEXT *)"menu",         5000,vcedhelp,
#ifdef VCEDFULL
    (TEXT *)"mark",         5002,vcedmark,
    (TEXT *)"merge_file",   5014,vcedmerge,
    (TEXT *)"new_file",     5016,vcednewfil,
    (TEXT *)"next_file",    5015,vcednxtfil,
#endif
    (TEXT *)"page_down",    4013,vcedpgdn,
    (TEXT *)"page_up",      4012,vcedpgup,
#ifdef VCEDFULL
    (TEXT *)"paste",        5003,vcedpaste,
    (TEXT *)"play",         5019,vcedplay,
    (TEXT *)"record",       5018,vcedrecord,
    (TEXT *)"redo",         5012,vcedredo,
    (TEXT *)"replace",      5004,vcedreplace,
#endif
    (TEXT *)"return",       4002,vcedreturn,
    (TEXT *)"save_buffer",  5008,vcedsbuf,
    (TEXT *)"tab",          4004,vcedtab,
    (TEXT *)"toggle_insert",4014,vcedinstog,
    (TEXT *)"toggle_status",5013,vcedtogstat,
#ifdef VCEDFULL
    (TEXT *)"undo",         5001,vcedundo,
#endif
    NULLTEXT,                  0,(PFI)0,
    };


