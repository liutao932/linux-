#include<stdio.h>
#include<stdlib.h>
 #define MAXSIZE 1024
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc,char ** argv)
{
        int ret = 0, len = 0, pos = 0;
        char buf[MAXSIZE];
        if(argc <3)
        {
             fprintf(stderr,"Uage:%s<srcfile><dstfile>",argv[0]);
             exit(1);
        }
        int fd,fp;
        fd = open(argv[1],O_RDONLY);
        if(fd <0)
        {
             perror("open");
             exit(1);
        }
        fp = open(argv[2],O_WRONLY|O_CREAT,O_TRUNC,0777);
        if(fp < 0)
        {
             perror("open");
             close(fd);
             exit(1);
        }
        while(1)
        {
            len  = read(fd,buf,MAXSIZE);
            if(len <0)
            {
                perror("read");
                break;
            }
            if(len  == 0)
                 break;
            pos = 0;
            while(len > 0)
            {
                ret = write(fp,buf+pos,len);
                if(ret <0)
                {
                   perror("wirte()");
                   exit(1);
                }
                pos += ret;
                len -=ret;
            }
        }
        close(fp);
        close(fd);
}
