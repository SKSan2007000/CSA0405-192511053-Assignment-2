#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <semaphore.h>
#include <string.h>
#include <stdint.h>
#define CHUNK (64*1024)
typedef struct { sem_t ready; size_t bytes; unsigned char data[]; } Shared;
static double now(void){struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);return t.tv_sec+t.tv_nsec/1e9;}
static int pipe_test(size_t bytes){int f[2];if(pipe(f))return -1;pid_t p=fork();if(p<0)return -1;if(!p){close(f[1]);unsigned char b[CHUNK];size_t n=0;ssize_t r;while((r=read(f[0],b,sizeof b))>0)n+=(size_t)r;close(f[0]);_exit(n==bytes?0:2);}close(f[0]);unsigned char *b=malloc(CHUNK);memset(b,0x5a,CHUNK);size_t sent=0;double a=now();while(sent<bytes){size_t z=bytes-sent<CHUNK?bytes-sent:CHUNK;ssize_t w=write(f[1],b,z);if(w<=0){perror("write");break;}sent+=(size_t)w;}close(f[1]);int st;waitpid(p,&st,0);double sec=now()-a;free(b);return WIFEXITED(st)&&WEXITSTATUS(st)==0?(int)(sec*1e9): -1;}
static int shm_test(size_t bytes){size_t total=sizeof(Shared)+bytes;Shared*s=mmap(NULL,total,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);if(s==MAP_FAILED)return -1;sem_init(&s->ready,1,0);s->bytes=bytes;pid_t p=fork();if(p<0)return -1;if(!p){sem_wait(&s->ready);volatile unsigned long sum=0;for(size_t i=0;i<bytes;i+=4096)sum+=s->data[i];_exit((sum || bytes==0)?0:2);}double a=now();memset(s->data,0x5a,bytes);sem_post(&s->ready);int st;waitpid(p,&st,0);double sec=now()-a;sem_destroy(&s->ready);munmap(s,total);return WIFEXITED(st)&&WEXITSTATUS(st)==0?(int)(sec*1e9):-1;}
static int cmp(const void*a,const void*b){int x=*(const int*)a,y=*(const int*)b;return (x>y)-(x<y);}
int main(void){size_t mb[]={1,10,100};puts("IPC transfer benchmark (5 trials per size; median shown)");for(int i=0;i<3;i++){size_t n=mb[i]*1024u*1024u;int pv[5],sv[5];for(int j=0;j<5;j++){pv[j]=pipe_test(n);sv[j]=shm_test(n);}qsort(pv,5,sizeof(int),cmp);qsort(sv,5,sizeof(int),cmp);int p=pv[2],s=sv[2];printf("%zu MB pipe median=%.3f ms (%.1f MB/s); shared-memory median=%.3f ms (%.1f MB/s)\n",mb[i],p/1e6,p>0?mb[i]*1000.0/(p/1e6):0,s/1e6,s>0?mb[i]*1000.0/(s/1e6):0);}return 0;}
