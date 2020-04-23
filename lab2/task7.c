#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static int task7() {
    int rc = fork();

    if (rc == 0) // child process
    {
        close(STDOUT_FILENO);
        printf("print from child process\n");
    } else if (rc > 0) {
        printf("print from parent process\n");
    } else {
        printf("Error\n");
    }
    return 0;
}