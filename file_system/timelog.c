#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#define PATH "/tmp/out"
#define BUFSIZE 1024
int main(int argc,char** argv)
{	
	int count = 0;
	char *buf;
	struct tm * tm;
	time_t sptime;
	FILE * fp = fopen(PATH,"a+");
	if(fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}
		
	while(fgets(buf,BUFSIZE,fp) != NULL)
	{
		++count;
	}
	
	while(1)
	{
		time(&sptime);
		tm = localtime(&sptime);
		fprintf(fp,"%-4d  %d-%d-%d   %d:%d:%d\n",++count,tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday,tm->tm_hour,tm->tm_min,tm->tm_sec);
		fflush(fp);
		sleep(1);
	}

	fclose(fp);
	exit(0);
}
