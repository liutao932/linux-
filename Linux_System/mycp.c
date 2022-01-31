#include<stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<stdlib.h>
//#define BUFSIZE 1024


int main(int argc,char **argv)
{
	if(argc <3)
	{
		fprintf(stderr,"Useg:%s<src_file><dest_file>",argv[0]);
	}
	int sfd,dfd,len,ret,pos;
	char buf[BUFSIZE];

	sfd = open(argv[1],O_RDONLY);
	if(sfd < 0)
	{
		perror("open()");
		exit(1);
	}
	dfd = open(argv[2],O_WRONLY|O_TRUNC|O_CREAT);
if(dfd<0)
	{
		perror("open()");
		exit(1);
	}
	
	pos = 0;
	while(1)
	{
		len = read(sfd,buf,BUFSIZE);
		if(len < 0)
		{
			perror("read()");
			break;	
		}	
		if(len == 0)
			break;
		while(len > 0)
		{
			ret = write(dfd,buf+pos,len);
			if(ret < 0)
			{
				perror("wirte()");
				exit(1);
			}
			pos += ret;
			len -= ret;
		}
	}

	close(dfd);
	close(sfd);
}
