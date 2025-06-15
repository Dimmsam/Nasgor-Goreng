#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Admin {
    char userName[50];
    char password[50];
    struct Admin* next;
} Admin;

bool loginAdmin(const char* username, const char* password);
void saveAdminData();
void loadAdminData();

// Buat variabel global
extern Admin* adminList;

#endif