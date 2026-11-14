#include "login.h" 
#include <stdio.h>

int main(){
    
    char userName[32];
    char role[32];

    if (login(userName, role)) {
        printf("login Berhasil!\n");
    } else {
        printf("Login gagal!\n");
    }
    return 0;
}