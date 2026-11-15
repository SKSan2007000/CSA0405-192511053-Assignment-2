#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
typedef struct{sem_t ready;int v[6];} Shared;
int main(void){Shared*s=mmap(0,sizeof *s,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);if(s==MAP_FAILED)return 1;sem_init(&s->ready,1,0);pid_t p=fork();if(!p){sem_wait(&s->ready);int sum=0,m=0;for(int i=0;i<6;i++){sum+=s->v[i];if(s->v[i]>m)m=s->v[i];}printf("shared memory: 6 readings, average %.1f, max %d\n",sum/6.0,m);fflush(stdout);_exit(0);}int a[]={31,33,36,34,41,38};for(int i=0;i<6;i++)s->v[i]=a[i];sem_post(&s->ready);waitpid(p,0,0);sem_destroy(&s->ready);munmap(s,sizeof *s);return 0;}