#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d)\n", getpid());
        char *args[] = {"/bin/ls", "-l", NULL};
        execvp(args[0], args);
        // If execvp returns, it must have failed
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        printf("Parent process (PID: %d), waiting for child to complete...\n", getpid());
        wait(NULL);
        printf("Child process completed.\n");
    }

    return 0;
}