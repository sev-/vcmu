/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:22
*
*   Name            addprokey.c  --  program a key
*
*   Description     Adds a definition to the list of programed key
*
*   Return Value    Returns -1 if error
*                    
*
**/

#define VCPRO_DEFS
#define VCERROR_DEFS

#include <vcstdio.h>

extern VCPROKEY *prokeytbl;

COUNT addprokey(key,func,aux)
COUNT key;
PFI func;
TEXT *aux;
    {
    VCPROKEY *newkey;
    VCPROKEY *scnprokey();
    TEXT *tcalloc();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "addprokey:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( scnprokey(key) )
        {
        vcerror=VCSYMEXTS;
        return(-1);
        }
    newkey = (VCPROKEY *)vcalloc(1,sizeof(VCPROKEY),vcdebug);
    if( newkey == (VCPROKEY *) 0 )
        {
        vcerror=NOMEM;
        return(-1);
        }
    newkey->pro_keycode=key;
    newkey->pro_func=func;
    newkey->pro_aux=aux;
    newkey->pro_magic=PROKEYMAGIC;
    newkey->pro_next=prokeytbl;
    prokeytbl=newkey;
    return(0);
    }

