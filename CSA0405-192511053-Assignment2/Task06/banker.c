#include <stdio.h>
#include <string.h>
#define P 5
#define R 3
int avail[R]={3,3,2},maxm[P][R]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}},alloc[P][R]={{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
int safe(int seq[P]){int work[R],fin[P]={0},n=0;memcpy(work,avail,sizeof work);while(n<P){int found=0;for(int p=0;p<P;p++)if(!fin[p]){int ok=1;for(int r=0;r<R;r++)if(maxm[p][r]-alloc[p][r]>work[r])ok=0;if(ok){for(int r=0;r<R;r++)work[r]+=alloc[p][r];fin[p]=1;seq[n++]=p;found=1;}}if(!found)return 0;}return 1;}
void request(int p,int q[R]){for(int r=0;r<R;r++)if(q[r]>maxm[p][r]-alloc[p][r]||q[r]>avail[r]){printf("P%d request: must wait (not available)\n",p);return;}for(int r=0;r<R;r++){avail[r]-=q[r];alloc[p][r]+=q[r];}int s[P];if(safe(s)){printf("P%d request: granted, safe sequence",p);for(int i=0;i<P;i++)printf(" P%d",s[i]);puts("");}else{for(int r=0;r<R;r++){avail[r]+=q[r];alloc[p][r]-=q[r];}printf("P%d request: denied (unsafe)\n",p);}}
int main(void){int s[P];if(safe(s)){printf("initial state safe:");for(int i=0;i<P;i++)printf(" P%d",s[i]);puts("");}request(1,(int[R]){1,0,2});request(4,(int[R]){3,3,0});request(0,(int[R]){0,2,0});return 0;}