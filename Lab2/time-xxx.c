#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/shm.h> 
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
int main(int argc, char **argv )
{   
    typedef struct timeval timeval_t;
    /* the size (in bytes) of shared memory object */
    const int SIZE = 4096;
    /* name of the shared memory object */
    const char *name = "time";
    /* shared memory file descriptor */
    int fd;
    /* pointer to shared memory obect */
    timeval_t *ptr;
    /* create the shared memory object */
    fd = shm_open(name,O_CREAT | O_RDWR, 0666);
    /* configure the size of the shared memory object */ 
    ftruncate(fd, SIZE);
    /* memory map the shared memory object */
    ptr = (timeval_t *)
    mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    pid_t pid;
    pid = fork();
        if (pid < 0) {
        /* error occurred */ 
        fprintf(stderr, "Fork Failed"); return 1;
    }
    else if (pid == 0) { 
        gettimeofday(ptr,0);
        execvp(argv[1], argv + 1);
    }
    else {
        wait(NULL);
        timeval_t endtime;
        gettimeofday(&endtime,0);
        timeval_t starttime;
        starttime = *ptr;
        shm_unlink(name);
        timeval_t elapsed_time;
        timersub(&endtime, &starttime, &elapsed_time);
        printf( "\nElapsed time: %lu.%06lu seconds\n", elapsed_time.tv_sec, elapsed_time.tv_usec );
        printf( "Command: " );
        char ** arg = argv + 1;
        while( *arg ) printf("%s ", *arg++);
        printf("\n");
    }
    return 0;
}