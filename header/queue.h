#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "booklist.h"
#include "transaksi.h"
#include "stack.h"

// Struct untuk Waiting List
typedef struct WaitingNode {
    char userName[50];
    struct WaitingNode* next;
} WaitingNode; // Buat di sambungin ke booknode

// Struct terusan dari booklist.h
struct BookNode;
typedef struct BookNode BookNode;

// Operasi Queue waiting list
void enqueueWaitingList(BookNode* book, const char* userName);
void dequeueWaitingList(BookNode* book);
bool isWaitingListEmpty(BookNode* book);

// Operasi File
void saveWaitingList(BookNode* book);
void loadWaitingList(BookNode* book);

// Manajemen Waiting List
void processWaitingList(BookNode* book);
bool isUserInWaitingList(BookNode* book, const char* userName);

#endif // QUEUE_H