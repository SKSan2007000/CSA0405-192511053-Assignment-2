#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <time.h>
#include <sched.h>
#define OPS 200000
static long counter;static pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;static atomic_long ac;static atomic_flag spin=ATOMIC_FLAG_INIT;static int mode;
static double tm(clockid_t id){struct timespec t;clock_gettime(id,&t);return t.tv_sec+t.tv_nsec/1e9;}
typedef struct { long n; double cpu; } Arg;
static void *work(void *p){Arg *arg=p;double start=tm(CLOCK_THREAD_CPUTIME_ID);for(long i=0;i<arg->n;i++){if(mode==0){pthread_mutex_lock(&m);counter++;pthread_mutex_unlock(&m);}else if(mode==1)atomic_fetch_add(&ac,1);else{while(atomic_flag_test_and_set_explicit(&spin,memory_order_acquire)){}counter++;atomic_flag_clear_explicit(&spin,memory_order_release);}}arg->cpu=tm(CLOCK_THREAD_CPUTIME_ID)-start;return NULL;}
int main(void){int ns[]={1,4,16};char *names[]={"mutex","atomic_fetch_add","spin_lock"};for(mode=0;mode<3;mode++)for(int j=0;j<3;j++){int n=ns[j];pthread_t t[16];Arg args[16];counter=0;atomic_store(&ac,0);atomic_flag_clear(&spin);double a=tm(CLOCK_MONOTONIC),cpu=0;for(int i=0;i<n;i++){args[i].n=OPS;args[i].cpu=0;pthread_create(&t[i],0,work,&args[i]);}for(int i=0;i<n;i++){pthread_join(t[i],0);cpu+=args[i].cpu;}double sec=tm(CLOCK_MONOTONIC)-a;long got=mode==1?atomic_load(&ac):counter;printf("%-18s threads=%2d updates=%ld time=%.6f s cpu=%.6f s result=%s\n",names[mode],n,got,sec,cpu,got==(long)n*OPS?"correct":"wrong");}return 0;}
