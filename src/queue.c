#include "../header/queue.h"

void enqueueWaitingList(BookNode* book, const char* userName) {
    if (book == NULL) return;

    // Cek apakah user sudah ada di waiting list
    if (isUserInWaitingList(book, userName)) {
        return;
    }

    WaitingNode* newNode = (WaitingNode*)malloc(sizeof(WaitingNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    strcpy(newNode->userName, userName);
    newNode->next = NULL;

    if (book->rear == NULL) {
        book->front = book->rear = newNode;
    } else {
        book->rear->next = newNode;
        book->rear = newNode;
    }
}

void dequeueWaitingList(BookNode* book) {
    if (book == NULL || book->front == NULL) return;

    WaitingNode* temp = book->front;
    book->front = book->front->next;

    if (book->front == NULL) {
        book->rear = NULL;
    }

    free(temp);
    saveWaitingList(book);
}

bool isWaitingListEmpty(BookNode* book) {
    return (book == NULL || book->front == NULL);
}