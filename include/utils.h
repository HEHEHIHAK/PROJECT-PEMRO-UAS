#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include "models.h"

int read_line(const char *prompt, char *buf, size_t size);
int read_int(const char *prompt, int min, int max, int *out);
void str_trim(char *s);
void get_today(char *buf, size_t size);
unsigned int next_loan_id(const Loan *loans, int n);

#endif