#ifndef SORTING_H
#define SORTING_H

#include "models.h"

// Definisi enum untuk kunci sorting (jika belum ada)
typedef enum {
    SORT_ID = 0,
    SORT_TITLE,
    SORT_AUTHOR,
    SORT_YEAR
} SortKey;

// Prototipe fungsi sorting
void sort_menu(Book *books, int n, int is_admin);
void bubble_sort(Book *arr, int n, SortKey key, int asc);
// Tambahkan prototipe sorting lainnya jika ada (selection/insertion)

#endif