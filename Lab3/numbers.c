#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_THREADS 3

/* Predefining numbers of threads */

void *average(void *params);
void *maximum(void *params);
void *minimum(void *params);

typedef struct {
    int size;
    int data[];

}   parameters;

/* Creating structure used for parsing parameters to threads.
   size is the number of integer arguments,
   data[] stores the actual data from user input. 
   this is needed because only one argument can be passed to a thread,
   so data would have to be packed as a struct */

int ave;
int max;
int min;

/* global variables to store the results */

int main(int argc, const char *argv[]) {

    pthread_t workers[NUMBER_OF_THREADS];
    /* declaring NUMBER_OF_THREADS threads, in this case, 3 */

    parameters *params = (parameters *) malloc ( sizeof ( parameters ) ) ;
    /* Allocating memory for parameter typed structure so it can be passed to threads */

    for(int i = 0; i < argc-1; i ++) {
        params->data[i] = atoi(argv[i+1]);
    }
    /* Iterate through the array of command line arguments, cast them from char to int,
       and store them in params->data */

    params->size = argc-1;
    /* Initialize the size of data to be argc-1 as the first argument is the name of this class */

    pthread_create(&workers[0], 0, average, params);
    pthread_create(&workers[1], 0, maximum, params);
    pthread_create(&workers[2], 0, minimum, params);
    /* Assigning jobs and parameters to the 3 threads respectively. */

    for(int i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_join(workers[i],0);
    };
    /* Collect all threads once they finish */

    printf("The average value is %d\n", ave);
    printf("The minimum value is %d\n", min);
    printf("The maximum value is %d\n", max);
    /* Print out the final results */

    return 0;
}

void *average(void *params){
    parameters* p = (parameters *)params;
    /* Cast the parameters from void * back to parameter * so they can be correctly accessed. */
    int sum = 0;
    for(int i = 0; i < (p->size); i ++) {
        sum += p->data[i];
    }
    ave = sum/p->size;
}

void *maximum(void *params) {
    parameters* p = (parameters *)params;
    max = p->data[0];
    for(int i = 0; i < p->size; i++) {
        if (p->data[i]>max) {
            max = p->data[i];
        }
    }
}

void *minimum(void *params) {
    parameters* p = (parameters *)params;
    min = p->data[0];
    for(int i = 0; i < p->size; i++) {
        if (p->data[i]<min) {
            min = p->data[i];
        }
    }
}



