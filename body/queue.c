#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/queue.h"

// Membuat node baru untuk waiting list
WaitingNode* createWaitingNode(char* userName) {
    WaitingNode* newNode = (WaitingNode*)malloc(sizeof(WaitingNode));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed!\n");
        return NULL;
    }
    
    strcpy(newNode->userName, userName);
    newNode->next = NULL;
    return newNode;
}

// Menambahkan user ke waiting list (enqueue)
void enqueue(WaitingNode** front, WaitingNode** rear, char* userName) {
    // Cek apakah user sudah ada di queue
    if (isUserInQueue(*front, userName)) {
        printf("User %s sudah ada dalam waiting list!\n", userName);
        return;
    }
    
    WaitingNode* newNode = createWaitingNode(userName);
    if (newNode == NULL) return;
    
    if (*rear == NULL) {
        // Queue kosong
        *front = *rear = newNode;
    } else {
        // Tambahkan di belakang
        (*rear)->next = newNode;
        *rear = newNode;
    }
    
    printf("User %s berhasil ditambahkan ke waiting list.\n", userName);
}

// Mengeluarkan user dari waiting list (dequeue)
char* dequeue(WaitingNode** front, WaitingNode** rear) {
    if (*front == NULL) {
        return NULL; // Queue kosong
    }
    
    WaitingNode* temp = *front;
    char* userName = (char*)malloc(50 * sizeof(char));
    strcpy(userName, temp->userName);
    
    *front = (*front)->next;
    
    // Jika queue menjadi kosong
    if (*front == NULL) {
        *rear = NULL;
    }
    
    free(temp);
    return userName;
}

// Mengecek apakah queue kosong
int isQueueEmpty(WaitingNode* front) {
    return front == NULL;
}

// Menampilkan isi waiting list
void displayQueue(WaitingNode* front) {
    if (isQueueEmpty(front)) {
        printf("Waiting list kosong.\n");
        return;
    }
    
    printf("\n=== WAITING LIST ===\n");
    WaitingNode* current = front;
    int position = 1;
    
    while (current != NULL) {
        printf("%d. %s\n", position, current->userName);
        current = current->next;
        position++;
    }
}

// Membebaskan memory queue
void freeQueue(WaitingNode* front) {
    WaitingNode* current = front;
    while (current != NULL) {
        WaitingNode* temp = current;
        current = current->next;
        free(temp);
    }
}

// Menghitung ukuran queue
int queueSize(WaitingNode* front) {
    int size = 0;
    WaitingNode* current = front;
    
    while (current != NULL) {
        size++;
        current = current->next;
    }
    
    return size;
}

// Mengecek apakah user ada dalam queue
int isUserInQueue(WaitingNode* front, char* userName) {
    WaitingNode* current = front;
    
    while (current != NULL) {
        if (strcmp(current->userName, userName) == 0) {
            return 1; // User ditemukan
        }
        current = current->next;
    }
    
    return 0; // User tidak ditemukan
}