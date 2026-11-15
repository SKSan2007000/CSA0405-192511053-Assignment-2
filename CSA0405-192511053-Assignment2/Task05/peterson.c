#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#define N 100000
static atomic_bool flag[2];static atomic_int turn;static int counter;
static void *worker(void *arg){int id=(int)(long)arg,other=1-id;for(int i=0;i<N;i++){atomic_store_explicit(&flag[id],true,memory_order_seq_cst);atomic_store_explicit(&turn,other,memory_order_seq_cst);while(atomic_load_explicit(&flag[other],memory_order_seq_cst)&&atomic_load_explicit(&turn,memory_order_seq_cst)==other){}counter++;atomic_store_explicit(&flag[id],false,memory_order_seq_cst);}return NULL;}
int main(void){pthread_t a,b;pthread_create(&a,0,worker,(void*)0);pthread_create(&b,0,worker,(void*)1);pthread_join(a,0);pthread_join(b,0);printf("Peterson with C11 sequentially-consistent atomics: counter=%d expected=%d\n",counter,2*N);return counter!=2*N;}
