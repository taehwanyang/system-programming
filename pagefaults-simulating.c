#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define ARR_SIZE    (1024 * 1024 * 1024)
#define THREAD_NUM 12

void * thread_main(void * args) {
    int * arr_ptr = (int *) malloc(ARR_SIZE);
    memset(arr_ptr, 0, ARR_SIZE);

    while (1) {
        for (int i = 0; i < ARR_SIZE; i++) {
            arr_ptr[i] += 100;
        }

        for (int i = 0; i < ARR_SIZE; i++) {
            arr_ptr[i] -= 100;
        }
    }
    free(arr_ptr);
    return NULL;
}

void start_threads();
void join_threads();

pthread_t threads[THREAD_NUM];

int main(int argc, char ** argv) {
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork() failed!\n");
        return -1;
    }

    if (pid == 0) {
        start_threads();
        join_threads();
        return 0;
    }

    execl("/usr/bin/vmstat", "vmstat", "1", NULL);
    getchar();

    return 0;
}


void start_threads() {
    int ret;
    for (int i = 0; i < THREAD_NUM; i++) {
        ret = pthread_create(&threads[i], NULL, thread_main, NULL);
        if (ret) {
            fprintf(stderr, "pthread_create() failed \n");
        }
    }
}

void join_threads() {
    int ret;
    for (int i = 0; i < THREAD_NUM; i++) {
       ret = pthread_join(threads[i], NULL);
       if (ret) {
           fprintf(stderr, "pthread_join() failed \n");
       }
    }
}


