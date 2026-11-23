#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/models.h"
#include "../include/sorting.h"

// Deklarasi fungsi login yang sudah kamu buat sebelumnya
int login(char username[], char role[]);

// Prototipe fungsi menu navigasi
void menu_admin(Book *books, int n_books);
void menu_user(Book *books, int n_books, const char *username);

int main(void) {
    char current_user[32] = "";
    char current_role[12] = "";

    // Data dummy buku untuk uji coba menu dan sorting sebelum modul Gibran digabung
    Book books[3] = {
        {"BK001", "Algoritma Pemrograman C", "Penulis A", 2021, 350, 5},
        {"BK002", "Struktur Data Lanjut", "Penulis B", 2019, 420, 2},
        {"BK003", "Sistem Basis Data", "Penulis C", 2023, 210, 4}
    };
    int n_books = 3;

    int running = 1;
    while (running) {
        printf("\n===========================================\n");
        printf("   SISTEM MANAJEMEN PERPUSTAKAAN (CLI)     \n");
        printf("===========================================\n");
        printf("1. Login ke Sistem\n");
        printf("0. Keluar dari Program\n");
        printf("Pilih opsi: ");

        int opsi = -1;
        if (scanf("%d", &opsi) != 1) {
            while (getchar() != '\n'); // Bersihkan buffer input
            continue;
        }

        if (opsi == 0) {
            printf("\nTerima kasih telah menggunakan sistem perpustakaan.\n");
            running = 0;
            break;
        } else if (opsi == 1) {
            // Jalankan fungsi login milikmu
            if (login(current_user, current_role)) {
                // Percabangan hak akses berdasarkan role
                if (strcmp(current_role, "admin") == 0) {
                    menu_admin(books, n_books);
                } else if (strcmp(current_role, "user") == 0) {
                    menu_user(books, n_books, current_user);
                } else {
                    printf("Role tidak dikenal!\n");
                }
            } else {
                printf("\nLogin gagal. Kembali ke menu utama.\n");
            }
        } else {
            printf("Pilihan tidak valid!\n");
        }
    }

    return 0;
}

// -------------------------------------------------------------
// 1. MENU NAVIGASI ADMIN (PUSTAKAWAN)
// -------------------------------------------------------------
void menu_admin(Book *books, int n_books) {
    int pilihan = -1;
    while (pilihan != 0) {
        printf("\n=====================================\n");
        printf("         MENU UTAMA: ADMIN           \n");
        printf("=====================================\n");
        printf("1. Lihat Seluruh Katalog Buku\n");
        printf("2. Urutkan Katalog (Sorting)\n");
        printf("3. Cari Buku\n");
        printf("4. Tambah Koleksi Buku Baru\n");
        printf("5. Perbarui Data / Stok Buku\n");
        printf("6. Hapus Buku dari Katalog\n");
        printf("7. Laporan Transaksi Peminjaman\n");
        printf("0. Logout (Keluar Akun)\n");
        printf("-------------------------------------\n");
        printf("Pilih menu (0-7): ");

        if (scanf("%d", &pilihan) != 1) {
            while (getchar() != '\n');
            printf("Input harus berupa angka!\n");
            continue;
        }

        switch (pilihan) {
            case 1:
                printf("\n[Fitur Modul Dwi: Menampilkan seluruh katalog]\n");
                break;
            case 2:
                // Memanggil fungsi modul sorting milikmu
                // only_available = 0 (karena Admin melihat semua buku termasuk stok 0)
                sort_menu(books, n_books, 0);
                break;
            case 3:
                printf("\n[Fitur Modul Dwi: Pencarian buku]\n");
                break;
            case 4:
                printf("\n[Fitur Modul Dwi: Menambahkan buku baru]\n");
                break;
            case 5:
                printf("\n[Fitur Modul Dwi: Memperbarui buku/stok]\n");
                break;
            case 6:
                printf("\n[Fitur Modul Dwi: Menghapus buku]\n");
                break;
            case 7:
                printf("\n[Fitur Modul Azna: Laporan transaksi peminjaman]\n");
                break;
            case 0:
                printf("\nBerhasil logout dari akun Admin.\n");
                break;
            default:
                printf("Pilihan menu tidak valid!\n");
        }
    }
}

// -------------------------------------------------------------
// 2. MENU NAVIGASI USER (MAHASISWA/ANGGOTA)
// -------------------------------------------------------------
void menu_user(Book *books, int n_books, const char *username) {
    int pilihan = -1;
    while (pilihan != 0) {
        printf("\n=====================================\n");
        printf("      MENU UTAMA: USER (%s)          \n", username);
        printf("=====================================\n");
        printf("1. Lihat Katalog Buku Tersedia\n");
        printf("2. Urutkan Katalog (Sorting)\n");
        printf("3. Cari Buku\n");
        printf("4. Pinjam Buku\n");
        printf("5. Kembalikan Buku\n");
        printf("6. Daftar Pinjaman Aktif Saya\n");
        printf("0. Logout (Keluar Akun)\n");
        printf("-------------------------------------\n");
        printf("Pilih menu (0-6): ");

        if (scanf("%d", &pilihan) != 1) {
            while (getchar() != '\n');
            printf("Input harus berupa angka!\n");
            continue;
        }

        switch (pilihan) {
            case 1:
                printf("\n[Fitur Modul Dwi: Menampilkan katalog buku yang tersedia (stok > 0)]\n");
                break;
            case 2:
                // Memanggil fungsi modul sorting milikmu
                // only_available = 1 (User hanya melihat buku yang tersedia)
                sort_menu(books, n_books, 1);
                break;
            case 3:
                printf("\n[Fitur Modul Dwi: Pencarian buku]\n");
                break;
            case 4:
                printf("\n[Fitur Modul Azna: Peminjaman buku]\n");
                break;
            case 5:
                printf("\n[Fitur Modul Azna: Pengembalian buku]\n");
                break;
            case 6:
                printf("\n[Fitur Modul Azna: Riwayat pinjaman aktif user]\n");
                break;
            case 0:
                printf("\nBerhasil logout dari akun User.\n");
                break;
            default:
                printf("Pilihan menu tidak valid!\n");
        }
    }
}