#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include "models.h"

int pinjam_buku(Book *b, int n_book, Loan **loans, int *n_loan, const char *username, const char *book_path, const char *loan_path);
int kembalikan_buku(Book *b, int n_book, Loan *loans, int n_loan, const char *username, const char *book_path, const char *loan_path);
void lihat_peminjaman_pribadi(const Loan *loans, int n_loan, const Book *b, int n_book, const char *username);
void laporan_transaksi_admin(const Loan *loans, int n_loan, const Book *b, int n_book);

#endif