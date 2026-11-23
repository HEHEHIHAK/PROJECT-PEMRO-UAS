#ifndef SORTING_H
#define SORTING_H

#include "models.h"

// Gunakan konstanta key sesuai yang dipakai di sorting.c
typedef enum {
    KEY_OCAID = 0,
    KEY_TITLE,
    KEY_YEAR,
    KEY_PAGES,
    KEY_STOCK
} SortKey;

// Samakan parameter sort_menu menjadi (const Book *b, int n, int only_available)
void sort_menu(const Book *b, int n, int only_available);
void bubble_sort(Book *arr, int n, SortKey key, int asc);

#endif