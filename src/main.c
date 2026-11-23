#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/models.h"
#include "../include/auth.h"
#include "../include/buku.h"
#include "../include/fileio.h"
#include "../include/sorting.h"
#include "../include/transaksi.h"
#include "../include/utils.h"

#define BOOKS_FILE "data/books_data.txt"
#define LOANS_FILE "data/peminjaman.txt"

void menu_admin(Book **books, int *n_books);
void menu_user(Book **books, int *n_books, Loan **loans, int *n_loans,
               const char *username);

int main(void) {
    char current_user[32] = "";
    char current_role[12] = "";
    Book *books = NULL;
    int n_books = 0;
    Loan *loans = NULL;
    int n_loans = 0;

    if (!load_books(BOOKS_FILE, &books, &n_books)) {
        printf("Gagal membaca data buku!\n");
        return 1;
    }
    if (!load_loans(LOANS_FILE, &loans, &n_loans)) {
        printf("Gagal membaca data peminjaman!\n");
        free(books);
        return 1;
    }

    while (1) {
        int opsi;

        printf("\n===========================================\n");
        printf("   SISTEM MANAJEMEN PERPUSTAKAAN (CLI)     \n");
        printf("===========================================\n");
        printf("1. Login ke Sistem\n");
        printf("0. Keluar dari Program\n");

        if (!read_int("Pilih opsi (0-1): ", 0, 1, &opsi) || opsi == 0) {
            printf("\nTerima kasih telah menggunakan sistem perpustakaan.\n");
            break;
        }

        if (login(current_user, current_role)) {
            if (strcmp(current_role, "admin") == 0) {
                menu_admin(&books, &n_books);
            } else if (strcmp(current_role, "user") == 0) {
                menu_user(&books, &n_books, &loans, &n_loans, current_user);
            } else {
                printf("Role tidak dikenal!\n");
            }
        } else {
            printf("\nLogin gagal. Kembali ke menu utama.\n");
        }
    }

    free(books);
    free(loans);
    return 0;
}

void menu_admin(Book **books, int *n_books) {
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

        if (!read_int("Pilih menu (0-7): ", 0, 7, &pilihan)) {
            break;
        }

        switch (pilihan) {
            case 1: tampilkan_katalog(*books, *n_books, 0); break;
            case 2: sort_menu(*books, *n_books, 0); break;
            case 3: cari_buku(*books, *n_books); break;
            case 4: tambah_buku(books, n_books, BOOKS_FILE); break;
            case 5: update_buku(*books, *n_books, BOOKS_FILE); break;
            case 6: hapus_buku(*books, n_books, BOOKS_FILE); break;
            case 7: printf("\n[Fitur Modul Azna: Laporan transaksi peminjaman]\n"); break;
            case 0: printf("\nBerhasil logout dari akun Admin.\n"); break;
        }
    }
}

void menu_user(Book **books, int *n_books, Loan **loans, int *n_loans,
               const char *username) {
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

        if (!read_int("Pilih menu (0-6): ", 0, 6, &pilihan)) {
            break;
        }

        switch (pilihan) {
            case 1: tampilkan_katalog(*books, *n_books, 1); break;
            case 2: sort_menu(*books, *n_books, 1); break;
            case 3: cari_buku(*books, *n_books); break;
            case 4: borrow_book(*books, *n_books, loans, n_loans, username); break;
            case 5: printf("\n[Fitur Modul Azna: Pengembalian buku]\n"); break;
            case 6: printf("\n[Fitur Modul Azna: Pinjaman aktif]\n"); break;
            case 0: printf("\nBerhasil logout dari akun User.\n"); break;
        }
    }
}