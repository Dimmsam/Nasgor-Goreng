#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"

Admin* createAdmin(const char* username, const char* password) {
    Admin* newAdmin = (Admin*)malloc(sizeof(Admin));
    strcpy(newAdmin->username, username);
    strcpy(newAdmin->password, password);
    newAdmin->next = NULL;
    return newAdmin;
}