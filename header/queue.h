#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Struct untuk node Queue (Waiting List)
typedef struct WaitingNode {
    char userName[50]; // Nama user yang masuk waiting list
    struct WaitingNode* next; // Pointer ke node berikutnya
} WaitingNode;

// Fungsi untuk queue (waiting list)
WaitingNode* createWaitingNode(char* userName);
void enqueue(WaitingNode** front, WaitingNode** rear, char* userName);
char* dequeue(WaitingNode** front, WaitingNode** rear);
bool isQueueEmpty(WaitingNode* front);
void displayQueue(WaitingNode* front);
void freeQueue(WaitingNode* front);


#endif
