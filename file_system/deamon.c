#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#define FILENAME "/tmp/out"
static int deamonsize(void)
{
        int fd;
        pid_t pid;
        pid = fork();
        if(pid < 0)
        {
                perror("fork()");
                return -1;
        }
        if(pid > 0)
                exit(0);

        fd = open("/dev/null",O_RDWR);
        if(fd < 0)
        {
                perror("open()");
                return -1;
        }
        dup2(fd,0);
        dup2(fd,1);
        dup2(fd,2);
        if(fd > 2)
                close(fd);
                setsid();
                chdir("/");
                //umask(0);
        return 0;
}
int main()
{
        FILE * fp = NULL;
        int i;
        if(deamonsize())
                exit(1);
        fp = fopen(FILENAME,"w");
        if(fp == NULL)
        {
                perror("fopen()");
                exit(1);
        }
        for(i = 0; ; ++i)
        {
                fprintf(fp,"%d\n",i);
                fflush(NULL);
                sleep(1);
        }

        exit(0);
}
