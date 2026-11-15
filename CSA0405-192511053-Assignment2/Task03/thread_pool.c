#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#define CAM 64
#define LOOPS 20000000
long result[CAM];typedef struct{int a,b;} Work;
void *run(void*x){Work*w=x;for(int i=w->a;i<w->b;i++){unsigned long z=i+1;for(int k=0;k<LOOPS/CAM;k++)z=(z*1664525u+1013904223u)%1000003u;result[i]=z%1000;}return NULL;}
double test(int n){pthread_t t[64];Work w[64];for(int i=0;i<CAM;i++)result[i]=0;struct timespec a,b;clock_gettime(CLOCK_MONOTONIC,&a);for(int i=0;i<n;i++){w[i]=(Work){CAM*i/n,CAM*(i+1)/n};pthread_create(&t[i],0,run,&w[i]);}for(int i=0;i<n;i++)pthread_join(t[i],0);clock_gettime(CLOCK_MONOTONIC,&b);return b.tv_sec-a.tv_sec+(b.tv_nsec-a.tv_nsec)/1e9;}
int main(void){int ns[]={1,4,8,16,64};double base=0;for(int i=0;i<5;i++){double s=test(ns[i]);if(!i)base=s;printf("pool=%d elapsed=%.6f speedup=%.3f\n",ns[i],s,base/s);}return 0;}