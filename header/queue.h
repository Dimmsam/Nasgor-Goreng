#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Struct untuk Waiting List
typedef struct WaitingNode {
    char userName[50];
    struct WaitingNode* next;
} WaitingNode; // Buat di sambungin ke booknode

#endif // QUEUE_H