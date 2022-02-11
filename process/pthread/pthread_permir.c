#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define BEGIN 30000000
#define END   30000200
#define MAXSIZE 4
static pthread_mutex_t mutex_num = PTHREAD_MUTEX_INITIALIZER;
static int num = 0;
struct pthread_org_st
{
        int n;
};
void *pthread_permir(void *p);
int main()
{
        int i,err;
        pthread_t tid[MAXSIZE];
        struct pthread_org_st * st;
        for(i =0; i< MAXSIZE;i++)
        {
                st = (struct pthread_org_st*)malloc(sizeof(struct pthread_org_st));
                if(st == NULL)
                {
                        perror("mallo()");
                        exit(1);
                }
                st->n = i;
                err = pthread_create(tid+ i,NULL,pthread_permir,st);
                if(err)
                {
                        perror("pthread_create()");
                        exit(1);
                }
        }

        for(i = BEGIN;i<=END;i++)    //线程池--------main线程
        {
                pthread_mutex_lock(&mutex_num); //查看num临界区上锁
                while(num != 0)
                {
                        pthread_mutex_unlock(&mutex_num); //不为0，main线程出让临界区。
                        sched_yield(); //出让调度器，不会发生调度器颠簸
                        pthread_mutex_lock(&mutex_num);
                }
                num = i;
                pthread_mutex_unlock(&mutex_num);
        }
        while(num != 0) //当num 为最后一个数时
        {
                pthread_mutex_lock(&mutex_num);
                sched_yield();
                pthread_mutex_unlock(&mutex_num);
        }
        num = -1;
        for(i = 0;i<MAXSIZE ;i++)
        {
                pthread_join(tid[i],NULL);
        }
        pthread_mutex_destroy(&mutex_num);
        exit(0);
}
void *pthread_permir(void *p)
{
        int i,j;
        int k  = ((struct pthread_org_st *)p)->n;
        while(1)
        {
                pthread_mutex_lock(&mutex_num);
                while(num ==0)
                {
                        pthread_mutex_unlock(&mutex_num);
                        sched_yield();
                        pthread_mutex_lock(&mutex_num);
                }
                //if(num == -1)
                //      break;      //严重错误，其他线程还在等待，break会发生死锁

                if(num == -1)
                {
                        pthread_mutex_unlock(&mutex_num); // 在退出之前解开锁
                        break;
                }
                i = num;
                num = 0;
                pthread_mutex_unlock(&mutex_num);
                int mark = 1;
                for( j = 2; j < i /2; j++)
                {
                        if( i % j == 0)
                        {
                                mark = 0;
                        }
                }
                if(mark)
                {
                        printf("pthread[%d]:::%d is permir\n",k,i);
                }
        }
        pthread_exit(NULL);
}
