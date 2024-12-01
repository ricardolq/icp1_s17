#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *thread_function(void *arg) {
    int num = *(int *)arg;
    printf("Thread number: %d\n", num);
    if (num % 2 != 0) {
        int *ret_val = malloc(sizeof(int));
        *ret_val = num * 2; // Example value to return
        pthread_exit(ret_val);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int num1 = 1, num2 = 2;

    // Create threads
    if (pthread_create(&thread1, NULL, thread_function, &num1) != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }
    if (pthread_create(&thread2, NULL, thread_function, &num2) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    // Join threads
    void *ret_val1;
    void *ret_val2;

    pthread_join(thread1, &ret_val1);
    pthread_join(thread2, &ret_val2);

    if (ret_val1 != NULL) {
        printf("Thread 1 returned: %d\n", *(int *)ret_val1);
        free(ret_val1);
    } else {
        printf("Thread 1 returned NULL\n");
    }

    if (ret_val2 != NULL) {
        printf("Thread 2 returned: %d\n", *(int *)ret_val2);
        free(ret_val2);
    } else {
        printf("Thread 2 returned NULL\n");
    }

    printf("Threads have finished execution\n");
    return 0;
}