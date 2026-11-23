#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/models.h"
#include "../include/sorting.h"
#include "../include/buku.h"
#include "../include/fileio.h"
#include "../include/transaksi.h"

// Sesuaikan nama file .txt dengan isi folder data/ kalian
#define BOOKS_FILE "data/books_data.txt"
#define LOANS_FILE "data/loans_data.txt"

// Deklarasi fungsi login yang sudah kamu buat sebelumnya
int login(char username[], char role[]);

// Prototipe fungsi menu navigasi
void menu_admin(Book **books, int *n_books, Loan **loans, int *n_loans);
void menu_user(Book *books, int n_books, Loan **loans, int *n_loans, const char *username);

int main(void) {
    char current_user[32] = "";
    char current_role[12] = "";

    Book *books = NULL;
    int n_books = 0;

    Loan *loans = NULL;
    int n_loans = 0;

    // 1. Muat data buku dari file .txt (Modul File I/O)
    if (!load_books(BOOKS_FILE, &books, &n_books) || n_books == 0) {
        // Cadangan otomatis jika nama filenya books.txt
        load_books("data/books.txt", &books, &n_books);
    }

    // 2. Muat data peminjaman dari file .txt
    if (!load_loans(LOANS_FILE, &loans, &n_loans)) {
        load_loans("data/loans.txt", &loans, &n_loans);
    }

    printf("[Info] Berhasil memuat %d buku dan %d data peminjaman.\n", n_books, n_loans);

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
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n'); // Bersihkan sisa Enter

        if (opsi == 0) {
            printf("\nTerima kasih telah menggunakan sistem perpustakaan.\n");
            running = 0;
            break;
        } else if (opsi == 1) {
            if (login(current_user, current_role)) {
                if (strcmp(current_role, "admin") == 0) {
                    menu_admin(&books, &n_books, &loans, &n_loans);
                } else if (strcmp(current_role, "user") == 0) {
                    menu_user(books, n_books, &loans, &n_loans, current_user);
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

    free(books);
    free(loans);
    return 0;
}

// -------------------------------------------------------------
// 1. MENU NAVIGASI ADMIN (PUSTAKAWAN)
// -------------------------------------------------------------
void menu_admin(Book **books, int *n_books, Loan **loans, int *n_loans) {
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
        while (getchar() != '\n'); // Bersihkan sisa Enter sebelum masuk ke fungsi modul

        switch (pilihan) {
            case 1:
                tampilkan_katalog(*books, *n_books, 0);
                break;
            case 2:
                sort_menu(*books, *n_books, 0);
                break;
            case 3:
                cari_buku(*books, *n_books);
                break;
            case 4:
                tambah_buku(books, n_books, BOOKS_FILE);
                break;
            case 5:
                update_buku(*books, *n_books, BOOKS_FILE);
                break;
            case 6:
                hapus_buku(*books, n_books, BOOKS_FILE);
                break;
            case 7:
                show_all_loans(*loans, *n_loans);
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
void menu_user(Book *books, int n_books, Loan **loans, int *n_loans, const char *username) {
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
        while (getchar() != '\n'); // Bersihkan sisa Enter sebelum masuk ke fungsi modul

        switch (pilihan) {
            case 1:
                tampilkan_katalog(books, n_books, 1);
                break;
            case 2:
                sort_menu(books, n_books, 1);
                break;
            case 3:
                cari_buku(books, n_books);
                break;
            case 4:
                borrow_book(books, n_books, loans, n_loans, username);
                save_books(BOOKS_FILE, books, n_books);
                save_loans(LOANS_FILE, *loans, *n_loans);
                break;
            case 5:
                return_book(books, n_books, loans, n_loans, username);
                save_books(BOOKS_FILE, books, n_books);
                save_loans(LOANS_FILE, *loans, *n_loans);
                break;
            case 6:
                show_my_loans(*loans, *n_loans, username);
                break;
            case 0:
                printf("\nBerhasil logout dari akun User.\n");
                break;
            default:
                printf("Pilihan menu tidak valid!\n");
        }
    }
}