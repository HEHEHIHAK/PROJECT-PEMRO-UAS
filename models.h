#ifndef MODELS_H
#define MODELS_H

typedef struct {
    char ocaid[64];
    char title[1200];
    char author[500];
    int year;
    int page_count;
    int stok;
} Book;

typedef struct {
    char username[32];
    char password[32];
    char role[12];
} Account;

typedef struct {
    unsigned int id_peminjaman;
    char username[32];
    char ocaid[64];
    char tanggal_pinjam[20];
    char status[20];
} Loan;

#endif