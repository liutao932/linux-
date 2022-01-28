#include<stdio.h>
#include<stdlib.h>


int main(int argc,char **argv)
{

	if(argc <3)
	{
		fprintf(stderr,"Useg:%s<src_file><dst_file>",argv[0]);
		exit(-1);
	}
	int ch;
	FILE * fbs, *fdb;
	fbs = fopen(argv[1],"r");
	if(fbs == NULL)
	{
		perror("fopen()");
		exit(1);
	}
	fdb = fopen(argv[2],"w");
	if(fdb == NULL)
	{
		fclose(fbs);
		perror("fopen()");
		exit(1);
	}

	while(1)
	{
		ch = fgetc(fbs);
		if(ch == EOF)
		{
			break;
		}
		fputc(ch,fdb);
	}
	fclose(fbs);
	fclose(fdb);
}
