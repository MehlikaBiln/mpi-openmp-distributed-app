#include <stdio.h>
#include <omp.h>

#define DATA_SIZE 1000

int main() {
    int data[DATA_SIZE];
    for (int i = 0; i < DATA_SIZE; i++) {
        data[i] = i;
    }

    #pragma omp parallel for
    for (int i = 0; i < DATA_SIZE; i++) {
        data[i] *= 2;
    }

    printf("OpenMP processing completed.\n");
    return 0;
}