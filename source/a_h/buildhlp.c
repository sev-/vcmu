/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:06
*
*   Name            buildhlp.c  --  build help file index
*
*   Description     This function reads through a file looking for
*                   @@keyword and creates and index of the keywords
*                   and their location in the file. It returns the
*                   number of keywords found
*
*   Return Value    Returns number of keywords found
*
**/

#include <vcstdio.h>

COUNT buildhlp(filnam,hndx)
TEXT *filnam;       /* File name of help file                       */
struct HLP_STR *hndx; /* Pointer to help index                      */
    {
    FILE *fp,*vcfopen();
    COUNT len;
    TEXT buffer[512];
    struct HLP_STR *hp;
#ifdef VMS
    int ftell();
    int flag = FALSE;
#else
#ifdef PRIMOS
    int ftell();
#else
    LONG ftell();
#endif
#endif
    VOID exit();
    FAST COUNT counter=0;
    VOID terror();
    TEXT *ttrim();
    TEXT *strncpy();
    TEXT *strcpy();
    TEXT *strcat();
    COUNT strncmp();
    TEXT buf[100];
#ifdef VCDEBUG
    vcdebug = (TEXT *) "buildhlp:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( (fp = vcfopen(filnam,VCF_RB)) == (FILE *)0)
        {
        strcpy(buf,"Cant open file ");
        if(filnam != NULLTEXT)
            strcat(buf,filnam);
        terror(buf);
        }
    hp = hndx;
    while( (fgets(buffer,511,fp) != (char *)0) && (counter < MAXHLP))
        {
#ifdef VMS
        if(flag)
            hp->filloc = (LONG)ftell(fp);
        flag = FALSE;
#endif
        if(strncmp(buffer,"@@",2))
            continue;
        /* at this point, have found '@@'       */
        counter++;
        hp++;
        empty(&hp->keyword[0],11);
        len = 0;
        while(len < 11)
            {
            if(buffer[len+2] < ' ')
                break;
            hp->keyword[len] = buffer[len+2];
            len++;
            }
        hp->keyword[len] = '\0';
        allcaps(hp->keyword);
#ifdef VMS
        flag = TRUE;
#else
#ifdef PRIMOS
        hp->filloc = (LONG)ftell(fp);
#else
        hp->filloc = ftell(fp);
#endif
#endif
        }
    fclose(fp);
    hndx->filloc = counter;
    return(counter);
    }

