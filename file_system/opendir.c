#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include <sys/types.h>
#define PAT "/etc"
int main()
{
 	DIR *dp;
	dp = opendir(PAT);
	if(dp == NULL)
	{
		perror("opendir()");
		exit(1);
	}
	struct dirent *cur;
	while((cur = readdir(dp)) != NULL)
	{	
		puts(cur->d_name);
	}	
	closedir(dp);
	exit(0);
}	

