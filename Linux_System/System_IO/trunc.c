#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc,char **argv)
{
        if(argc <2)
        {
                fprintf(stderr,"Uage:%s <file>\n");
                exit(1);
        }
        int fp = open(argv[1],O_WRONLY|O_TRUNC);
        if(fp < 0)
        {
                perror("open()");
                exit(1);
        }
        close(fp);
}
