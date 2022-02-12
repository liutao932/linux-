#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define BEGIN 30000000
#define END   30000200
#define MAXSIZE END - BEGIN + 1
#define N 4
#include "mysem.h"
struct mysem_t * me;
struct pthread_org_st
{
        int n;
};
void *pthread_permir(void *p);
int main()
{
        int i,err;
	me = mysem_init(N);
	if(me == NULL)
	{
		exit(1);
	}
        pthread_t tid[MAXSIZE];
        struct pthread_org_st * st;
        void * ptr;
        for(i =BEGIN; i<= END;i++)
        {
                st = (struct pthread_org_st*)malloc(sizeof(struct pthread_org_st));
                if(st == NULL)
                {
                        perror("mallo()");
                        exit(1);
                }
                st->n = i;
		mysem_sub(me,1);
                err = pthread_create(tid+ (i- BEGIN),NULL,pthread_permir,st);
                if(err)
                {
                        perror("pthread_create()");
                        exit(1);
                }
        }
        for(i = BEGIN;i<=END;i++)
        {
                pthread_join(tid[i-BEGIN],&ptr);
                free(ptr);
        }
	mysem_destroy(me);
        exit(0);
}
void *pthread_permir(void *p)
{
        int j;
        int i = ((struct pthread_org_st *)p)->n;
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
                printf("%d is permir\n",i);
        }
	sleep(5);
	mysem_add(me,1);
        pthread_exit(p);
}
