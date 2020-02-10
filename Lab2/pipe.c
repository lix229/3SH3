#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/shm.h> 
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
#define READ_END 0
#define WRITE_END 1
int main(int argc, char **argv )
{   
    typedef struct timeval timeval_t;
    int pipeFD[2];
    pipe(pipeFD);
    pid_t pid;
    pid = fork();
        if (pid < 0) {
        /* error occurred */ 
        fprintf(stderr, "Fork Failed"); return 1;
    }
    else if (pid == 0) {
        close(pipeFD[READ_END]);
        timeval_t startTime;
        gettimeofday(&startTime, 0);
        write(pipeFD[WRITE_END], &startTime, sizeof(startTime));
        close(pipeFD[WRITE_END]);
        execvp(argv[1], argv + 1);
    }
    else {
        wait(NULL);
        timeval_t end_time;
        gettimeofday( &end_time,0);
        timeval_t startTime;
        close(pipeFD[WRITE_END]);
        read(pipeFD[READ_END], &startTime, sizeof(startTime));
        close(pipeFD[READ_END]);
        timeval_t elapsed_time;
        timersub( &end_time, &startTime, &elapsed_time );
        printf( "\nElapsed time: %lu.%06lu seconds\n", elapsed_time.tv_sec, elapsed_time.tv_usec );
        printf( "Command: " );
        char ** arg = argv + 1;
        while( *arg ) printf("%s ", *arg++);
        printf("\n");
    }
    return 0;
}