# Dağıtık Sistem Projesi: OpenMP + MPI + Docker

Bu proje, Docker kullanarak dağıtık bir sistemde OpenMP ve MPI ile paralel veri işleme uygulaması gerçekleştirir.

---

## İçerik
- [Amaç](#amaç)
- [Kullanılan Teknolojiler](#kullanılan-teknolojiler)
- [Kurulum Adımları](#kurulum-adımları)
  - [1. Projeyi Klonlayın veya İndirin](#1-projeyi-klonlayın-veya-indirin)
  - [2. Docker ve Docker Compose Yüklenmesi](#2-docker-ve-docker-compose-yüklenmesi)
  - [3. Docker Ortamını Çalıştırma](#3-docker-ortamını-çalıştırma)
  - [4. Node1 İçerisine Girin](#4-node1-içerisine-girin)
  - [5. MPI Komutunu Çalıştırma](#5-mpi-komutunu-çalıştırma)
- [Projenin İçeriği](#projenin-içeriği)
- [Çıktılar](#çıktılar)
- [Sonuç](#sonuç)

---

## Amaç
Bu projede, OpenMP kullanarak her bir düğüm içerisinde çok çekirdekli paralel işleme sağlanmakta, MPI kullanarak da düğümler arasında veri paylaşımı ve işbirliği gerçekleştirilmektedir. Tüm sistem Docker konteynerleri üzerinde dağıtık olarak çalışır.

---

## Kullanılan Teknolojiler
- **C (OpenMP + MPI)**
- **Docker & Docker Compose**
- **Ubuntu 20.04 base image**
- **OpenSSH server** (dağıtık ağ için)

---

## Kurulum Adımları

### 1. Projeyi Klonlayın veya İndirin
```bash
git clone https://github.com/MehlikaBiln
mpi-openmp-distributed-app.git
cd mpi-openmp-distributed-app
```
veya ZIP olarak indirip bir klasöre çıkarın.

### 2. Docker ve Docker Compose Yüklenmesi
Docker yüklü değilse, resmi siteden indirerek kurabilirsiniz:
- [Docker indir](https://www.docker.com/products/docker-desktop/)

Terminale şu komutlarla doğrulama yapabilirsiniz:
```bash
docker -v
docker compose version
```

### 3. Docker Ortamını Çalıştırma
Projeyi build edip konteynerleri ayağa kaldırmak için:
```bash
docker compose up -d --build
```
Bu komut:
- node1, node2, node3, node4 konteynerlerini oluşturur
- SSH servislerini başlatır
- MPI + OpenMP uygulamasını derler

### 4. Node1 İçerisine Girin
```bash
docker exec -it node1 bash
```
Artık dağıtık yapının ana düğümündesiniz.

### 5. MPI Komutunu Çalıştırma
Node1 içinde aşağıdaki komutu yazın:
```bash
mpirun -np 4 -host node1,node2,node3,node4 ./mpi_program
```
Bu komut:
- Her node için birer MPI işlemi başlatır
- Veriyi parçalar (dataset.txt üzerinden)
- Her node kendi parçasını OpenMP ile paralel işler
- Sonuçlar toplanarak `log.txt` içerisine yazılır

---

## Projenin İçeriği

### Dosyalar
- `mpi_program.c` : OpenMP + MPI işlemesini yapan C kodu
- `openmp_program.c` : Yalnızca OpenMP içeren bağımsız örnek kod
- `dataset.txt` : 1000 tane random sayıların bulunduğu veri seti
- `log.txt` : Program çalıştırıldığında hesaplama sonucunun yazıldığı dosya
- `run_all.sh`, `run_mpi.sh`, `run_openmp.sh` : Uygulama başlatma scriptleri
- `Dockerfile` : MPI, OpenMP ve SSH içeren Ubuntu imajını tanımlar
- `docker-compose.yml` : 4 node için ağ ve servis tanımı yapar

---

## Çıktılar

Program başarıyla çalıştığında `log.txt` dosyasına toplam sonuç şu şekilde yazılır:
```
MPI işlemi başlatılıyor (3 process)
-Processor 1 wrote output to output_1.txt
-Processor 1 processed its data chunk.
-Processor 0 wrote output to output_0.txt
-Processor 0 processed its data chunk.
-Processor 2 wrote output to output_2.txt
-Processor 2 processed its data chunk.

-.txt dosyalarının çıktıları görünür

OpenMP processing completed.
OpenMP işlemi başlatılıyor (4 thread)...

```
Bu değer, `dataset.txt` içinde yer alan random sayıların iki katı alınmış bir şekilde oluşan çıktılardır. MPI her node'a veri dağıtır, OpenMP ile parçalar paralel işlenir ve sonuçlar toplanır.

---

## Sonuç
Bu proje ile Docker konteynerlerinde çalışan birden fazla node arasında MPI ve OpenMP kullanarak paralel işleme başarıyla sağlanabilir. Gerçek dağıtık sistem mantığı simüle edilmiş olur.

---

Hazırlayan: Mehlika

