#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#define THREADS 16
#define TRAINS 8
#define COACHES 8
#define OPS 50000
static long seats[TRAINS][COACHES];static pthread_mutex_t global_lock,train_lock[TRAINS],coach_lock[TRAINS][COACHES];static int mode;
static double now(void){struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);return t.tv_sec+t.tv_nsec/1e9;}
static void *book(void *arg){long id=(long)arg;int tr=(int)(id%TRAINS),co=(int)((id/TRAINS)%COACHES);for(int i=0;i<OPS;i++){pthread_mutex_t *l=mode==0?&global_lock:(mode==1?&train_lock[tr]:&coach_lock[tr][co]);pthread_mutex_lock(l);seats[tr][co]++;pthread_mutex_unlock(l);}return NULL;}
int main(void){pthread_mutex_init(&global_lock,0);for(int t=0;t<TRAINS;t++){pthread_mutex_init(&train_lock[t],0);for(int c=0;c<COACHES;c++)pthread_mutex_init(&coach_lock[t][c],0);}char *names[]={"global","per-train","per-coach"};for(mode=0;mode<3;mode++){for(int t=0;t<TRAINS;t++)for(int c=0;c<COACHES;c++)seats[t][c]=0;pthread_t th[THREADS];double a=now();for(long i=0;i<THREADS;i++)pthread_create(&th[i],0,book,(void*)i);for(int i=0;i<THREADS;i++)pthread_join(th[i],0);double sec=now()-a;long total=0;for(int t=0;t<TRAINS;t++)for(int c=0;c<COACHES;c++)total+=seats[t][c];printf("%s lock time=%.6f s bookings=%ld expected=%d throughput=%.0f bookings/s\n",names[mode],sec,total,THREADS*OPS,total/sec);}return 0;}
