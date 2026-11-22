#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "utils.h"

void str_trim(char *s) {
    if (!s) return;
    char *start = s;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }
    size_t len = strlen(start);
    while (len > 0 && isspace((unsigned char)start[len - 1])) {
        len--;
    }
    memmove(s, start, len);
    s[len] = '\0';
}

int read_line(const char *prompt, char *buf, size_t size) {
    if (prompt) {
        printf("%s", prompt);
        fflush(stdout);
    }
    if (!fgets(buf, (int)size, stdin)) {
        return 0;
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
        if (len > 1 && buf[len - 2] == '\r') {
            buf[len - 2] = '\0';
        }
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
    str_trim(buf);
    return 1;
}

int read_int(const char *prompt, int min, int max, int *out) {
    char buf[128];
    while (1) {
        if (!read_line(prompt, buf, sizeof(buf))) {
            return 0;
        }
        if (buf[0] == '\0') {
            printf("Input tidak boleh kosong. Silakan ulangi.\n");
            continue;
        }
        char *endptr;
        long val = strtol(buf, &endptr, 10);
        if (*endptr != '\0') {
            printf("Input tidak valid (harus berupa angka). Silakan ulangi.\n");
            continue;
        }
        if (val < min || val > max) {
            printf("Input harus berada di antara %d dan %d.\n", min, max);
            continue;
        }
        *out = (int)val;
        return 1;
    }
}