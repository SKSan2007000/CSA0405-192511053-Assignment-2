#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void){printf("Parent PID: %ld\n",(long)getpid());fflush(stdout);for(int i=0;i<4;i++){pid_t p=fork();if(p<0){perror("fork");return 1;}if(p==0){printf("Child %d PID=%ld PPID=%ld\n",i+1,(long)getpid(),(long)getppid());fflush(stdout);sleep(2+i);_exit(0);}}printf("Use ps -o pid,ppid,stat,comm --ppid %ld\n",(long)getpid());for(int i=0;i<4;i++){int s;pid_t p=wait(&s);if(p>0)printf("Reaped PID=%ld status=%d\n",(long)p,WIFEXITED(s)?WEXITSTATUS(s):-1);}puts("All children collected.");return 0;}