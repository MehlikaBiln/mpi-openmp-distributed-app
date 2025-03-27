FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    openmpi-bin \
    libopenmpi-dev \
    libomp-dev \
    python3 \
    python3-pip

WORKDIR /app

COPY mpi_program.c /app/mpi_program.c
COPY openmp_program.c /app/openmp_program.c
COPY run_mpi.sh /app/run_mpi.sh
COPY run_openmp.sh /app/run_openmp.sh

RUN mpicc -o mpi_program mpi_program.c
RUN gcc -fopenmp -o openmp_program openmp_program.c

CMD ["tail", "-f", "/dev/null"]
