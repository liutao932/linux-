#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#define BUFSIZE 1024
#define STRTIME 1024
int main(int argc,char **argv)
{
	char buf[BUFSIZE];
	char strtime[STRTIME];
	strtime[0]='\0';
	time_t sptime = time(NULL);
	struct tm * tm = localtime(&sptime);
	while(1)
	{
		int ch = getopt(argc,argv,"yH:MmSd");
		if(ch <0)
		{	
			break;
		}
		switch(ch)
		{
			case 'y':
				/*if(strcmp(optarg,"2") == 0)
				{
					strncat(strtime,"%y ",STRTIME);
				}
				else if(strcmp(optarg,"4") == 0)
				{
					strncat(strtime,"%Y ",STRTIME);
				}
				else
					fprintf(stderr,"Invild error");*/
					strncat(strtime,"%Y ",STRTIME);
				break;
			case 'H':
				if(strcmp(optarg,"12") == 0)
				{
					strncat(strtime,"%I(%p) ",STRTIME);
				}
				else if(strcmp(optarg,"24") == 0)
				{
					strncat(strtime,"%H ",STRTIME);
				}
				else
                                        fprintf(stderr,"Invild error");
				break;
			case 'M':
				strncat(strtime,"%M ",STRTIME);
				break;
			case 'm':
				strncat(strtime,"%m ",STRTIME);
				break;
			case 'S':
				strncat(strtime,"%S ",STRTIME);
				break;
			case 'd':
				strncat(strtime,"%d ",STRTIME);
				break;
			default:
				break;
		}
	}
	strftime(buf,BUFSIZE,strtime,tm);
	
	puts(buf);

}
