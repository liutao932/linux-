#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
static void arlm_handler(int s)
{
        write(1,"!",1);
}
int main()
{
        int i,j;
        sigset_t set;
        signal(SIGINT,arlm_handler);
        sigemptyset(&set);
        sigaddset(&set,SIGINT);

        for( i = 0; i< 1000; i++)
        {
                sigprocmask(SIG_BLOCK,&set,NULL);
                for( j = 0; j< 5; j++)
                {
                        write(1,"*",1);
                }
                printf("\n");
                sleep(1);
                sigprocmask(SIG_UNBLOCK,&set,NULL);
        }
}
