#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void *prime(void *params);

int main(int argc, const char *argv[]) {
    pthread_t workers[1];
    int num = atoi(argv[1]);

    pthread_create(&workers[0], 0, prime, &num);

    pthread_join(workers[0],NULL);

    return 0;
}

void *prime(void *params) {

    int *number = (int *)params;
    int result_pos = 0;
    int result[10000];
    // printf("%d",*number);
    if (*number < 2) {
        printf("No prime number less than 2.");
        return 0;
    }
    else {
        for(int i = 2; i <= *number; i ++) {
            bool is_prime = true;
            for(int m = 2; m < i; m++) {
                if(i%m == 0 & i != 2){
                    is_prime = false;
                }
            }
            if(is_prime) {
                result[result_pos] = i;
                result_pos += 1;
            }         
        }
    }
    printf("Prime numbers less or equal to %d are: ", *number);
    for(int i = 0; i<result_pos;i++){
        printf("%d ", result[i]);
    }
    printf("\n");
}