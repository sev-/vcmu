/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:46
*
*   Name            hprint.c  --  print help text in window
*
*   Description     print help text into window
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID hprint(wptr)
WPTR wptr;          /* Pointer to window to print help messages     */
    {
    COUNT outndx,wrdndx,bufndx,lcount,lineflag;
    TEXT *p,buf[81],word[81],line[81],*strcpy();
    COUNT putit = 0;
    COUNT statcode = 0;  /* if 1, terminate help msg in middle */
    COUNT ntemp;
    VOID atsay();
    COUNT getone();
    COUNT strlen();
    VOID ERASE();
    COUNT key;
    VOID woff();
    VOID won();
    VOID bell();
    COUNT wshow();
#ifdef AZ
    TEXT *fgets();
#endif
#ifdef VCDEBUG
    vcdebug = (TEXT *) "hprint:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    strcpy(line,"Help Message Not Found.");
    outndx = lcount = 0;
    p = buf;
loop1:
    if(statcode)
        return;
    woff();
    if(p == NULLTEXT)
        {
        line[outndx]='\0';
        atsay(lcount,1,line);
        atsay(wptr->depth-1,wptr->width-8,"End...");
        while(TRUE)
            {
            if(!(wdoctrl->wcurrent->wctrl & ACTIVE))
                wshow(wdoctrl->wcurrent);
            if(wdoctrl->wfreeze)
                won();
            key = getone();
            if(hlphk2 != NULLFUNC)
                key = (*hlphk2)(key);
            if(key == spkey.xhkey)
                break;
            bell();
            }
        if(wdoctrl->wfreeze)
            won();
        return;
        }
    bufndx = wrdndx = 0;
    p = (TEXT *)fgets(buf,sizeof(buf)-1,hlpfil);
loop2:
    wrdndx=0;
    while(buf[bufndx]!='\0')
        {
        if( buf[bufndx]=='\\' )  /* ESC sequence added 8/4/86 */
            bufndx++;
        else
            if( buf[bufndx] ==' ' || buf[bufndx] == NLCHAR ||
               buf[bufndx] =='\n' || buf[bufndx] == '\r' || buf[bufndx] == '@')
                 break;
        lineflag=0;
        word[wrdndx++]=buf[bufndx++];
        }
    word[wrdndx++]='\0';
    if(buf[bufndx]=='@')
        {
        p = NULLTEXT;
        goto loop1;
        }
    if(outndx+strlen(word)+1 < wptr->width-2 && buf[bufndx] )
        {
        if(outndx>0)
            line[outndx++]=' ';
        for(ntemp=0;ntemp<strlen(word);ntemp++)
            line[outndx++]=word[ntemp];
        if(buf[bufndx]==NLCHAR) /* this is new line symbol NLCHAR */
            {
            line[outndx]='\0';
            putit = 1;    
            bufndx++;
            }
        }
    else
        {
        line[outndx]='\0';
        putit = 1;
        }

    if(putit)
        {
        atsay(lcount++,1,line);
        outndx=0;
/*      if(putit==NLCHAR)
*/          for(ntemp=0;ntemp<strlen(word);ntemp++)
                line[outndx++]=word[ntemp];
        putit = 0;
        }

    if(lcount == wptr->depth-1)
        {
        atsay(wptr->depth-1,wptr->width-9,"more...");
        if(!(wdoctrl->wcurrent->wctrl & ACTIVE))
            wshow(wdoctrl->wcurrent);
        if(wdoctrl->wfreeze)
            won();
        key = getone();
        if(hlphk2 != NULLFUNC)
            key = (*hlphk2)(key);
        if(key == spkey.xhkey)
            {
            statcode = 1;
            goto loop1;
            }
        woff();
        lcount=0;
        ERASE();
        }


    if(buf[bufndx] == '\r' || buf[bufndx] == '\n' || buf[bufndx]=='\0')
        {
        if(buf[bufndx] == '\n')
            {
            if(lineflag == 1)
                {
                line[outndx]='\0';
                atsay(lcount++,1,line);
                outndx=0;
                for(ntemp=0;ntemp<strlen(word);ntemp++)
                    line[outndx++]=word[ntemp];
                }
            else
                lineflag = 1;
            }

        if(lcount == wptr->depth-1)
            {
            atsay(wptr->depth-1,wptr->width-9,"more...");
            if(!(wdoctrl->wcurrent->wctrl & ACTIVE))
                wshow(wdoctrl->wcurrent);
            if(wdoctrl->wfreeze)
                won();
            key = getone();
            if(hlphk2 != NULLFUNC)
                key = (*hlphk2)(key);
            if(key == spkey.xhkey)
                {
                statcode = 1;
                goto loop1;
                }
            woff();
            lcount=0;
            ERASE();
            }

        bufndx=0;
        goto loop1;
        }
    else
        {
        if(buf[bufndx]==' ')
            {
            while(buf[bufndx]==' ')
                bufndx++;
            }
        goto loop2;
        }
    }


  
