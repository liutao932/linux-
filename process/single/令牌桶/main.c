#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<errno.h>
#include<signal.h>
#define CPS 10
#define BURST 100
#define BUFSIZE 1024
//static volatile int loop = 0;   //正真的内存中取数据，而不让编译器优化，放在寄存器中
static volatile int token = 0;

/*static void alrm_hander(int s)
{
        alarm(1);
        loop = 1;
}*/
static void alrm_hander(int s)
{
        alarm(1);
        token++;
        if(token > BURST)
                token = BURST;
}

int main(int argc,char ** argv)
{
        int ret = 0, len = 0, pos = 0;
        mytbf_t *tbf;
        char buf[BUFSIZE];
        if(argc < 2)
        {
             fprintf(stderr,"Uage:%s<srcfile><dstfile>",argv[0]);
             exit(1);
        }
        int fd;
        int fp = 1;
        tbf = mytbf_init(CPS,BURST);
        if(tbf == NULL)
        {
                fprintf(stderr,"mytbf_init()");
                exit(1);
        }
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
            /*while(!loop)     //信号1秒钟后loop = 1
                pause();
                //;     //死循环cpu占用率高
            loop = 0;
            */
            /*while(token <= 0)
                pause();
            token--;*/
            size = mytbf_fetchtoken(tbf,BUFSZIE);
            if(size < 0)
            {
                    fprintf(stderr,"mytbf_fetchtoken():%s\n",strerror(-size));
            }
            while(( len = read(fd,buf,size)) < 0)
            {
                if(errno == EINTR)
                        continue;
                perror("read");
                break;
            }
            if(len  == 0)
                 break;
            if(size - len >0)
                    mytbf_returntoken(tbf,size-len);
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
           // sleep(1);   this is funtion is unsafe,please alarm() and signal
        }
        mytbf_destroy(tbf);
        close(fd);
}
