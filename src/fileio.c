#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fileio.h"

static const char *skip_ws(const char *p) {
    while (*p && isspace((unsigned char)*p)) {
        p++;
    }
    return p;
}

static const char *read_field(const char *p, char *dest, size_t max_len) {
    p = skip_ws(p);
    if (*p == '\0') return NULL;

    size_t i = 0;
    if (*p == '"') {
        p++; /* Lewati kutip pembuka */
        while (*p) {
            if (*p == '"') {
                if (*(p + 1) == '"') {
                    if (i + 1 < max_len) dest[i++] = '"';
                    p += 2;
                } else {
                    p++; /* Lewati kutip penutup */
                    break;
                }
            } else {
                if (i + 1 < max_len) dest[i++] = *p;
                p++;
            }
        }
    } else {
        while (*p && !isspace((unsigned char)*p)) {
            if (i + 1 < max_len) dest[i++] = *p;
            p++;
        }
    }
    dest[i] = '\0';
    return p;
}

int parse_book_line(const char *line, Book *out, int has_stock) {
    char buf[4096];
    strncpy(buf, line, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    size_t len = strlen(buf);
    while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
        buf[--len] = '\0';
    }

    const char *p = skip_ws(buf);
    if (*p == '\0') return 0;

    p = read_field(p, out->ocaid, sizeof(out->ocaid));
    if (!p || out->ocaid[0] == '\0') return 0;

    p = read_field(p, out->title, sizeof(out->title));
    if (!p || out->title[0] == '\0') return 0;

    p = read_field(p, out->author, sizeof(out->author));
    if (!p || out->author[0] == '\0') return 0;

    if (has_stock) {
        if (sscanf(p, "%d %d %d", &out->year, &out->page_count, &out->stok) != 3) {
            return 0;
        }
    } else {
        if (sscanf(p, "%d %d", &out->year, &out->page_count) != 2) {
            return 0;
        }
        out->stok = 3;
    }

    if (out->year <= 0 || out->page_count <= 0 || out->stok < 0) {
        return 0;
    }
    return 1;
}

static void write_escaped_field(FILE *fp, const char *s) {
    fputc('"', fp);
    for (const char *p = s; *p; p++) {
        if (*p == '"') {
            fputs("\"\"", fp);
        } else {
            fputc(*p, fp);
        }
    }
    fputc('"', fp);
}

int save_books(const char *path, const Book *b, int n) {
    char tmp_path[512];
    snprintf(tmp_path, sizeof(tmp_path), "%s.tmp", path);

    FILE *fp = fopen(tmp_path, "w");
    if (!fp) return 0;

    fprintf(fp, "ocaid title author year page_count stok\n");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%s ", b[i].ocaid);
        write_escaped_field(fp, b[i].title);
        fputc(' ', fp);
        write_escaped_field(fp, b[i].author);
        fprintf(fp, " %d %d %d\n", b[i].year, b[i].page_count, b[i].stok);
    }

    fclose(fp);
    remove(path);
    if (rename(tmp_path, path) != 0) {
        return 0;
    }
    return 1;
}

int load_books(const char *path, Book **b, int *n) {
    int from_master = 0;
    FILE *fp = fopen(path, "r");
    if (!fp) {
        fp = fopen("data/Books.txt", "r");
        if (!fp) fp = fopen("Books.txt", "r");
        if (!fp) return 0;
        from_master = 1;
    }

    int cap = 1024;
    int count = 0;
    Book *arr = malloc((size_t)cap * sizeof(Book));
    if (!arr) {
        fclose(fp);
        return 0;
    }

    char line[4096];
    int line_num = 0;
    int has_stock = !from_master;

    while (fgets(line, sizeof(line), fp)) {
        line_num++;
        if (line_num == 1 && strncmp(line, "ocaid", 5) == 0) {
            has_stock = (strstr(line, "stok") != NULL);
            continue;
        }

        Book temp;
        if (!parse_book_line(line, &temp, has_stock)) {
            continue;
        }

        int dup = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(arr[i].ocaid, temp.ocaid) == 0) {
                fprintf(stderr, "Peringatan: ocaid duplikat '%s' dilewati (baris %d).\n", temp.ocaid, line_num);
                dup = 1;
                break;
            }
        }
        if (dup) continue;

        if (count >= cap) {
            int new_cap = cap * 2;
            Book *tmp_arr = realloc(arr, (size_t)new_cap * sizeof(Book));
            if (!tmp_arr) {
                free(arr);
                fclose(fp);
                return 0;
            }
            arr = tmp_arr;
            cap = new_cap;
        }
        arr[count++] = temp;
    }

    fclose(fp);
    *b = arr;
    *n = count;

    if (from_master) {
        save_books(path, arr, count);
    }
    return 1;
}