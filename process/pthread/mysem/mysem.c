#include"mysem.h"


mysem* mysem_init(int n)
{
	struct mysem_t* me = (struct mysem_t*)malloc(sizeof(struct mysem_t));
	if(me == NULL)
	exit(1);
	me->initval = n;
	pthread_mutex_init(&me->mutex,NULL);
	pthread_cond_init(&me->cond,NULL);
	return me;
}

int mysem_add(mysem* ptr,int n)
{
	struct mysem_t * me = ptr;
	pthread_mutex_lock(&me->mutex);
		
	me->initval += n;
	pthread_cond_broadcast(&me->cond);
	pthread_mutex_unlock(&me->mutex);
	return n;
}


int mysem_sub(mysem* ptr,int n)
{
	struct mysem_t * me = ptr;
	pthread_mutex_lock(&me->mutex);
	
	while(me->initval < n)
	{
		pthread_cond_wait(&me->cond,&me->mutex);	
	}	
	me->initval -= n ;
	pthread_mutex_unlock(&me->mutex);
	return n;
}


int mysem_destroy(mysem* ptr)
{
	struct mysem_t * me = ptr;
	pthread_mutex_destroy(&me->mutex);
	pthread_cond_destroy(&me->cond);
	return 0;
}

