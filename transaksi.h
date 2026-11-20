#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include "models.h"

int borrow_book(Book *b, int n, Loan **loans, int *lc, const char *username);
int return_book(Book *b, int n, Loan **loans, int *lc, const char *username);
int show_my_loans(const Loan *loans, int lc, const char *username);
int show_all_loans(const Loan *loans, int lc);

#endif 