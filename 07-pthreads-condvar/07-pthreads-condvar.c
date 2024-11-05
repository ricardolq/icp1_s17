#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#define NUM_THREADS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int count = 0;

void* thread_func(void* arg) {
    int id = *((int*)arg);
    free(arg);

    pthread_mutex_lock(&mutex);
    count++;
    printf("Thread %d: count = %d\n", id, count);

    if (count == NUM_THREADS) {
        pthread_cond_broadcast(&cond);
    } else {
        while (count < NUM_THREADS) {
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            ts.tv_sec += 10; // wait for 10 seconds

            int rc = pthread_cond_timedwait(&cond, &mutex, &ts);
            if (rc == ETIMEDOUT) {
                printf("Thread %d: timed out\n", id);
                break;
            }
        }
    }

    printf("Thread %d: proceeding\n", id);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, thread_func, id);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}