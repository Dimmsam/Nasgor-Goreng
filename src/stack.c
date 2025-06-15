#include "../header/stack.h"


User* userList = NULL;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

void push(Stack* stack, const char* judul, const char* genre) {
    RiwayatNode* newNode = (RiwayatNode*)malloc(sizeof(RiwayatNode));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed\n");
        return;
    }

    strcpy(newNode->judul, judul);
    strcpy(newNode->genre, genre);
    newNode->next = stack->top;
    stack->top = newNode;
}

RiwayatNode* pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        return NULL;
    }

    RiwayatNode* temp = stack->top;
    stack->top = stack->top->next;
    return temp;
}

bool isStackEmpty(Stack* stack) {
    return (stack->top == NULL);
}

void displayReadingHistory(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Reading history is empty\n");
        return;
    }

    printf("\nReading History:\n");
    printf("----------------------------------------\n");
    
    RiwayatNode* current = stack->top;
    int position = 1;
    
    while (current != NULL) {
        printf("%d. Title: %s\n", position++, current->judul);
        printf("   Genre: %s\n", current->genre);
        printf("----------------------------------------\n");
        current = current->next;
    }
}

void displayUserHistory(const char* userName) {
    Stack* userStack = getUserStack(userName);
    if (userStack != NULL) {
        displayReadingHistory(userStack);
    } else {
        printf("No reading history found for user %s\n", userName);
    }
}

void saveHistoryToFile(Stack* stack, const char* userName) {
    char filename[256];
    sprintf(filename, "data/statistics/%s_history.txt", userName);
    
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Cannot open history file for writing\n");
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
        printf("Error: Cannot open history file for reading\n");
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
            printf("Error: Memory allocation failed\n");
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
        printf("Riwayat sudah kosong\n");
        return;
    }

    RiwayatNode* current = stack->top;
    while (current != NULL) {
        RiwayatNode* temp = current;
        current = current->next;
        free(temp);
    }
    stack->top = NULL;
    printf("Semua Riwayat Bacaan Sudah Dibersihkan\n");
}