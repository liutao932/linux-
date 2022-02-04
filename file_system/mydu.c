#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<glob.h>
#define PATHSIZE  1024
static int gl_noloop(const char * name)
{
	char *pos;
	pos = strrchr(name,'/');
	if(pos == NULL)
	{
		fprintf(stderr,"point is NULL");
		exit(1);
	}	
	if(strcmp(pos+1,".") == 0 || strcmp(pos+1,"..") == 0)
		return 0;
	else	
		return 1;
	
}
static int64_t mydu(const char *Fname)
{	
	static struct stat statres;
	static char PathName[PATHSIZE];
	glob_t globres;
	int i;
	int64_t sum;
	if(lstat(Fname,&statres) < 0)
	{
		perror("stat()");
		exit(1);
	}
	if(!S_ISDIR(statres.st_mode))
		return statres.st_blocks;
	strncpy(PathName,Fname,PATHSIZE);
	strncat(PathName,"/*",PATHSIZE);
	glob(PathName,0,NULL,&globres);

	strncpy(PathName,Fname,PATHSIZE);
        strncat(PathName,"/.",PATHSIZE);
        glob(PathName,GLOB_APPEND,NULL,&globres);

	sum = statres.st_blocks;
	for(i =0; i<globres.gl_pathc;i++)
	{	
		if(gl_noloop(globres.gl_pathv[i]))
		{
			sum += mydu(globres.gl_pathv[i]);
		}	
	}
	globfree(&globres);
	return sum;

}


int main(int argc,char **argv)
{
	if(argc <2)
	{
		fprintf(stderr,"Usage:%s\n",argv[1]);
		exit(1);
	}
	printf("%lld\n",mydu(argv[1])/ 2);
	exit(0);
}

