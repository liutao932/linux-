#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
#define BUFSIZE 1024
int main()
{
	char buf[BUFSIZE];
	time_t sptime = time(NULL);
	struct tm * tm = localtime(&sptime);
	strftime(buf,BUFSIZE,"Now:%Y-%m-%d",tm);
	
	puts(buf);

	tm->tm_mday += 100;
	mktime(tm);
	strftime(buf,BUFSIZE,"Aften 100 :%Y-%m-%d",tm);
	puts(buf);
}
