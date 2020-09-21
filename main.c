#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hiredis.h>
#include "redis_util.h"
#include "jemalloc/jemalloc.h"
//#include "google/tcmalloc.h"
#include "pthread.h"
#include<sys/time.h> //注意引用这个头文件
#define ONLY_N2M_1(n,m) ~(~0U<<(m-n+1))<<(n-1)

#define testTimes 1000
#define testThread 100

pthread_barrier_t barrier;

//void test(int num){
//    for (int i = 0; i <num ; ++i) {
//        unsigned char *p = malloc(1000);
//        p = calloc(500, 4);
//        free(p);
//    }
//    pthread_barrier_wait(&barrier);
//}
//
//int main(int argc, char **argv) {
//    pthread_barrier_init(&barrier, NULL, testThread + 1);
//    struct timeval start,end;
//    gettimeofday(&start, NULL );
//    for (int i = 0; i < testThread; ++i) {
//        pthread_t pid;
//        pthread_create(&pid, NULL, &test, testTimes);
//        pthread_detach(pid);
//    }
//    pthread_barrier_wait(&barrier);
//
//    gettimeofday(&end, NULL );
//    double timeuse = ( end.tv_sec - start.tv_sec ) + (end.tv_usec - start.tv_usec)/1000000.0;
//    printf("time=%f\n",timeuse);
//    pthread_barrier_destroy(&barrier);
//    return 0;
//}

