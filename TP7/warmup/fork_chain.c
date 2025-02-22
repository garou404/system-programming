#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    int i = 0;
    printf("el padre: %d\n", getpid());
    while (i < 3) {
        if(fork() != 0) {
            sleep(1);
            break;
        }
        printf("ppid: %d, pid: %d\n", getppid(), getpid());
        i++;
    }
    if (i >= 3) {
        sleep(3);
        execlp("ps", "ps", "f", NULL);
        // if(execlp("ps", "ps", "f" ) != 0) {
            // printf("ps f command failed\n");
            // return EXIT_FAILURE;
        // }
    }
    int *ptr = malloc(sizeof(int));
    wait(ptr);
    sleep(2);
    free(ptr);
    printf("end of pid %d\n", getpid());
    return EXIT_SUCCESS;
}
