#ifndef _MYSEM_H_
#define _MYSEM_H
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
typedef void mysem;
struct mysem_t
{
	int initval;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};

mysem* mysem_init(int n);

int mysem_add(mysem*,int);


int mysem_sub(mysem*,int);


int mysem_destroy(mysem*);
#endif
