#include <stdio.h>
#include <dos.h>

main(argc,argv)
int argc;
char *argv[];
	{
	int more;
	FILE *fout,*fopen();
	struct find_t finfo;
	if(argc < 2)
		{
		printf("delfiles {filenames/or wildcard}");
		exit(0);
		}
	while(argc-- > 1)
		{
		more = _dos_findfirst(argv[argc],_A_NORMAL,&finfo);
		while(!more)
			{
			unlink(finfo.name);
			more = _dos_findnext(&finfo);
			}
		}
	exit(0);
	}




