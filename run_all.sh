#!/bin/bash

echo ""
echo "======================================="
echo "node1 aktif - İşlem başlatılıyor..."
echo "======================================="

echo ""
echo " MPI işlemi başlatılıyor (3 process)..."
echo "---------------------------------------"
mpirun --allow-run-as-root --oversubscribe -np 3 ./mpi_program

echo ""
echo " output_0.txt içeriği:"
echo "---------------------------------------"
cat output_0.txt

echo ""
echo " output_1.txt içeriği:"
echo "---------------------------------------"
cat output_1.txt

echo ""
echo "output_2.txt içeriği:"
echo "---------------------------------------"
cat output_2.txt

echo ""
echo "======================================="
echo "🚀 OpenMP işlemi başlatılıyor (4 thread)..."
echo "======================================="
export OMP_NUM_THREADS=4
./openmp_program

echo ""
echo " Tüm işlemler başarıyla tamamlandı!"
echo " Tüm çıktılar terminale ve log.txt dosyasına yazıldı."
