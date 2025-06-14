#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "booklist.h"

// Struct untuk Waiting List
typedef struct WaitingNode {
    char userName[50];
    struct WaitingNode* next;
} WaitingNode; // Buat di sambungin ke booknode

// Struct terusan dari booklist.h
struct BookNode;
typedef struct BookNode BookNode;

// Operasi queue untuk Waiting List
void enqueueWaitingList(BookNode* book, const char* userName);
void dequeueWaitingList(BookNode* book);
bool isWaitingListEmpty(BookNode* book);

#endif // QUEUE_H