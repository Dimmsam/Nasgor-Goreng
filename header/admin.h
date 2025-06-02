#ifndef ADMIN_H
#define ADMIN_H

typedef struct Admin {
    char username[50];
    char password[50];
    struct Admin* next;
} Admin;

// Fungsi
Admin* createAdmin(const char* username, const char* password);
void addAdmin(Admin** head, const char* username, const char* password);
int loginAdmin(Admin* head, const char* username, const char* password);
void registerAdmin(Admin** head);

#endif