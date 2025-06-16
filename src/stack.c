#include "../header/stack.h"


User* userList = NULL;

Stack* createStack() {    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("\t\t\t\t\t\tError: Gagal alokasi memori\n");
        getchar();
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

void push(Stack* stack, const char* judul, const char* genre) {
    RiwayatNode* newNode = (RiwayatNode*)malloc(sizeof(RiwayatNode));
    if (newNode == NULL) {
        printf("\t\t\t\t\t\tError: Gagal alokasi memori\n");
        getchar();
        return;
    }

    strcpy(newNode->judul, judul);
    strcpy(newNode->genre, genre);
    newNode->next = stack->top;
    stack->top = newNode;
}

//RiwayatNode* pop(Stack* stack) {
//    if (isStackEmpty(stack)) {
//        return NULL;
//    }
//
//    RiwayatNode* temp = stack->top;
//    stack->top = stack->top->next;
//    return temp;
//}

bool isStackEmpty(Stack* stack) {
    return (stack->top == NULL);
}

void displayReadingHistory(Stack* stack) {    if (isStackEmpty(stack)) {
        printf("\t\t\t\t\t\tRiwayat bacaan kosong\n");
        return;
    }

    printf("\t\t\t\t\t\tRiwayat Bacaan:\n");
    printf("\t\t\t\t\t\t----------------------------------------\n");
    
    RiwayatNode* current = stack->top;
    int position = 1;
    
    while (current != NULL) {        printf("\t\t\t\t\t\t%d. Judul: %s\n", position++, current->judul);
        printf("\t\t\t\t\t\t   Genre: %s\n", current->genre);
        printf("\t\t\t\t\t\t----------------------------------------\n");
        current = current->next;
    }
}

void displayUserHistory(const char* userName) {
    Stack* userStack = getUserStack(userName);
    if (userStack != NULL) {
        displayReadingHistory(userStack);
    } else {
        printf("\t\t\t\t\t\tTidak ditemukan riwayat bacaan untuk pengguna %s\n", userName);
    }
}

void saveHistoryToFile(Stack* stack, const char* userName) {
    char filename[256];
    sprintf(filename, "data/statistics/%s_history.txt", userName);
    
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("\t\t\t\t\t\tError: Tidak dapat membuka file riwayat untuk menulis\n");
        getchar();
        return;
    }

    RiwayatNode* current = stack->top;
    while (current != NULL) {
        fprintf(file, "%s|%s\n", current->judul, current->genre);
        current = current->next;
    }

    fclose(file);
}

void loadHistoryFromFile(Stack** stack, const char* userName) {
    char filename[256];
    sprintf(filename, "data/statistics/%s_history.txt", userName);
    
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("\t\t\t\t\t\tError: Tidak dapat membuka file riwayat untuk dibaca\n");
        getchar();
        return;
    }

    if (*stack == NULL) {
        *stack = createStack();
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        
        line[strcspn(line, "\n")] = 0;
        
        char* judul = strtok(line, "|");
        char* genre = strtok(NULL, "|");
        
        if (judul && genre) {
            push(*stack, judul, genre);
        }
    }

    fclose(file);
}

Stack* getUserStack(const char* userName) {
    User* current = userList;
    while (current != NULL) {
        if (strcmp(current->userName, userName) == 0) {
            return current->riwayatBaca;
        }
        current = current->next;
    }
    return NULL;
}

void addBookToUserHistory(const char* userName, const char* judul, const char* genre) {
    // Cari atau create user
    User* current = userList;
    User* prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->userName, userName) == 0) {
            break;
        }
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        // Create new user
        current = (User*)malloc(sizeof(User));
        if (current == NULL) {
            printf("\t\t\t\t\t\tError: Gagal alokasi memori\n");
            getchar();
            return;
        }
        
        strcpy(current->userName, userName);
        current->riwayatBaca = createStack();
        current->next = NULL;

        if (prev == NULL) {
            userList = current;
        } else {
            prev->next = current;
        }
    }

    // Add book to history
    push(current->riwayatBaca, judul, genre);
    saveHistoryToFile(current->riwayatBaca, userName);
}

void clearAllHistory(Stack* stack) {
    if (stack == NULL || stack->top == NULL) {
        printf("\t\t\t\t\t\tRiwayat sudah kosong\n");
        return;
    }

    RiwayatNode* current = stack->top;
    while (current != NULL) {
        RiwayatNode* temp = current;
        current = current->next;
        free(temp);
    }
    stack->top = NULL;
    printf("\t\t\t\t\t\tSemua Riwayat Bacaan Sudah Dibersihkan\n");
}