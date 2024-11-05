#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
int counter = 0;

void* increment_counter(void* threadid) {
    long tid = (long)threadid;
    printf("Thread %ld starting...\n", tid);

    pthread_mutex_lock(&mutex);
    counter++;
    printf("Thread %ld incremented counter to %d\n", tid, counter);
    pthread_mutex_unlock(&mutex);

    printf("Thread %ld exiting...\n", tid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    pthread_mutex_init(&mutex, NULL);

    for(t = 0; t < NUM_THREADS; t++) {
        printf("Main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, increment_counter, (void *)t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for(t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    pthread_mutex_destroy(&mutex);
    printf("Final counter value: %d\n", counter);
    pthread_exit(NULL);
}