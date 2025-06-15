#include "../header/admin.h"

Admin* adminList = NULL;

bool loginAdmin(const char* username, const char* password) {
    Admin* current = adminList;
    while (current != NULL) {
        if (strcmp(current->userName, username) == 0 && 
            strcmp(current->password, password) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void saveAdminData() {
    FILE* file = fopen("data/admin/admin.txt", "w");
    if (file == NULL) {
        printf("Error: Tidak bisa membuka file data admin\n");
        return;
    }

    Admin* current = adminList;
    while (current != NULL) {
        fprintf(file, "%s|%s\n", current->userName, current->password);
        current = current->next;
    }

    fclose(file);
}

void loadAdminData() {
    FILE* file = fopen("data/admin/admin.txt", "r");
    if (file == NULL) {
        printf("Error: Tidak bisa membuka file data admin\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char* username = strtok(line, "|");
        char* password = strtok(NULL, "|");
        
        if (username && password) {
            Admin* newAdmin = (Admin*)malloc(sizeof(Admin));
            if (newAdmin == NULL) {
                printf("Error: Alokasi memori gagal\n");
                continue;
            }
            
            strcpy(newAdmin->userName, username);
            strcpy(newAdmin->password, password);
            newAdmin->next = NULL;
            
            // Add to list
            if (adminList == NULL) {
                adminList = newAdmin;
            } else {
                Admin* current = adminList;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newAdmin;
            }
        }
    }

    fclose(file);
}