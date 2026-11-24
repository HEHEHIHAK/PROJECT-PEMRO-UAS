# PROJECT-PEMRO-UAS
```bash
SISTEM KATALOG BUKU & TRANSAKSI (C)

Kelomok 8
- Muhammad Gibran   (260810701100084) | Modul Fondasi & Struktur Data
- Andy Maulana      (260810701100085) | Modul Login, Navigasi Menu, & Sorting
- Umi Dwi Noviani   (260810701100019) | Katalog & CRUD Buku
- Azna Tsabita      (260810701100005) | Transaksi Peminjaman

1. Definisi & Struktur
Aplikasi berbasis konsol (CLI) yang dibangun menggunakan bahasa pemrograman C dengan pendekatan modular. Program ini dirancang untuk mengelola data katalog buku, pencarian, pengurutan data (sorting), serta pencatatan transaksi buku.

*Fitur Utama*
* Autentikasi Pengguna:* Sistem login sebelum mengakses menu utama aplikasi.
* Manajemen Katalog Buku:* Menambah, melihat, mengubah, dan menghapus data buku.
* Pengurutan Data (Sorting):* Mengurutkan daftar buku berdasarkan ID, judul, tahun terbit, jumlah halaman, atau stok menggunakan algoritma Bubble Sort lengkap dengan perhitungan waktu eksekusi.
* Transaksi Buku:* Mencatat dan menampilkan riwayat transaksi peminjaman/pembelian buku.

perpustakaan/
├── include/                  # Direktori header file (definisi struct & prototipe)
│   ├── models.h              # Definisi struct utama bersama (Book, Account, Loan)
│   ├── fileio.h              # Deklarasi fungsi baca/tulis dan parser file
│   ├── utils.h               # Deklarasi fungsi bantu validasi input, string, & waktu
│   ├── buku.h                # Deklarasi fungsi katalog (paging), pencarian, & CRUD
│   ├── transaksi.h           # Deklarasi fungsi pinjam, kembali, & laporan transaksi
│   ├── sorting.h             # Deklarasi enum & algoritma pengurutan manual
│   └── auth.h                # Deklarasi fungsi autentikasi login dan logout
├── src/                      # Direktori kode sumber implementasi (.c)
│   ├── main.c                # Titik masuk program, inisialisasi memori, & menu utama
│   ├── fileio.c              # Implementasi parser manual Books.txt & penyimpanan aman
│   ├── utils.c               # Implementasi pembacaan input aman & utilitas sistem
│   ├── buku.c                # Implementasi tampilan katalog & operasi tambah/ubah/hapus
│   ├── transaksi.c           # Implementasi logika peminjaman & sinkronisasi stok
│   ├── sorting.c             # Implementasi Bubble, Insertion, & Selection Sort
│   └── auth.c                # Implementasi validasi login (interaktif & argumen CLI)
├── data/                     # Direktori penyimpanan dataset dan file operasional
│   ├── Books.txt             # Dataset master buku (read-only, tidak diubah program)
│   ├── books_data.txt        # Dataset operasional (otomatis dibuat saat pertama jalan)
│   ├── user.txt              # Daftar akun pengguna dan peran (admin / user)
│   └── peminjaman.txt        # Riwayat transaksi peminjaman dan pengembalian
├── Makefile                  # Untuk mengcompilasi program
└── README.txt                # Panduan lengkap penggunaan dan informasi aplikasi

2. Cara Menjalankan Program
- Prasyarat
Sebelum menjalankan program, pastikan GCC dan Make sudah terinstal di komputer. Untuk memeriksanya, buka terminal dan jalankan perintah berikut:
gcc --version
make --version
Jika kedua perintah menampilkan informasi versi, berarti GCC dan Make sudah terpasang dan siap digunakan.
Jika belum terpasang, lakukan instalasi GCC dan Make sesuai dengan sistem operasi yang digunakan.

- Jalankan perintah berikut pada terminal:
git clone https://github.com/HEHEHIHAK/PROJECT-PEMRO-UAS.git
cd PROJECT-PEMRO-UAS

- Kompilasi Menggunakan Makefile
Untuk melakukan kompilasi program menggunakan Makefile, jalankan perintah:
make
Setelah kompilasi berhasil, jalankan program dengan perintah:
./app.exe

- Kompilasi Tanpa Makefile
Jika tidak menggunakan Makefile, lakukan kompilasi secara manual menggunakan perintah GCC:
gcc -std=c99 -Wall -Wextra -Iinclude src/*.c -o app.exe
Setelah proses kompilasi selesai, jalankan program dengan perintah:
./app.exe

- Membersihkan File Hasil Kompilasi
Untuk menghapus file hasil kompilasi, jalankan perintah berikut jika target clean tersedia pada Makefile:
make clean


Catatan:
- Pastikan seluruh file sumber (.c) dan header (.h) tersedia.
- Jalankan perintah dari folder utama proyek.
- Pastikan folder data tersedia agar program dapat membaca dan menyimpan data dengan benar.