#include "../header/queue.h"

void enqueueWaitingList(BookNode* book, const char* userName) {
    if (book == NULL) return;

    // Cek apakah user sudah ada di waiting list
    if (isUserInWaitingList(book, userName)) {
        return;
    }

    WaitingNode* newNode = (WaitingNode*)malloc(sizeof(WaitingNode));
    if (newNode == NULL) {
        printf("\t\t\t\t\t\tError: Gagal alokasi memori\n");
        getchar();
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

void saveWaitingList(BookNode* book) {
    if (book == NULL) return;

    char filename[100];
    sprintf(filename, "data/books/waiting/%s_waiting.txt", book->info.kode_buku);
    
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("\t\t\t\t\t\tError: Gagal membuka file untuk dibaca\n");
        getchar();
        return;
    }

    WaitingNode* current = book->front;
    while (current != NULL) {
        fprintf(file, "%s\n", current->userName);
        current = current->next;
    }

    fclose(file);
}

void loadWaitingList(BookNode* book) {
    if (book == NULL) return;

    char filename[100];
    sprintf(filename, "data/books/waiting/%s_waiting.txt", book->info.kode_buku);
    
    FILE* file = fopen(filename, "r");
    if (file == NULL) return;

    char userName[50];
    while (fscanf(file, "%s", userName) == 1) {
        WaitingNode* newNode = (WaitingNode*)malloc(sizeof(WaitingNode));
        if (newNode == NULL) continue;

        strcpy(newNode->userName, userName);
        newNode->next = NULL;

        if (book->rear == NULL) {
            book->front = book->rear = newNode;
        } else {
            book->rear->next = newNode;
            book->rear = newNode;
        }
    }

    fclose(file);
}

void processWaitingList(BookNode* book) {
    if (book == NULL || book->front == NULL) return;

    WaitingNode* temp = book->front;
    // Proses peminjaman untuk user pertama
    addTransaction(temp->userName, book->info.kode_buku, book->judul, "dipinjam");
    book->stok--;
    incrementViewCount(book->info.kode_buku);
     // Tambahkan ke history user
    addBookToUserHistory(temp->userName, book->judul, book->genre);
    // Dequeue user pertama
    dequeueWaitingList(book);
}

bool isUserInWaitingList(BookNode* book, const char* userName) {
    if (book == NULL || book->front == NULL) return false;

    WaitingNode* current = book->front;
    while (current != NULL) {
        if (strcmp(current->userName, userName) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}
