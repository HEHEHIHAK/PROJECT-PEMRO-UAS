// Fungsi untuk memproses peminjaman buku
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/transaksi.h"
#include "../include/buku.h"
#include "../include/fileio.h"
#include "../include/utils.h"


/* Fungsi untuk memproses peminjaman buku */
int borrow_book(Book *b, int n, Loan **loans, int *lc,
                const char *username)
{
    char ocaid[64];
    int index;

    printf("\n=== PEMINJAMAN BUKU ===\n");
    printf("Masukkan OCAID buku: ");

    if (scanf("%63s", ocaid) != 1) {
        printf("Input tidak valid.\n");
        return 1;
    }

    index = cari_index_ocaid(b, n, ocaid);

    if (index == -1) {
        printf("Buku tidak ditemukan.\n");
        return 1;
    }

    if (b[index].stok <= 0) {
        printf("Stok buku sedang habis.\n");
        return 1;
    }

    for (int i = 0; i < *lc; i++) {
        if (strcmp((*loans)[i].username, username) == 0 &&
            strcmp((*loans)[i].ocaid, ocaid) == 0 &&
            strcmp((*loans)[i].status, "DIPINJAM") == 0) {
            printf("Kamu masih meminjam buku ini.\n");
            return 1;
        }
    }

    Loan *temp = realloc(*loans, (*lc + 1) * sizeof(Loan));

    if (temp == NULL) {
        printf("Gagal mengalokasikan memori.\n");
        return 1;
    }

    *loans = temp;

    Loan new_loan = {0};

    new_loan.id_peminjaman = next_loan_id(*loans, *lc);

    snprintf(new_loan.username, sizeof(new_loan.username),
             "%s", username);

    snprintf(new_loan.ocaid, sizeof(new_loan.ocaid),
             "%s", ocaid);

    get_today(new_loan.tanggal_pinjam,
             sizeof(new_loan.tanggal_pinjam));

    snprintf(new_loan.status, sizeof(new_loan.status),
             "%s", "DIPINJAM");

    (*loans)[*lc] = new_loan;
    (*lc)++;

    b[index].stok--;

    if (save_books("data/books_data.txt", b, n) == 0 ||
        save_loans("data/peminjaman.txt", *loans, *lc) == 0) {
        b[index].stok++;
        (*lc)--;

        save_books("data/books_data.txt", b, n);
        save_loans("data/peminjaman.txt", *loans, *lc);

        printf("Gagal menyimpan transaksi.\n");
        return 1;
    }

    printf("Peminjaman berhasil!\n");
    printf("ID Peminjaman: %u\n", new_loan.id_peminjaman);

    return 0;
}

int return_book(Book *b, int n, Loan **loans, int *lc, const char *username) {
    unsigned int id;
    printf("\n=== PENGEMBALIAN BUKU ===\n");
    printf("Masukkan ID Peminjaman yang ingin dikembalikan: ");
    if (scanf("%u", &id) != 1) {
        while (getchar() != '\n');
        printf("ID tidak valid!\n");
        return 0;
    }
    while (getchar() != '\n');

    for (int i = 0; i < *lc; i++) {
        if ((*loans)[i].id_peminjaman == id &&
            strcmp((*loans)[i].username, username) == 0 &&
            (strcmp((*loans)[i].status, "DIPINJAM") == 0 || strcmp((*loans)[i].status, "Dipinjam") == 0)) {
            
            strcpy((*loans)[i].status, "DIKEMBALIKAN");
            for (int j = 0; j < n; j++) {
                if (strcmp(b[j].ocaid, (*loans)[i].ocaid) == 0) {
                    b[j].stok++;
                    break;
                }
            }

            // Simpan perubahan ke file teks secara otomatis
            save_books("data/books_data.txt", b, n);
            save_loans("data/peminjaman.txt", *loans, *lc);

            printf("Buku dengan ID Peminjaman %u berhasil dikembalikan!\n", id);
            return 1;
        }
    }
    printf("Data peminjaman aktif tidak ditemukan.\n");
    return 0;
}

int show_my_loans(const Loan *loans, int lc, const char *username) {
    int found = 0;
    printf("\n=== DAFTAR PINJAMAN SAYA (%s) ===\n", username);
    printf("%-5s | %-15s | %-15s | %-15s\n", "ID", "ID Buku", "Tgl Pinjam", "Status");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < lc; i++) {
        if (strcmp(loans[i].username, username) == 0) {
            printf("%-5u | %-15s | %-15s | %-15s\n",
                   loans[i].id_peminjaman, loans[i].ocaid,
                   loans[i].tanggal_pinjam, loans[i].status);
            found = 1;
        }
    }
    if (!found) {
        printf("Belum ada riwayat peminjaman.\n");
    }
    return found;
}

int show_all_loans(const Loan *loans, int lc) {
    printf("\n=== LAPORAN SELURUH TRANSAKSI PEMINJAMAN ===\n");
    if (lc == 0) {
        printf("Belum ada data transaksi peminjaman.\n");
        return 0;
    }
    printf("%-5s | %-15s | %-15s | %-15s | %-15s\n", "ID", "Username", "ID Buku", "Tgl Pinjam", "Status");
    printf("---------------------------------------------------------------------------\n");
    for (int i = 0; i < lc; i++) {
        printf("%-5u | %-15s | %-15s | %-15s | %-15s\n",
               loans[i].id_peminjaman, loans[i].username, loans[i].ocaid,
               loans[i].tanggal_pinjam, loans[i].status);
    }
    return 1;
}