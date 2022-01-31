#include<stdio.h>
#include <fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#define PATH "/tmp/mytmp/src_file"
int main()
{
	int fp = open(PATH,O_RDWR);
	if(fp < 0)
	{
		perror("open()");
		exit(1);
	}
	dup2(fp,1);
	if(fp != 1)
	close(fp);
	puts("hello world");
		
}
