#include <stdio.h>
#include <string.h>
#include "models.h"

/* Mengembalikan 1 jika login berhasil, 0 jika gagal.
   Saat berhasil, username dan role terisi. */
int login(char username[], char role[]) {
    char input_user[32], input_pass[32];
    char line[256];
    FILE *f = fopen("data/user.txt", "r");
    if (!f) f = fopen("user.txt", "r");
    if (!f) {
        printf("File akun (user.txt) tidak ditemukan!\n");
        return 0;
    }

    printf("Username: ");
    if (scanf("%31s", input_user) != 1) { fclose(f); return 0; }
    printf("Password: ");
    if (scanf("%31s", input_pass) != 1) { fclose(f); return 0; }
    while (getchar() != '\n');

    while (fgets(line, sizeof(line), f)) {
        Account a;
        if (sscanf(line, " %31[^,\n],%31[^,\n],%11s", a.username, a.password, a.role) != 3 &&
            sscanf(line, " %31s %31s %11s", a.username, a.password, a.role) != 3)
            continue;
        if (strcmp(a.username, input_user) == 0 && strcmp(a.password, input_pass) == 0) {
            strcpy(username, a.username);
            strcpy(role, a.role);
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    printf("Username atau password salah!\n");
    return 0;
}
