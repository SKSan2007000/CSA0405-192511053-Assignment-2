#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define SIZE 16
#define EACH 1000
static int buffer[SIZE],in=0,out=0;static sem_t empty,full;static pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;static int *seen;static long sum=0;static int producers,consumers,total;
static void *produce(void *arg){long id=(long)arg;for(int i=0;i<EACH;i++){int v=(int)(id*EACH+i+1);sem_wait(&empty);pthread_mutex_lock(&lock);buffer[in]=v;in=(in+1)%SIZE;pthread_mutex_unlock(&lock);sem_post(&full);}return NULL;}
static void *consume(void *arg){(void)arg;int count=total/consumers;for(int i=0;i<count;i++){sem_wait(&full);pthread_mutex_lock(&lock);int v=buffer[out];out=(out+1)%SIZE;if(v>0&&v<=total){seen[v]++;sum+=v;}pthread_mutex_unlock(&lock);sem_post(&empty);}return NULL;}
int main(int argc,char **argv){producers=argc>1?atoi(argv[1]):1;consumers=argc>2?atoi(argv[2]):1;if(producers<1||consumers<1||producers>4||consumers>4)return 2;total=producers*EACH;seen=calloc((size_t)total+1,sizeof(int));pthread_t p[4],c[4];sem_init(&empty,0,SIZE);sem_init(&full,0,0);for(long i=0;i<producers;i++)pthread_create(&p[i],NULL,produce,(void*)i);for(int i=0;i<consumers;i++)pthread_create(&c[i],NULL,consume,NULL);for(int i=0;i<producers;i++)pthread_join(p[i],NULL);for(int i=0;i<consumers;i++)pthread_join(c[i],NULL);int ok=1;for(int i=1;i<=total;i++)if(seen[i]!=1)ok=0;long expected=(long)total*(total+1)/2;printf("producers=%d consumers=%d items=%d sum=%ld expected=%ld each_once=%s\n",producers,consumers,total,sum,expected,ok&&sum==expected?"yes":"no");free(seen);sem_destroy(&empty);sem_destroy(&full);return !(ok&&sum==expected);}
