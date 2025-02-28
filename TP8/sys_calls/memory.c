#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int var = 42;

int main(int argc, char** argv) {
    if(fork() == 0){
        printf("[%d] Hhh hhh non, non\n", getpid());
        sleep(1);
        var = 666;
        sleep(1);
        printf("PID [%d], var address %p, var value %d\n", getpid(), &var, var);
        printf("end of B1\n");
        // create file
        execlp("touch", "touch", "sync", NULL);
    }else{
        printf("[%d] Je suis ton père\n", getpid());
        while(fopen("sync", "r") == NULL) {}
        printf("sync file deleted\n");
        unlink("sync");
        sleep(1);
        printf("PID [%d], var address %p, var value %d\n", getpid(), &var, var);
        printf("end of B2\n");
    }
    return EXIT_SUCCESS;
}
