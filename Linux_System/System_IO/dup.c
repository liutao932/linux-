#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#define FILENAME "/tmp/out.txt"

int main()
{
	close(1); // 关闭标准输出
	int fp = open(FILENAME,O_WRONLY|O_CREAT|O_TRUNC,0600);
	if(fp < 0)
	{
		perror("open()");
	}
	puts("hello world\n");
	exit(0);
}

