#include <stdio.h>
#include <dos.h>

main(argc,argv)
int argc;
char *argv[];
	{
	int error;
	FILE *fout,*fopen();
	struct find_t finfo;
	if(argc < 2)
		{
		printf("makeresp {filespec}");
		exit(1);
		}
	error = _dos_findfirst(argv[1],_A_NORMAL,&finfo);
	if((fout = fopen("response","w+")) != (FILE *)0)
		{
		while(!error)
			{
			fprintf(fout,"+%s ",finfo.name);
			if(!(error = _dos_findnext(&finfo)))
				fprintf(fout,"&");
			fprintf(fout,"\n");
			}
		fclose(fout);
		}
	exit(0);
	}




