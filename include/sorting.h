#ifndef SORTING_H
#define SORTING_H

#include "models.h"

// Enum atribut yang diurutkan
typedef enum {
    KEY_OCAID,
    KEY_TITLE,
    KEY_YEAR,
    KEY_PAGES,
    KEY_STOCK
} SortKey;

// Fungsi bubble sort dan menu sorting
void bubble_sort(Book *arr, int n, SortKey key, int asc);
void sort_menu(const Book *b, int n, int only_available);

#endif