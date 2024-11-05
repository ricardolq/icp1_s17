#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

pthread_barrier_t barrier;

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    printf("Thread %d is waiting at the barrier\n", thread_id);
    
    // Wait at the barrier
    pthread_barrier_wait(&barrier);
    
    printf("Thread %d has crossed the barrier\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    // Initialize the barrier
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Destroy the barrier
    pthread_barrier_destroy(&barrier);
    
    return 0;
}