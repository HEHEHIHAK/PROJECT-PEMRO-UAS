/* buku.c - Modul katalog dan CRUD buku (versi singkat) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "buku.h"
#include "fileio.h"

#define PER_HALAMAN 20
#define LOANS_FILE  "data/peminjaman.txt"

static int baca_teks(const char *prompt, char *buf, int ukuran) {
    printf("%s", prompt);
    if (fgets(buf, ukuran, stdin) == NULL) {
        buf[0] = '\0';
        return 0;
    }
        if (strchr(buf, '\n') != NULL) {
        buf[strcspn(buf, "\n")] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    return 1;
}

static int baca_angka(const char *prompt, int min, int max) {
    char teks[32];
    int angka;

    while (1) {
        if (!baca_teks(prompt, teks, sizeof(teks))) {
            return min;
        }
        if (sscanf(teks, "%d", &angka) != 1) {
            printf("Harus berupa angka.\n");
        } else if (angka < min || angka > max) {
            printf("Angka harus antara %d dan %d.\n", min, max);
        } else {
            return angka;
        }
    }
}

static int mengandung(const char *teks, const char *cari) {
    char a[1200];
    char b[1200];
    int i;

    strncpy(a, teks, sizeof(a) - 1);
    a[sizeof(a) - 1] = '\0';
    strncpy(b, cari, sizeof(b) - 1);
    b[sizeof(b) - 1] = '\0';

    for (i = 0; a[i] != '\0'; i++) {
        a[i] = tolower((unsigned char)a[i]);
    }
    for (i = 0; b[i] != '\0'; i++) {
        b[i] = tolower((unsigned char)b[i]);
    }
    return strstr(a, b) != NULL;
}

static void cetak_buku(int no, const Book *buku) {
    printf("%-4d %-22.22s %-40.40s %-20.20s %5d %5d %4d\n",
           no, buku->ocaid, buku->title, buku->author,
           buku->year, buku->page_count, buku->stok);
}

static void cetak_judul_kolom(void) {
    printf("\n%-4s %-22s %-40s %-20s %5s %5s %4s\n",
           "No", "ID", "Judul", "Pengarang", "Tahun", "Hal", "Stok");
}

static int lanjut(void) {
    char jawab[16];

    printf("-- Enter = lanjut, q = berhenti : ");
    if (fgets(jawab, sizeof(jawab), stdin) == NULL || jawab[0] == 'q' || jawab[0] == 'Q') {
        return 0;
    }
    return 1;
}

static int simpan(const Book *b, int n, const char *path) {
    if (save_books(path, b, n) == 0) {
        printf("PERINGATAN: data gagal disimpan ke file!\n");
        return -1;
    }
    return 0;
}

void tampilkan_katalog(const Book *b, int n, int hanya_tersedia) {
    int i;
    int tampil = 0;

    cetak_judul_kolom();
    for (i = 0; i < n; i++) {
        if (hanya_tersedia && b[i].stok <= 0) {
            continue; 
        }
        tampil++;
        cetak_buku(tampil, &b[i]);

        if (tampil % PER_HALAMAN == 0 && i < n - 1) {
            if (!lanjut()) {
                break;
            }
        }
    }
    if (tampil == 0) {
        printf("Tidak ada buku.\n");
    } else {
        printf("\n%d buku ditampilkan.\n", tampil);
    }
}

int cari_index_ocaid(const Book *b, int n, const char *ocaid) {
    int i;

    for (i = 0; i < n; i++) {
        if (strcmp(b[i].ocaid, ocaid) == 0) {
            return i;
        }
    }
    return -1;
}

void cari_buku(const Book *b, int n) {
    char kata[1200];
    int pilihan;
    int i;
    int ketemu = 0;

    printf("\n=== Cari Buku ===\n1. Berdasarkan ID\n2. Berdasarkan judul\n0. Kembali\n");
    pilihan = baca_angka("Pilihan: ", 0, 2);
    if (pilihan == 0) {
        return;
    }

    baca_teks("Kata kunci: ", kata, sizeof(kata));
    if (kata[0] == '\0') {
        printf("Kata kunci tidak boleh kosong.\n");
        return;
    }

    cetak_judul_kolom();
    for (i = 0; i < n; i++) {
        if ((pilihan == 1 && strcmp(b[i].ocaid, kata) == 0) ||
            (pilihan == 2 && mengandung(b[i].title, kata))) {
            ketemu++;
            cetak_buku(ketemu, &b[i]);
            if (ketemu % PER_HALAMAN == 0 && !lanjut()) {
                break;
            }
        }
    }
    if (ketemu == 0) {
        printf("Buku tidak ditemukan.\n");
    } else {
        printf("\n%d buku ditemukan.\n", ketemu);
    }
}

int tambah_buku(Book **b, int *n, const char *path) {
    Book baru;
    Book *besar;
    int i;

    printf("\n=== Tambah Buku ===\n");

    baca_teks("ID buku (ocaid) : ", baru.ocaid, sizeof(baru.ocaid));
    if (baru.ocaid[0] == '\0' || strchr(baru.ocaid, ' ') != NULL) {
        printf("ID tidak boleh kosong atau berisi spasi. Dibatalkan.\n");
        return -1;
    }
    if (cari_index_ocaid(*b, *n, baru.ocaid) != -1) {
        printf("ID sudah dipakai buku lain. Dibatalkan.\n");
        return -1;
    }

    baca_teks("Judul           : ", baru.title, sizeof(baru.title));
    baca_teks("Pengarang       : ", baru.author, sizeof(baru.author));
    if (baru.title[0] == '\0' || baru.author[0] == '\0') {
        printf("Judul dan pengarang tidak boleh kosong. Dibatalkan.\n");
        return -1;
    }

    baru.year       = baca_angka("Tahun terbit    : ", 1, 2026);
    baru.page_count = baca_angka("Jumlah halaman  : ", 1, 20000);
    baru.stok       = baca_angka("Stok            : ", 0, 999);

    besar = realloc(*b, (*n + 1) * sizeof(Book));
    if (besar == NULL) {
        printf("Memori tidak cukup.\n");
        return -1;
    }
    *b = besar;

    (*b)[*n] = baru;
    (*n)++;

    i = simpan(*b, *n, path);
    if (i == 0) {
        printf("Buku berhasil ditambahkan.\n");
    }  else {
        (*n)--;
    }
    return i;
}

int update_buku(Book *b, int n, const char *path) {
    char ocaid[64];
    char teks[1200];
    int idx;
    int pilihan;
    int selisih;
    int berubah = 0;

    printf("\n=== Ubah Buku ===\n");
    baca_teks("ID buku yang diubah: ", ocaid, sizeof(ocaid));
    idx = cari_index_ocaid(b, n, ocaid);
    if (idx == -1) {
        printf("Buku tidak ditemukan.\n");
        return -1;
    }

    do {
        printf("\nJudul: %s\nPengarang: %s\nTahun: %d | Halaman: %d | Stok: %d\n",
               b[idx].title, b[idx].author, b[idx].year, b[idx].page_count, b[idx].stok);
        printf("1. Judul  2. Pengarang  3. Tahun  4. Halaman  5. Stok (+/-)  0. Selesai\n");
        pilihan = baca_angka("Pilihan: ", 0, 5);

        if (pilihan == 1) {
            baca_teks("Judul baru: ", teks, sizeof(b[idx].title));
            if (teks[0] != '\0') {
                strcpy(b[idx].title, teks);
                berubah = 1;
            }
        } else if (pilihan == 2) {
            baca_teks("Pengarang baru: ", teks, sizeof(b[idx].author));
            if (teks[0] != '\0') {
                strcpy(b[idx].author, teks);
                berubah = 1;
            }
        } else if (pilihan == 3) {
            b[idx].year = baca_angka("Tahun baru: ", 1, 2026);
            berubah = 1;
        } else if (pilihan == 4) {
            b[idx].page_count = baca_angka("Halaman baru: ", 1, 20000);
            berubah = 1;
        } else if (pilihan == 5) {
            selisih = baca_angka("Tambah/kurangi stok (mis. 3 atau -1): ", -999, 999);
            if (b[idx].stok + selisih < 0) {
                printf("Stok tidak boleh kurang dari 0.\n");
            } else {
                b[idx].stok += selisih;
                berubah = 1;
            }
        }
    } while (pilihan != 0);

    if (!berubah) {
        printf("Tidak ada perubahan.\n");
        return -1;
    }
    if (simpan(b, n, path) != 0) {
        return -1;
    }
    printf("Perubahan disimpan.\n");
    return 0;
}

int hapus_buku(Book *b, int *n, const char *path) {
    char ocaid[64];
    char jawab[16];
    Loan *loans = NULL;
    int jumlah_loan = 0;
    int dipinjam = 0;
    int idx;
    int i;

    printf("\n=== Hapus Buku ===\n");
    baca_teks("ID buku yang dihapus: ", ocaid, sizeof(ocaid));
    idx = cari_index_ocaid(b, *n, ocaid);
    if (idx == -1) {
        printf("Buku tidak ditemukan.\n");
        return -1;
    }

    if (load_loans(LOANS_FILE, &loans, &jumlah_loan) == 0) {
        jumlah_loan = 0;
    }
    for (i = 0; loans != NULL && i < jumlah_loan; i++) {
        if (strcmp(loans[i].ocaid, ocaid) == 0 && strcmp(loans[i].status, "DIPINJAM") == 0) {
            dipinjam = 1;
        }
    }
    free(loans);

    if (dipinjam) {
        printf("Buku sedang dipinjam, tidak bisa dihapus.\n");
        return -1;
    }

    printf("Hapus \"%s\"?\n", b[idx].title);
    baca_teks("Ketik y untuk ya, lainnya batal: ", jawab, sizeof(jawab));
    if (jawab[0] != 'y' && jawab[0] != 'Y') {
        printf("Dibatalkan.\n");
        return -1;
    }

    for (i = idx; i < *n - 1; i++) {
        b[i] = b[i + 1];
    }
    (*n)--;

    if (simpan(b, *n, path) != 0) {
        return -1;
    }
    printf("Buku dihapus.\n");
    return 0;
}