/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:08
*
*   Name            vcint.c  --  interupt Call
*
*   Description     Sets up and makes interupt call on IBM
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>
#ifdef MSC
#include <dos.h>
#endif

#ifdef IBM

VOID vcint(vec,ir,or)
PFAST COUNT vec;    /* Interrupt vector                             */
struct VCREGS *ir;  /* Input regs                                   */
struct VCREGS *or;  /* Output regs                                  */
        {
#ifdef MSC
    COUNT int86x();
    struct SREGS segregs;    
#endif
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcint:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef CI
        sysint(vec,ir,or);
#endif
#ifdef AZ
    sysint(vec,ir,or);
#endif
#ifdef LC
        int86(vec,ir,or);
#endif
#ifdef MSC
    segregs.es = ir->es;
    segregs.ds = ir->ds;
    int86x(vec,(union REGS *)ir,(union REGS *)or,&segregs);
#endif
#ifdef MW
        struct mwreg {
        unsigned r_ax;
        unsigned r_bx;
        unsigned r_cx;
        unsigned r_dx;
        unsigned r_si;
        unsigned r_di;
        unsigned r_ds;
        unsigned r_es;
        unsigned r_flags;
        }  iregs,oregs;
        iregs.r_ax=ir->ax;
        iregs.r_bx=ir->bx;
        iregs.r_cx=ir->cx;
        iregs.r_dx=ir->dx;
        iregs.r_si=ir->si;
        iregs.r_di=ir->di;
        iregs.r_es=ir->es;
        iregs.r_ds=ir->ds;
        intcall(&iregs,&oregs,vec);
        or->ax=oregs.r_ax;
        or->bx=oregs.r_bx;
        or->cx=oregs.r_cx;
        or->dx=oregs.r_dx;
        or->si=oregs.r_si;
        or->di=oregs.r_di;
        or->es=oregs.r_es;
        or->ds=oregs.r_ds;
#endif
#ifdef DESMET
        extern COUNT _rax,_rbx,_rcx,_rdx,_rsi,_rdi,_res,_rds;
        _rax=ir.ax;
        _rbx=ir.bx;
        _rcx=ir.cx;
        _rdx=ir.dx;
        _rsi=ir.si;
        _rdi=ir.di;
        _res=ir.es;
        _rds=ir.ds;
        _doint(vec);
        or.ax=_rax;
        or.bx=_rbx;
        or.cx=_rcx;
        or.dx=_rdx;
        or.si=_rsi;
        or.di=_rdi;
        or.es=_res;
        or.ds=_rds;
#endif
        }

#endif


