#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Before exec\n");

    // Replace the current process with the "ls" command
    execl("/bin/ls", "ls", "-l", (char *)NULL);

    // If exec returns, it must have failed
    perror("execl failed");
    return 1;
}