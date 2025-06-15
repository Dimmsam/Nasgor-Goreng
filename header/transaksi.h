#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"
#include "booklist.h"
#include "queue.h"

// Struct untuk Transaction
typedef struct Transaction {
    char transactionId[20];
    char userName[50];
    char userRealName[50];
    char kodeBuku[20];
    char judulBuku[100];
    char status[20]; // "dipinjam" atau "dikembalikan"
} Transaction;

// Struct untuk Transaction Node (Linked List)
typedef struct TransactionNode {
    Transaction data;
    struct TransactionNode* next;
} TransactionNode;

// Operasi untuk transaksi
char* generateTransactionId();
void addTransaction(const char* userName, const char* userRealName, 
                   const char* kodeBuku, const char* judulBuku, const char* status);
bool updateTransactionStatus(const char* transactionId, const char* newStatus);

// Fungsi untuk display detail transaksi
void displayUserTransactions(const char* userName);

// Operasi File
void saveActiveTransactions();
void saveTransactionHistory();
void loadActiveTransactions();
void loadTransactionHistory();

// Proses Transaksi
bool processBookBorrow(const char* userName, const char* userRealName, const char* kodeBuku);
bool processBookReturn(const char* transactionId);

// Variabel global
extern TransactionNode* activeTransactionList;
extern TransactionNode* historyTransactionList;

#endif // TRANSAKSI_H