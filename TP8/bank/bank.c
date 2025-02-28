#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
    if(argc != 3) {
        printf("Usage: ./bank name money\n");
        return EXIT_FAILURE;
    }
    char* name = argv[1];
    int money = atoi(argv[2]);
    
    int balance;
    sem_t* sem = sem_open("/key", O_CREAT, S_IRWXU, 1);
    // if (sem == SEM_FAILED) {
    //     perror("sem_open failed");
    //     exit(EXIT_FAILURE);
    // }
    // sem_unlink("/key");
    sem_wait(sem);
    FILE* f = fopen(name, "r");
    if(f){
        fread(&balance, sizeof(int), 1, f);
    }else{
        balance = 0;
    }
    balance += money;
    printf("%s: %d\n", name, balance);
    
    f = fopen(name, "w");
    fwrite(&balance, sizeof(int), 1, f);
    fclose(f);
    sem_post(sem);
    return EXIT_SUCCESS;
}
