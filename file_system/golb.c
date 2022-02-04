#include<stdio.h>
#include<stdlib.h>
#include<glob.h>
#define PAT "/etc/*"
int main()
{
	int i;
	glob_t ret;
	int res = glob(PAT,0,NULL,&ret);
	if(res)
	{
		printf("Error Code %d\n",res);
		exit(1);	
	}
	for(i = 0; i<ret.gl_pathc;i++)
	{
		puts(ret.gl_pathv[i]);
	}		
	globfree(&ret);
	exit(0);
	
}

