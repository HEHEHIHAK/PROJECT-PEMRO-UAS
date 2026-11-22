#ifndef BUKU_H
#define BUKU_H

#include "models.h"

void tampilkan_katalog(const Book *b, int n, int hanya_tersedia);
void cari_buku(const Book *b, int n);
int tambah_buku(Book **b, int *n, const char *path);
int update_buku(Book *b, int n, const char *path);
int hapus_buku(Book *b, int *n, const char *path);
int cari_index_ocaid(const Book *b, int n, const char *ocaid);

#endif