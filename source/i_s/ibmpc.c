/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:28
*
*   Name            IBM PC Routines
*
*   Description     This functions are for IBM PC under MSDOS
*                  
*
**/

#include <vcstdio.h>

#ifdef IBM

COUNT vcin()
    {
    struct VCREGS ir,or;
    COUNT retval;
    COUNT bufkdy();
    COUNT gbufkey();
    VOID vcint();
    COUNT xkeyrdy();
    while(!xkeyrdy())
        if(waitfunc)
            (*waitfunc)();
#ifdef NOREDIRECT
    ir.ax = 0x1100;
    vcint(0x16,&ir,&or);
    if( (or.ax & 0xff00) == 0x0f00)
        {   /* Regular Keyboard     */
        ir.ax = 0x600;
        ir.dx = 0xff;
        vcint(0x21,&ir,&or);
        retval = or.ax & 0xff;
        ir.ax = 0x200;
        vcint(0x16,&ir,&or);
        vcshift = or.ax & 0xff;
        }
    else
        {   /* Extended Keyboard    */
        ir.ax = 0x1000;
        vcint(0x16,&ir,&or);
        if( (or.ax & 0xff) == 0)
            ungetone((or.ax & 0xff00) >> 8);
        retval = or.ax & 0xff;
        ir.ax = 0x1200;
        vcint(0x16,&ir,&or);
        vcshift = or.ax & 0xff;
        }
#else
    ir.ax = 0x600;
    ir.dx = 0xff;
    vcint(0x21,&ir,&or);
    retval = or.ax & 0xff;
#endif
    return(retval);
    }

COUNT vcout(buf,nbytes)
TEXT *buf;
COUNT nbytes;
    {
    int write();
    return((COUNT)write(1,buf,(int)nbytes));
    }

COUNT xkeyrdy()
    {
    COUNT kbhit();
#ifdef MSC
    struct VCREGS i,o;
#endif
    COUNT retval;
#ifdef MSC
#ifdef NOREDIRECT
    i.ax = 0x1100;
    vcint(0x16,&i,&o);
    if( (o.ax & 0xff00) == 0x0f00)
        {  
        retval = kbhit();   /* Must be regular keyboard            */
        i.ax = 0x200;
        vcint(0x16,&i,&o);
        vcshift = o.ax & 0xff;
        return(retval);
        }
    else
        {                                /* Extended Keyboard       */
        retval = (o.es & 0x40) ? 0 : 1 ; /* Check the zero flag     */
        i.ax = 0x1200;
        vcint(0x16,&i,&o);
        vcshift = o.ax & 0xff;
        return(retval);
        }
#else
    return((COUNT)kbhit());
#endif
#endif
#ifdef LC
    return((COUNT)kbhit());
#endif
#ifdef CI
    struct VCREGS i,o;
    i.ax=0x100;
    return( (sysint(0x16,&i,&o) & 0x40) ? 0 : 1);
#endif
#ifdef MW
    struct { COUNT ax,bx,cx,dx,si,di,ds,es,flags; }i,o;
    i.ax=0x100;
    invcall(&i,&o,0x16);
    return( (o.flags & 0x40) ? 0 : 1);
#endif
#ifdef AZ
    struct VCREGS i,o;
    i.ax=0x100;
    return( (sysint(0x16,&i,&o) & 0x40) ? 0 : 1);
#endif
    }

#endif




