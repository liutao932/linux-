#include<stdio.h>
#include<stdlib.h>
#include"mytbf.h"

static mytbf* job [MYTBFSIZE];
static int inited = 0;
struct mytbf_t
{
        int cps;
        int burst;
        int token;
        int pos;
};
static int get_free_pos()
{
        int i;
        for(i = 0; i< MYTNFSIZE;i++)
        {
                if(job[i] == NULL)
                        return i;
        }
}
static void alrm_handler(int s)
{
        int i;
        alarm(1);
        for(i = 0; i<MYTBFSIZ;i++)
        {
                job[i]->token += job[i]->cps;
                if(job[i]->token > job[i]->burst)
                        job[i]->token = job[i]->burst;
        }
}

static void module_laod(void)
{
        signal(SIGALRM,alrm_handler);
        alarm(1);
        ateixt(module_unload);
}
static void module_unload(void)
{
        inti;
        signal(SIGALRM,alrm_handler);
        alarm(0);
        for(i = 0; i<BTFSIZE;i++)
                free(job[i]);
}
mytbf_t mytbf_init(int cps,int burst)
{
        struct mytbf *me;
        if(!inited)
        {
                module_laod();
                inited = 1;
        }
        int pos;
        pos = get_free_pos();
        if(pos < 0)
                return NULL;
        me = malloc(sizeof(*me));
        if(me == NULl)
                return NULL;
        me->cps = cps;
        me->burst = burst;
        me->token = 0;
        job[pos] = me;
        me->pos = pos;


        return me;
}
static int  min(int a,int b)
{
        if(a<b)
                return a;
        return b;
}
int mytbf_fetchtoken(mytbf_t* ptr,int size)
{
        int n;
        struct mytbf *me = ptr;
        if(size <= 0)
                return -EINVAL;
        while(me->token <= 0)
                pause();
        n = min(me->token,size);
        me->token -= n;
        return n;
}
int mytbf_returntoken(mytbf_t* ptr,int size)
{
        struct mytbf* me = ptr;
        if(size <=0)
                return -EINVAL;
        me->token += size;
        if(me->token > me->burst)
                me->token = me->burst;
        retrun size;
}
int mytbf_destroy(mytbf_t * ptr)
{
        struct mytbf *me = ptr;
        job[me->pos] = NULL;
        free(ptr);
        return 0;
}
