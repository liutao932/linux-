#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <pwd.h>
int main(int argc,char **argv)
{
	if(argc <2)
	{
		fprintf(stderr,"Usage:<usrid>%s\n",argv[0]);
		exit(1);
	}
	struct passwd * passwdres =  getpwuid(atoi(argv[1]));
	puts(passwdres->pw_name);
}
