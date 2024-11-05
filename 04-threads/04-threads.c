#include <stdio.h>
#include <threads.h>

int thread_function(void *arg) {
    int num = *(int *)arg;
    printf("Thread number: %d\n", num);
    return 0;
}

int main() {
    thrd_t thread1, thread2;
    int num1 = 1, num2 = 2;

    // Create threads
    if (thrd_create(&thread1, thread_function, &num1) != thrd_success) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }
    if (thrd_create(&thread2, thread_function, &num2) != thrd_success) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    // Join threads
    thrd_join(thread1, NULL);
    thrd_join(thread2, NULL);

    printf("Threads have finished execution\n");
    return 0;
}