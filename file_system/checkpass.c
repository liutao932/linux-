#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#define _XOPEN_SOURCE       /* See feature_test_macros(7) */
#include <unistd.h>
#include <shadow.h>
#include <crypt.h>
int main(int argc,char **argv)
{
	if(argc <2)
	{
		fprintf(stderr,"Usage:<username>%s",argv[1]);
		exit(1);
	}
	char *crypt_pass;	
	char * input_pass = getpass("Please input passwwd:");
	struct spwd *pwdline = getspnam(argv[1]);
	crypt_pass = crypt(input_pass,pwdline->sp_pwdp);
	if(strcmp(crypt_pass,pwdline->sp_pwdp) == 0)
		puts("Ok");
	else
		puts("Fail");
	exit(0);
}
