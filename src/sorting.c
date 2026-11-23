#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../include/models.h"
#include "../include/sorting.h"

// Deklarasi fungsi katalog dari modul Dwi (buku.h)
extern void tampilkan_katalog(salinan, n, only_available);
/* --- 1. KOMPARATOR --- */

// Pembanding judul case-insensitive agar tidak terpengaruh huruf besar/kecil
static int compare_icase(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        int diff = tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
        if (diff != 0) return diff;
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

// Pembanding 5 atribut data buku
static int compare_books(const Book *a, const Book *b, SortKey key) {
    switch (key) {
        case KEY_OCAID:
            return strcmp(a->ocaid, b->ocaid);
        case KEY_TITLE:
            return compare_icase(a->title, b->title);
        case KEY_YEAR:
            return (a->year > b->year) - (a->year < b->year);
        case KEY_PAGES:
            return (a->page_count > b->page_count) - (a->page_count < b->page_count);
        case KEY_STOCK:
            return (a->stok > b->stok) - (a->stok < b->stok);
        default:
            return 0;
    }
}

// Helper penentu pertukaran (1 jika posisi a dan b salah urutan)
static int out_of_order(const Book *a, const Book *b, SortKey key, int asc) {
    int c = compare_books(a, b, key);
    return asc ? (c > 0) : (c < 0);
}

/* --- 2. BUBBLE SORT --- */

void bubble_sort(Book *arr, int n, SortKey key, int asc) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (out_of_order(&arr[j], &arr[j + 1], key, asc)) {
                Book temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        // Berhenti lebih awal jika array sudah terurut
        if (!swapped) break;
    }
}

/* --- 3. MENU PENGURUTAN (BUBBLE SORT) --- */

void sort_menu(const Book *b, int n, int only_available) {
    if (b == NULL || n <= 0) {
        printf("\nKatalog kosong, tidak ada data untuk diurutkan.\n");
        return;
    }

    int pilihan_key = 0;
    int pilihan_arah = 0;

    printf("\n=== PENGURUTAN BUKU (BUBBLE SORT) ===\n");
    printf("Pilih Atribut Kunci:\n");
    printf("1. ID Buku (ocaid)\n");
    printf("2. Judul (title)\n");
    printf("3. Tahun Publikasi (year)\n");
    printf("4. Jumlah Halaman (page_count)\n");
    printf("5. Stok Buku (stok)\n");
    printf("Pilihan (1-5): ");
    if (scanf("%d", &pilihan_key) != 1 || pilihan_key < 1 || pilihan_key > 5) {
        while (getchar() != '\n');
        printf("Pilihan atribut tidak valid!\n");
        return;
    }

    printf("\nPilih Arah Urutan:\n");
    if (pilihan_key == 2) {
        printf("1. A - Z (Naik)\n");
        printf("2. Z - A (Turun)\n");
    } else if (pilihan_key == 3) {
        printf("1. Terlama ke Terbaru\n");
        printf("2. Terbaru ke Terlama\n");
    } else {
        printf("1. Ascending (Terkecil ke Terbesar)\n");
        printf("2. Descending (Terbesar ke Terkecil)\n");
    }
    printf("Pilihan (1-2): ");
    if (scanf("%d", &pilihan_arah) != 1 || pilihan_arah < 1 || pilihan_arah > 2) {
        while (getchar() != '\n');
        printf("Pilihan arah tidak valid!\n");
        return;
    }

    SortKey key = (SortKey)(pilihan_key - 1);
    int ascending = (pilihan_arah == 1) ? 1 : 0;

    // Salin array agar katalog data asli tidak berantakan
    Book *salinan = (Book *)malloc(n * sizeof(Book));
    if (salinan == NULL) {
        printf("Alokasi memori gagal!\n");
        return;
    }
    memcpy(salinan, b, n * sizeof(Book));

    printf("\nSedang mengurutkan dengan Bubble Sort...\n");
    clock_t start = clock();
    bubble_sort(salinan, n, key, ascending);
    clock_t end = clock();

    double waktu_detik = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Pengurutan selesai dalam waktu: %.4f detik.\n\n", waktu_detik);

    // Tampilkan hasil pengurutan
    show_catalog(salinan, n, only_available);

    // Bebaskan memori salinan
    free(salinan);
}