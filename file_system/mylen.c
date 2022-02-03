#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
static struct stat*  Flen(const char *Fname)
{
	struct stat* ret = (struct stat *) malloc(sizeof(struct stat));
	if(ret == NULL)
	{
		printf("malloc is error\n");
	}
	if(stat(Fname,ret) < 0)
	{
		perror("stat()");
	}
	return ret;
}

int main(int argc,char **argv)
{
	if(argc < 2)
	{
		fprintf(stderr,"Usage:%s<src_file>\n",argv[1]);
		exit(1);
	}
	//printf("%lld\n",(long long )Flen(argv[1]));
	struct stat* res = Flen(argv[1]);
	printf("%d  %lld  %d  %d\n",res->st_mode,(long long )res->st_size,res->st_gid,res->st_uid);
}	
