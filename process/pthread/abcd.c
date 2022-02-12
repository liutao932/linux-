#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#define MAX 4
//static pthread_mutex_t mutex[MAX];  //锁链
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int num = 0;
static int next(int n)
{
        if(n +1 >= 4)
                return 0;
        return n+1;

}
static void * wirteabcd(void * p)
{
        int n = (int) p;
        int ch = 'a' + n;
        while(1)
        {	
                pthread_mutex_lock(&mutex);  //给自己上锁
		while(num != n)
		{
			pthread_cond_wait(&cond,&mutex);
		}
                write(1,&ch,1);              //临界区
		num = next(num);
		pthread_cond_broadcast(&cond);
                pthread_mutex_unlock(&mutex); //给下一个解锁
        }
        pthread_exit(NULL);
}

int main()
{
        int i,err;
        pthread_t tid[MAX];
        for(i = 0; i< MAX;i++)
        {
 //             pthread_mutex_init(mutex+i,NULL);   //初始化4把锁
 //             pthread_mutex_lock(mutex+i);   //每把锁都上锁
                err = pthread_create(tid +i, NULL,wirteabcd,(void *)i);
                if(err)
                {
                        fprintf(stderr,"%s pthread_create()",strerror(err));
                        exit(1);
                }
        }
       // pthread_mutex_unlock(mutex+0);   //4个线程创建完成后解开第一把锁
        alarm(5);
        for(i = 0; i< MAX;i++)
        {
                pthread_join(tid[i],NULL);
        }
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
}
