#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<errno.h>
#define PAS 10
#define MAXSIZE PAS
int main(int argc,char ** argv)
{
        int ret = 0, len = 0, pos = 0;
        char buf[MAXSIZE];
        if(argc < 2)
        {
             fprintf(stderr,"Uage:%s<srcfile><dstfile>",argv[0]);
             exit(1);
        }
        int fd;
        int fp = 1;
        do{

                fd = open(argv[1],O_RDONLY);
                if(fd <0)
                {
                   if(errno != EINTR)
                   {
                     perror("open");
                     exit(1);
                   }
                }
        }while(fp < 0);

        while(1)
        {
            len  = read(fd,buf,MAXSIZE);
            if(len <0)
            {
                if(errno == EINTR)
                        continue;
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
            sleep(1);
        }
        close(fd);
}
