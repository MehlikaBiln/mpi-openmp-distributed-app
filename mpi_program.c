#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define DATA_SIZE 1000  // Veri kümesi boyutu

void process_data(int *data, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        data[i] *= 2;  // Veriyi işleyelim (Her sayıyı 2 ile çarp)
    }
}

void read_dataset(int *data, int size) {
    FILE *file = fopen("dataset.txt", "r");
    if (!file) {
        printf("Error: Could not open dataset.txt\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &data[i]);
    }

    fclose(file);
}

void write_output(int *data, int size, int rank) {
    char filename[20];
    sprintf(filename, "output_%d.txt", rank);  // Her işlemci için ayrı dosya

    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not create output file for processor %d\n", rank);
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", data[i]);
        if ((i + 1) % 10 == 0) fprintf(file, "\n");  // Satır başına 10 sayı yaz
    }

    fclose(file);
    printf("Processor %d wrote output to %s\n", rank, filename);
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int chunk_size = DATA_SIZE / world_size;
    int data[chunk_size];

    if (world_rank == 0) {
        int full_data[DATA_SIZE];
        read_dataset(full_data, DATA_SIZE);

        // Veriyi tüm düğümlere paylaştır
        MPI_Scatter(full_data, chunk_size, MPI_INT, data, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        MPI_Scatter(NULL, chunk_size, MPI_INT, data, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    }

    process_data(data, chunk_size);

    // Çıktıyı yazdır
    write_output(data, chunk_size, world_rank);

    printf("Processor %d processed its data chunk.\n", world_rank);

    MPI_Finalize();
    return 0;
}
