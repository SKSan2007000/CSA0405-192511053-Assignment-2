#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void){int f[2];if(pipe(f)<0)return 1;pid_t p=fork();if(p==0){close(f[1]);int x,n=0,sum=0,m=0;while(read(f[0],&x,sizeof x)==sizeof x){n++;sum+=x;if(x>m)m=x;}printf("analyser: %d readings, average %.1f, max %d\n",n,n?(double)sum/n:0,m);fflush(stdout);close(f[0]);_exit(0);}close(f[0]);int a[]={31,33,36,34,41,38};for(int i=0;i<6;i++)write(f[1],&a[i],sizeof a[i]);close(f[1]);waitpid(p,0,0);puts("reader: done");return 0;}