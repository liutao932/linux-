#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
#include<errno.h>
#include<string.h>
#define MAX 9

static pthread_mutex_t mutex_array = PTHREAD_MUTEX_INITIALIZER;
static void swap(int* a, int* b)//交换
{
        int tmp = *a;
        *a = *b;
        *b = tmp;
}
static void InsertSort(int* a, int n)//插入排序
{
        assert(a);
        for (int i = 0; i < n - 1; i++)
        {
                int end = i;
                int x = a[end + 1];
                while (end >= 0)
                {
                        if (a[end] > x)
                        {
                                a[end + 1] = a[end];
                                end--;
                        }
                        else
                        {
                                break;
                        }
                }
                a[end + 1] = x;
        }
}
static int partion3(int* a, int left, int rigth)//前后指针
{
        int prev = left, cur = left + 1;
        int key = left;
        while (cur <= rigth)
        {
                if (a[cur] < a[key] && ++prev != cur)
                {
                        swap(&a[prev], &a[cur]);
                }
                cur++;
        }
        swap(&a[prev], &a[key]);
        return prev;
}
static void QuickSort(int* a, int left, int rigth)//快速排序
{
        if (rigth - left + 1 <= 10)
        {
                InsertSort(a + left, rigth - left + 1);
        }
        else
        {
                if (left >= rigth)
                                return;
                //int key = partion1(a, left, rigth);
                //int key = partion2(a, left, rigth);
                int key = partion3(a, left, rigth);
                QuickSort(a, left, key - 1);
                QuickSort(a, key + 1, rigth);
        }
}
static void* pthread_sort(void *p)
{
        int *array = (int*) p;
        pthread_mutex_lock(&mutex_array);
        QuickSort(array,0,9999);
        pthread_mutex_unlock(&mutex_array);
        pthread_exit(NULL);
}
int main()
{

        int i,err;
        int *array = (int*)malloc(sizeof(int)*10000);
        if(array == NULL)
                exit(1);
        srand(time(NULL));
        for(i = 0; i< 10000;i++)
        {
                array[i] = rand() % 1000 + 1;
        }
        //QuickSort(array,0,9999);
        pthread_t tid[MAX];
        for( i = 0; i< MAX;i++)
        {
                err = pthread_create(tid + i,NULL,pthread_sort,array);
                if(err)
                {
                        fprintf(stderr,"%s pthread_create()",strerror(err));
                }
        }

        for(i = 0; i<MAX; i++)
        {
                pthread_join(tid[i],NULL);
        }

        pthread_mutex_destroy(&mutex_array);

        for(int i = 0; i< 10000;i++)
        {
                printf("%d\n",*(array +i));
        }
        exit(0);
}
