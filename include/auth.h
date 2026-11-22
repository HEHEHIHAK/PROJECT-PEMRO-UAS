#ifndef AUTH_H
#define AUTH_H

#include "models.h"

int login_cli(int argc, char *argv[], const Account *acc, int n_acc, Account *logged_in);
int login_interactive(const Account *acc, int n_acc, Account *logged_in);

#endif