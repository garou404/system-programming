#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>

#define N 100
volatile int n = 0;

volatile unsigned long long k = 0;

// gestionnaire de signals/signals manager
void hello(int x){
    n++;
    k--;
    if(n % 1000 == 0) printf("Hello\n");
    ualarm(1000, 0);
}

int main(int argc, char** argv) {
    unsigned long long ref = 0;
    
    // declare and initialize sigaction struct
    struct sigaction sa;
    sa.sa_handler = hello;
    sa.sa_flags = 0;
    
    // create sigset and add SIGALRM to it 
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGALRM);

    sigaction(SIGALRM, &sa, NULL);
    
    ualarm(1000, 0);

    while(n != N) {
        // mask the signal SIGALRM
        // SIGALRM is set to wait until unblock so that we avoid modifying the var at the same time
        sigprocmask(SIG_BLOCK, &sigset, NULL);
        k++;
        sigprocmask(SIG_UNBLOCK, &sigset, NULL);
        ref++;
    }
    printf("ref - k = %lld\n", ref - k);
    printf("end of program\n");
}
