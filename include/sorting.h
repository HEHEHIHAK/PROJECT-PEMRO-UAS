#ifndef SORTING_H
#define SORTING_H

#include "models.h"

/* attr: 1=ocaid, 2=title, 3=year, 4=page_count, 5=stok | asc: 1=Ascending, 0=Descending */
void bubble_sort_books(Book *b, int n, int attr, int asc);
void selection_sort_books(Book *b, int n, int attr, int asc);
void insertion_sort_books(Book *b, int n, int attr, int asc);
void menu_sorting_katalog(Book *b, int n);

#endif