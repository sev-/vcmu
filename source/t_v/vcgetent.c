/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:51
*
*   Name            vcgetent.c  --  get env
*
*   Description     This function reads the termcap information for
*                   the terminal and puts it into buf and returns -1
*                   if unable to open termcap and 0 if terminal does 
*                   not have entry. This is used to replace Unix 
*                   function because termcap.vc grew to large.
*
*   Return Value    Returns -1 if error, 0 if no entry 
*
**/

#include <vcstdio.h>

#ifdef TERMCAP

COUNT vcgetent(buf,terminal)
TEXT *buf;          /* Buffer to place termcap info                 */
TEXT *terminal;     /* Terminal to get info for                     */
    {
    FILE *vcfopen(),*tcap;
    TEXT *result,*bufptr,*tmpptr,nterm[100];
    TEXT trashline[180];
    TEXT *strchr(),*strsset(),*vcgetenv();
    TEXT *bptr;
    COUNT trash,found = 0;
    COUNT retval = 1;
    COUNT len;
    TEXT *strcpy();
    COUNT fdternam();
    COUNT strlen();
    VOID termsort();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcgetent:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( (buf == NULLTEXT) || (terminal == NULLTEXT) )
        retval = 0;
    strcpy(pathbuf,"/etc/termcap.vc");
    if((tmpptr = vcgetenv("VCTERMCAP")) != NULLTEXT)
        strcpy(pathbuf,tmpptr);
    bufptr = buf;
    if((tcap = vcfopen(pathbuf,VCF_R)) == (FILE *)0)
        retval = -1;
    if(retval != 1)
        return(retval);
    while((result = (TEXT *)fgets(bufptr,210,tcap)) != NULLTEXT)
        {
        if( !found )
            {
            bptr = bufptr;
            while( (*bptr <= ' ') || (*bptr > 'z') )
                {
                if((*bptr == '\n') || (*bptr == '\0'))
                    break;
                bptr++;
                }
            if( (*bptr == '#') || (*bptr == ':') || (*bptr == '\n') || 
                (*bptr == '\0'))
                continue;
            if( !fdternam(bufptr,terminal) )
                continue;
            found=1;
            if(!no_tc)
                {
                while( (trash = fgetc(tcap)) != ':');
                continue;
                }
            }
        if((bptr = strsset(bufptr,":\\")) == NULLTEXT)
            {
            len = strlen(bufptr);
            bptr = bufptr+len-1;
            while((*bptr == ' ') || (*bptr == '\n') || (*bptr == '\\'))
                bptr--;
            if( *bptr != ':' )
                *(++bptr) = ':';
            *(++bptr) = ' ';
            *(++bptr) = ' ';
            *(++bptr) = '\0';
            break;
            }
        else
            {
            while(TRUE)
                {
                while( ((trash = fgetc(tcap)) == ':') || 
                       (trash == '\t') || (trash == ' ') );
                if(trash == '#')
                    {
                    if((TEXT *)fgets(trashline,179,tcap) == NULLTEXT)
                        break;
                    }
                else
                    break;
                }
            bufptr = bptr+1;
            *(bufptr++) = trash;
            }
        }
    fclose(tcap);
    if( bufptr == buf)
        retval = 0;
    if( no_tc && ((bufptr = strsset(buf,":tc=")) != NULLTEXT))
        {
        no_tc = FALSE;
        result = bufptr++;
        result += 4;
        tmpptr = &nterm[0];
        while( (*result != ':') && (*result != ' ') && 
               (*result != '\0') && (*result != '\n') )
            *(tmpptr++) = *(result++);
        *tmpptr = '\0';
        retval = vcgetent(bufptr,&nterm[0]);
        no_tc = TRUE;
        }
    chbuf = buf;
    if(no_tc && (retval == 1))
        {
        termsort();
        no_tc = TRUE;
        }
    return(retval);    
    }

#endif


