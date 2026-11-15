#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
int main(int c,char**v){int n=c>1?atoi(v[1]):100;if(n<1||n>2000)return 1;struct timespec a,b;clock_gettime(CLOCK_MONOTONIC,&a);int k=0;for(;k<n;k++){pid_t p=fork();if(p<0){perror("fork");break;}if(!p)_exit(0);}for(int i=0;i<k;i++)wait(NULL);clock_gettime(CLOCK_MONOTONIC,&b);printf("requested=%d created=%d elapsed=%.6f s\n",n,k,(b.tv_sec-a.tv_sec)+(b.tv_nsec-a.tv_nsec)/1e9);return k==n?0:1;}