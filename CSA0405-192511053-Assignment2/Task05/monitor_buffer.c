#include <stdio.h>
#include <pthread.h>
#define SIZE 5
#define ITEMS 20
static int q[SIZE],in=0,out=0,count=0;static pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;static pthread_cond_t not_full=PTHREAD_COND_INITIALIZER,not_empty=PTHREAD_COND_INITIALIZER;
static void put(int x){pthread_mutex_lock(&m);while(count==SIZE)pthread_cond_wait(&not_full,&m);q[in]=x;in=(in+1)%SIZE;count++;pthread_cond_signal(&not_empty);pthread_mutex_unlock(&m);}
static int get(void){pthread_mutex_lock(&m);while(count==0)pthread_cond_wait(&not_empty,&m);int x=q[out];out=(out+1)%SIZE;count--;pthread_cond_signal(&not_full);pthread_mutex_unlock(&m);return x;}
static void *producer(void*x){(void)x;for(int i=1;i<=ITEMS;i++)put(i);return NULL;}static void *consumer(void*x){long *sum=x;for(int i=0;i<ITEMS;i++)*sum+=get();return NULL;}
int main(void){pthread_t p,c;long sum=0;pthread_create(&p,0,producer,0);pthread_create(&c,0,consumer,&sum);pthread_join(p,0);pthread_join(c,0);printf("monitor-style condition variable sum=%ld expected=210\n",sum);return sum!=210;}
