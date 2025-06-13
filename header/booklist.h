#ifndef BOOKLIST_H
#define BOOKLIST_H

typedef struct BookNode {
    char judul[100];
    Spesifikasi info;
    int viewCount;
    int stok;                     // Jumlah stok buku
    WaitingNode* front;              // Front of the queue
    WaitingNode* rear;               // Rear of the queue
    struct BookNode* next;
} BookNode;


#endif