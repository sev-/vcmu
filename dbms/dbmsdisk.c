/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:12
*
*   Name            dbmsdisk - database information on disk
*                                   
*   Description     This function save the database information    
*                   on disk rather than to link list
*
*   Return Value    Returns 0 if no errors
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

FILEINFO *dbmsdisk(fileinfo,buffer,mode,parm)
FILEINFO *fileinfo; /* Pointer to file info structure               */
TEXT *buffer;       /* Buffer to add or place new location          */
COUNT mode;         /* Mode (init read add)                         */
LONG parm;          /* Size when openning, rec # for find           */
    {
    FILEINFO *fi = (FILEINFO *)0;
    FILE *vcfopen();
    TEXT *mktemp();
    TEXT template[9];
    TEXT *vcalloc();
    TEXT *strcpy();
    VOID vcfree();
    switch(mode)
        {
        case DBMSINTREC:
            fi = (FILEINFO *)vcalloc(1,sizeof(*fi),vcdebug);
            strcpy(template,"rpXXXXXX");
            fi->fname = vcalloc(1,9,vcdebug);
            strcpy(fi->fname,mktemp(template));
            if( (fi->fptr = vcfopen(fi->fname,"w+b")) == (FILE *)0)
                return((FILEINFO *)0);
            fi->nloc = 0l;
            fi->lloc = 0l;
            fi->fsize = (UCOUNT)parm;
            break;
        case DBMSCLSREC:
            if(fileinfo != (FILEINFO *)0)
                {
                fclose(fileinfo->fptr);
                unlink((char *)fileinfo->fname);
                vcfree(fileinfo->fname,vcdebug);
                vcfree(fileinfo,vcdebug);
                }
            break;
        case DBMSADDREC:
            if(fileinfo != (FILEINFO *)0)
                {
                if((fileinfo->lloc = ftell(fileinfo->fptr)) != fileinfo->nloc)
                    fseek(fileinfo->fptr,fi->nloc,0);
                if(fwrite(buffer,fileinfo->fsize,1,fileinfo->fptr)
                                                != 1)
                    return((FILEINFO *)0);
                fi = fileinfo;
                fi->nloc += fileinfo->fsize;
                }
            break;
        case DBMSFRSREC:
            if(fileinfo != (FILEINFO *)0)
                {
                if(!(fseek(fileinfo->fptr,0l,0)))
                    {
                    fread(buffer,fileinfo->fsize,1,fileinfo->fptr);
                    fi = fileinfo;
                    fi->lloc = 0l;
                    }
                }
            break;
        case DBMSNXTREC:
            if(fileinfo != (FILEINFO *)0)
                {
                fileinfo->lloc += fileinfo->fsize;
                if( fileinfo->lloc <= (fileinfo->nloc-fileinfo->fsize))
                    {
                    if(!(fseek(fileinfo->fptr,fileinfo->lloc,0)) )
                        {
                        fread(buffer,fileinfo->fsize,1,fileinfo->fptr);
                        fi = fileinfo;
                        }
                    }
                }
            break;
        case DBMSEQUREC:
            if(fileinfo != (FILEINFO *)0)
                {
                fileinfo->lloc = parm * fileinfo->fsize;
                if(!(fseek(fileinfo->fptr,fileinfo->lloc,0)) )
                    {
                    fread(buffer,fileinfo->fsize,1,fileinfo->fptr);
                    fi = fileinfo;
                    }
                }
            break;
        case DBMSRWTREC:
            if(fileinfo != (FILEINFO *)0)
                {
                fileinfo->lloc = parm * fileinfo->fsize;
                if(!(fseek(fileinfo->fptr,fileinfo->lloc,0)) )
                    {
                    if(fwrite(buffer,fileinfo->fsize,1,fileinfo->fptr)
                                                != 1)
                        return((FILEINFO *)0);
                    fi = fileinfo;
                    }
                }
            break;
        }
    return(fi);
    }


