/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 9/1/90 at 00:35:41
*
*   Name            helpgen -- Vitamin C help generator
*                                   
*   Description     Generates a help index for vchelp to use             
*
*   Return Value    None               
*                                   
**/                                 

#include <vcstdio.h>

#define FNAMLEN 32

main()
    {
    FILE *ofil,             /* pointer to output file */
         *ifil,             /*    "     " input file  */
         *fopen();
    TEXT inname[FNAMLEN],   /* input file name space  */
         outname[FNAMLEN],  /* output "     "    "    */
         msgbuf[80],        /* used to format output  */
         answer[2];
    COUNT n,cnt,ynonly();
    TEXT *ttrim();
    COUNT vcsmall();
    VOID empty();
    WPTR wopen();
    VOID atsay();
    COUNT atsayget();
    COUNT readgets();
    COUNT isblank();
    COUNT wclose();
    VOID terror();
    VOID at();
    VOID eraeol();
    TEXT *strcpy();
    COUNT xatget();
    COUNT strcmp();
    COUNT buildhlp();
    VOID hlpsort();
    VOID getone();
    VOID vcend();
    TEXT *vcalloc();

    vcsmall(CLRSCRN);

    empty(inname,FNAMLEN);
    empty(outname,FNAMLEN);
    empty(answer,2);

    wopen(0,0,vcterm.rows-1,vcterm.cols-1,
                   "Vitamin C Help File Generator");
    atsay(1,13,"Copyright (c) 1985-1990 by Creative Programming");
    atsay(2,24,"For Use Only By Original Owner.");

    atsay(5,2,"This program can be used  to  extract  keywords  from a text file that was");
    atsay(6,2,"prepared according to the  conventions  outlined  in the Vitamin C.");
    atsay(7,2,"The key words and their  offset  from  the  beginning of the file are then");
    atsay(8,2,"written to a help index file for later use with the Vitamin C Help.");

retry1:
    atsayget(10,2,"Enter input file ................... ",inname,NULL);
    readgets();

    if( isblank(inname) )
        {
        wclose(wdoctrl->wcurrent);
        terror("No input file given.  End run.");
        }
    if( (ifil=fopen(ttrim(inname),VCF_RB)) == (FILE *)NULL)
        {
        atsay(12,2,"File not found.  Try Again.");
        goto retry1;
        }
    fclose(ifil);
    at(12,2);
    eraeol();

    n=0;
    while(inname[n]!=' ' && inname[n]!='.')
        {
        outname[n]=inname[n];
        n++;
        }
    if(n+4<FNAMLEN)
        {
        outname[n]='.';
        outname[n+1]='n';
        outname[n+2]='d';
        outname[n+3]='x';
        }

retry2:
    atsayget(12,2,"Enter output file .................. ",outname,
            "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    readgets();

    if( isblank(outname) )
        {
        wclose(wdoctrl->wcurrent);
        terror("No output file given.  End run.");
        }

    if( (ifil=fopen(ttrim(outname),VCF_RB)) != NULL)
        {
        strcpy(answer,"N");
        atsay(14,2,"Output file exists.  Overwrite ?  Y/N");
        xatget(14,40,answer,"X",ynonly,NULL,NULL,vc.dflt,vc.dflt);
        readgets();
        if(strcmp("Y",answer))
            {
            at(14,0);
            eraeol();
            goto retry2;
            }
        else
            {
            at(14,0);
            eraeol();
            fclose(ifil);
            }
        }
    else
        fclose(ifil);

    hlpndx = (struct HLP_STR *)vcalloc(MAXHLP+1,sizeof(*hlpndx),vcdebug);
    atsay(16,2,"Extracting keywords from help file...");
    strcpy(hlpndx->keyword,"Total Entry");
    
    sprintf(msgbuf,"%d Keywords found",cnt=buildhlp(ttrim(inname),hlpndx));
    atsay(17,2,msgbuf);

    atsay(18,2,"Sorting key words...");

    hlpsort(hlpndx,cnt);

    atsay(19,2,"Writing help index file...");
    if( (ofil=fopen(ttrim(outname),VCF_WB)) == NULL)
        {
        wclose(wdoctrl->wcurrent);
        terror("Can't open output file.");
        }
    fwrite((TEXT *)hlpndx,cnt+1,sizeof(struct HLP_STR),ofil);
    fclose(ofil);

    atsay(20,2,"Done.");
    at(22,0);
    getone();
    vcend(CLOSE);
    }

ynonly(str)
char str[];
    {
    str[0]=toupper(str[0]);
    if(str[0]=='Y' || str[0]=='N')
        return(0);
    else
        return(1);
    }

