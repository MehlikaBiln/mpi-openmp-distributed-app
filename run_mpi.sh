echo "Running MPI program"
mpirun --allow-run-as-root -np 3 --host mpi_node1,mpi_node2,mpi_node3 /app/mpi_program
