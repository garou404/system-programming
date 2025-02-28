#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Usage: ./sem n\n");
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    char* key = "/key";
    int token_nb = 4;
    sem_t* sem = sem_open(key, O_CREAT, S_IRWXU, token_nb);
    sem_unlink(key);
    for (int i = 0; i < n; i++)
        fork();
    // sem_t* my_sem = sem_open(key, 0);
    sem_wait(sem);
    printf("[%d] start job\n", getpid());
    sleep(1);
    printf("[%d] stop job\n", getpid());
    sem_post(sem);
    return EXIT_SUCCESS;
}
