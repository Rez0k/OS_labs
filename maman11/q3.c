#define _POSIX_C_SOURCE 200112L
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
int s;
sigset_t set;
int *sigptr;

void sem_init(int status) {
    s = status;
    int sig;
    sigptr = &sig;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
}

void sem_down() {
    if (s == 0) {
        sigprocmask( SIG_BLOCK, &set, NULL );
    }
    if (s > 0) {
        s--;
    }
}

void sem_up() {
    int ret_val = sigwait(&set,sigptr);
    printf("ret_val: %d", ret_val);
    if (ret_val == 0) {
        kill(*sigptr,SIGUSR1);
        return;
    }
    s++;
}

void main() {
  sem_init(1);
  
//   sem_down();

//   printf("Waiting for a SIGINT signal\n");

//   sem_up();

    int pid = fork();
    printf("im father: %d\n", pid);
    int sum = 0;
    if ( pid == 0 ) {  // the son
        printf("im son");
        sem_down();
        sleep(100);
        sum += 1;
        sem_up();
    } else {
        printf("kalsheu");
        //sem_down();
        sleep(1000);
        //sum += 1;
        //sem_up();
    }

    printf("sum is : %d", sum);
}
