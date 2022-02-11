#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define MAX 20
#define FILENAME "/tmp/out"
#define BUFSIZE 1024
#include<errno.h>
#include<string.h>
static  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  //定义临界区
static void* open_add(void *p)
{
        FILE *fp;
        char buf[BUFSIZE];
        fp = fopen(FILENAME,"r+");
        if(fp == NULL)
        {
                perror("fopen()");
                exit(1);
        }
        pthread_mutex_lock(&mutex);   //加锁
        fgets(buf,BUFSIZE,fp);
        fseek(fp,0,SEEK_SET);
//      sleep(1);
        fprintf(fp,"%d\n",atoi(buf) + 1);
        fclose(fp);
        pthread_mutex_unlock(&mutex);  //解锁
        pthread_exit(NULL);
}
int main()
{
        pthread_mutex_init(&mutex,NULL);
        int i,err;
        pthread_t tid[MAX];
        for(i = 0; i< MAX; i++)
        {
                err = pthread_create(tid + i,NULL,open_add,NULL);
                if(err)
                {
                        fprintf(stderr,"pthread_create() %s\n",strerror(err));
                        exit(1);
                }
        }
        for( i = 0; i< MAX;i++)
        {
                pthread_join(tid[i],NULL);
        }
        pthread_mutex_destroy(&mutex);
        exit(1);
}
