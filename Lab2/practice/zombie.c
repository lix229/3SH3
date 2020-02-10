#include <sys/types.h> 
#include <stdio.h> 
#include <unistd.h>
int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        /* error occurred */ 
        fprintf(stderr, "Fork Failed"); return 1;
    }
    else if (pid == 0) { 
        /* child process */
        execlp("/bin/echo","echo","Zombie process created.",NULL); 
    }
    else {
        sleep(3);
        wait(NULL);
        printf("Zombie process exited.\n");
    }
    return 0;
}