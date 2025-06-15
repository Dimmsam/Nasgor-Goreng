#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Struct buat node Stack (riwayat bacaan)
typedef struct RiwayatNode {
    char judul[100];
    char genre[50];
    struct RiwayatNode* next;
} RiwayatNode;

// Struct buat Stack
typedef struct Stack {
    RiwayatNode* top;
} Stack;

// Struct buat User
typedef struct User {
    char userName[50];
    Stack* riwayatBaca;
    struct User* next;
} User;

// Stack Operations
Stack* createStack();
void push(Stack* stack, const char* judul, const char* genre);
RiwayatNode* pop(Stack* stack);
bool isStackEmpty(Stack* stack);

// Display Functions
void displayReadingHistory(Stack* stack);
void displayUserHistory(const char* userName);

// File Operations
void saveHistoryToFile(Stack* stack, const char* userName);
void loadHistoryFromFile(Stack** stack, const char* userName);

// User Management
Stack* getUserStack(const char* userName);
void addBookToUserHistory(const char* userName, const char* judul, const char* genre);
void clearAllHistory(Stack* stack);
// Global variable
extern User* userList;

#endif // STACK_H