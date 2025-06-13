#ifndef ADMIN_H
#define ADMIN_H

// Struct untuk Admin
typedef struct Admin {
    char userName[50];
    char password[50];
    struct Admin* next;
} Admin;

#endif