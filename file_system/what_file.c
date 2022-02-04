#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
static int Myfile(const char* Fname)
{
	struct stat ret;
	if(stat(Fname,&ret) < 0)
	{	
		perror("stat()");
	}
	if (S_ISREG(ret.st_mode))
		return '-';
	else if(S_ISDIR(ret.st_mode))
		return 'd';
	else if(S_ISCHR(ret.st_mode))
		return 'c';
	else if(S_ISBLK(ret.st_mode))
		return 'b';
	else if(S_ISFIFO(ret.st_mode))
		return 'p';
	else if(S_ISLNK(ret.st_mode))
		return 'l';
	else if(S_ISSOCK(ret.st_mode))
		return 's';
	else
		return '?';
}
int main(int argc,char **argv)
{
	if(argc < 2)
	{
		fprintf(stderr,"Usage:%s\n",argv[1]);
	}
	printf("%c",Myfile(argv[1]));
}
