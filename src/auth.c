#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auth.h"

int login(char username[], char role[]) {
    char inputUser[32];
    char inputPass[32];

    char simpanUser[32];
    char simpanPass[32];
    char simpanRole[12];
    FILE *file;

    printf("===== LOGIN PERPUSTAKAAN USK =====\n");

    printf("Username : ");
    scanf("%31s", inputUser);

    printf("Password : ");
    scanf("%31s", inputPass);

    file = fopen("user.txt", "r");
    if (file == NULL) {
        printf("File user.txt tidak ditemukan!\n");
        return 0;
    }
    while (fscanf(file, "%31s %31s %11s", simpanUser, simpanPass, simpanRole) == 3){
        
        if (strcmp(inputUser, simpanUser) == 0 && strcmp(inputPass, simpanPass) == 0) {

            strcpy(username, simpanUser);
            strcpy(role, simpanRole);

            fclose(file);

            printf("\nlogin berhasil!\n");
            printf("Selamat datang, %s\n", username);

            return 1;
        }
    }
    fclose(file);
    printf("\nUsername atau password salah!\n");

    return 0;

}
