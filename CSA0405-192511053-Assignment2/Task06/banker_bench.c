#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TRIALS 7
static double now(void){struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);return t.tv_sec+t.tv_nsec/1e9;}
static int cmp(const void*a,const void*b){double x=*(const double*)a,y=*(const double*)b;return (x>y)-(x<y);}
static double run(int n,int m){int *av=calloc((size_t)m,sizeof(int)),*mx=calloc((size_t)n*m,sizeof(int)),*al=calloc((size_t)n*m,sizeof(int)),*fin=calloc((size_t)n,sizeof(int));for(int r=0;r<m;r++)av[r]=0;
/* Reverse dependency chain: the final process can finish first; each
   completed process releases one unit needed by its predecessor. */
for(int p=0;p<n;p++){al[p*m]=1;mx[p*m]=(p==n-1)?1:(n-p);}
double a=now();int done=0;while(done<n){int found=0;for(int p=0;p<n;p++)if(!fin[p]){int ok=1;for(int r=0;r<m;r++)if(mx[p*m+r]-al[p*m+r]>av[r])ok=0;if(ok){for(int r=0;r<m;r++)av[r]+=al[p*m+r];fin[p]=1;done++;found=1;}}if(!found)break;}double elapsed=now()-a;free(av);free(mx);free(al);free(fin);return done==n?elapsed:-1;}
int main(void){int ns[]={10,100,1000};puts("Banker safety scan: 7 trials per size; median shown");for(int z=0;z<3;z++){double v[TRIALS];for(int i=0;i<TRIALS;i++)v[i]=run(ns[z],3);qsort(v,TRIALS,sizeof(double),cmp);printf("processes=%d resources=3 median=%.9f s min=%.9f max=%.9f\n",ns[z],v[TRIALS/2],v[0],v[TRIALS-1]);}return 0;}
