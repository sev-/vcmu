/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:51
*
*   Name            vcsignal.c - fancy signal handling for unix
*                                   
*   Description     Sets up better signal handling for unix
*
*   Return Value    VOID
*                                   
**/

#include <vcstdio.h>

#ifdef UNIX

#include <signal.h>

VOID vcsignal()
    {
    VOID vcintsig();
    VOID vcquitsig();
    VOID vcillsig();
    VOID vcfpesig();
    VOID vcbussig();
    VOID vcsegvsig();
#ifdef SIGTSTP
    VOID vcstopsig();
    VOID vccontsig();
#endif
    signal(SIGINT,vcintsig);
    signal(SIGQUIT,vcquitsig);
    signal(SIGILL,vcillsig);
    signal(SIGFPE,vcfpesig);
    signal(SIGBUS,vcbussig);
    signal(SIGSEGV,vcsegvsig);
#ifdef SIGTSTP
    signal(SIGTSTP,vcstopsig);
    signal(SIGCONT,vccontsig);
#endif
    }

VOID vcintsig()
    {
    signal(SIGINT,SIG_IGN);
    if(askmsg("Interrupt","Abort Process ",'n'))
        {
        vcend(0);
        terror("Terminated by user");
        }
    signal(SIGINT,vcintsig);
    }

VOID vcquitsig()
    {
    signal(SIGQUIT,SIG_IGN);
    if(askmsg("Interrupt","Abort Process ",'n'))
        {
        vcend(0);
        terror("Terminated by user");
        }
    signal(SIGQUIT,vcquitsig);
    }

VOID vcillsig()
    {
    vcend(0);
    terror("illegal instruction");
    }

VOID vcfpesig()
    {
    vcend(0);
    terror("floating point exception");
    }

VOID vcbussig()
    {
    vcend(0);
    terror("bus error");
    }

VOID vcsegvsig()
    {
    vcend(0);
    terror("segmentation violation");
    }

#ifdef SIGTSTP
VOID vcstopsig()
    {
    set_normal();
    flipattr(normattr);
    if((vcterm.ge != NULLTEXT) && graphattr)
        dist_str(vcterm.ge,0);
    if(vcterm.es != NULLTEXT)
        sendpstr(vcterm.es);
    kill(getpid(),SIGSTOP);
    }

VOID vccontsig()
    {
    if(vcterm.is != NULLTEXT)
        dist_str(vcterm.is,0);
    set_raw();
    wrefresh(TRUE);
    }
#endif

#endif
