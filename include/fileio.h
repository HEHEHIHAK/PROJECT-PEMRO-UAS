#ifndef FILEIO_H
#define FILEIO_H

#include "models.h"

int parse_book_line(const char *line, Book *out, int has_stock);
int load_books(const char *path, Book **b, int *n);
int save_books(const char *path, const Book *b, int n);
int load_accounts(const char *path, Account **acc, int *n);
int load_loans(const char *path, Loan **loans, int *n);
int save_loans(const char *path, const Loan *loans, int n);

#endif