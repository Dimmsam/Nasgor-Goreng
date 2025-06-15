#include "../header/transaksi.h"

// Inisialisasi variabel global untuk transaksi
TransactionNode* activeTransactionList = NULL;
TransactionNode* historyTransactionList = NULL;

char* generateTransactionId() {
    static char id[20];
    static int counter = 1;
    sprintf(id, "T%03d", counter++);
    return id;
}

void addTransaction(const char* userName, const char* userRealName, 
                   const char* kodeBuku, const char* judulBuku, const char* status) {
    TransactionNode* newNode = (TransactionNode*)malloc(sizeof(TransactionNode));
    if (newNode == NULL) {
        printf("Error: Gagal alokasi memori\n");
        return;
    }

    strcpy(newNode->data.transactionId, generateTransactionId());
    strcpy(newNode->data.userName, userName);
    strcpy(newNode->data.userRealName, userRealName);
    strcpy(newNode->data.kodeBuku, kodeBuku);
    strcpy(newNode->data.judulBuku, judulBuku);
    strcpy(newNode->data.status, status);
    newNode->next = NULL;

    // Tambahkan transaksi ke daftar aktif atau histori
    if (strcmp(status, "dipinjam") == 0) {
        if (activeTransactionList == NULL) {
            activeTransactionList = newNode;
        } else {
            TransactionNode* current = activeTransactionList;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
        saveActiveTransactions();
    } else {
        if (historyTransactionList == NULL) {
            historyTransactionList = newNode;
        } else {
            TransactionNode* current = historyTransactionList;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
        saveTransactionHistory();
    }
}

bool updateTransactionStatus(const char* transactionId, const char* newStatus) {
    TransactionNode* current = activeTransactionList;
    TransactionNode* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->data.transactionId, transactionId) == 0) {
            // Pindahkan transaksi ke histori jika status diubah menjadi "dikembalikan"
            if (strcmp(newStatus, "dikembalikan") == 0) {
                // Hapus dari daftar aktif
                if (prev == NULL) {
                    activeTransactionList = current->next;
                } else {
                    prev->next = current->next;
                }

                // Tambahkan ke daftar histori
                current->next = NULL;
                if (historyTransactionList == NULL) {
                    historyTransactionList = current;
                } else {
                    TransactionNode* historyCurrent = historyTransactionList;
                    while (historyCurrent->next != NULL) {
                        historyCurrent = historyCurrent->next;
                    }
                    historyCurrent->next = current;
                }

                strcpy(current->data.status, newStatus);
                saveActiveTransactions();
                saveTransactionHistory();
                return true;
            }
            return false;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

void displayUserTransactions(const char* userName) {
    printf("\nTransaksi untuk user %s:\n", userName);
    printf("----------------------------------------\n");
    
    // Check Transaksi aktif
    printf("Transaksi aktif untuk user %s:\n", userName);
    printf("----------------------------------------\n");
    TransactionNode* current = activeTransactionList;
    while (current != NULL) {
        if (strcmp(current->data.userName, userName) == 0) {
            printf("ID: %s\n", current->data.transactionId);
            printf("Book: %s (%s)\n", current->data.judulBuku, current->data.kodeBuku);
            printf("Status: %s\n", current->data.status);
            printf("----------------------------------------\n");
        }
        current = current->next;
    }

    // Cek Histori
    printf("\nHistori transaksi untuk user %s:\n", userName);
    printf("----------------------------------------\n");
    current = historyTransactionList;
    while (current != NULL) {
        if (strcmp(current->data.userName, userName) == 0) {
            printf("ID: %s\n", current->data.transactionId);
            printf("Book: %s (%s)\n", current->data.judulBuku, current->data.kodeBuku);
            printf("Status: %s\n", current->data.status);
            printf("----------------------------------------\n");
        }
        current = current->next;
    }
}

void saveActiveTransactions() {
    FILE* file = fopen("data/transactions/active.txt", "w");
    if (file == NULL) {
        printf("Error: Tidak bisa membuka file\n");
        return;
    }

    TransactionNode* current = activeTransactionList;
    while (current != NULL) {
        fprintf(file, "%s|%s|%s|%s|%s|%s\n",
                current->data.transactionId,
                current->data.userName,
                current->data.userRealName,
                current->data.kodeBuku,
                current->data.judulBuku,
                current->data.status);
        current = current->next;
    }

    fclose(file);
}

void saveTransactionHistory() {
    FILE* file = fopen("data/transactions/history.txt", "w");
    if (file == NULL) {
        printf("Error: Tidak bisa membuka file\n");
        return;
    }

    TransactionNode* current = historyTransactionList;
    while (current != NULL) {
        fprintf(file, "%s|%s|%s|%s|%s|%s\n",
                current->data.transactionId,
                current->data.userName,
                current->data.userRealName,
                current->data.kodeBuku,
                current->data.judulBuku,
                current->data.status);
        current = current->next;
    }

    fclose(file);
}

void loadActiveTransactions() {
    FILE* file = fopen("data/transactions/active.txt", "r");
    if (file == NULL) {
        printf("Error: Tidak bisa membuka file\n");
        return;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        
        char* id = strtok(line, "|");
        char* userName = strtok(NULL, "|");
        char* userRealName = strtok(NULL, "|");
        char* kodeBuku = strtok(NULL, "|");
        char* judulBuku = strtok(NULL, "|");
        char* status = strtok(NULL, "|");
        
        if (id && userName && userRealName && kodeBuku && judulBuku && status) {
            addTransaction(userName, userRealName, kodeBuku, judulBuku, status);
        }
    }

    fclose(file);
}

void loadTransactionHistory() {
    FILE* file = fopen("data/transactions/history.txt", "r");
    if (file == NULL) {
        printf("Error: Tidak bisa membuka file\n");
        return;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        
        char* id = strtok(line, "|");
        char* userName = strtok(NULL, "|");
        char* userRealName = strtok(NULL, "|");
        char* kodeBuku = strtok(NULL, "|");
        char* judulBuku = strtok(NULL, "|");
        char* status = strtok(NULL, "|");
        
        if (id && userName && userRealName && kodeBuku && judulBuku && status) {
            addTransaction(userName, userRealName, kodeBuku, judulBuku, status);
        }
    }

    fclose(file);
}

bool processBookBorrow(const char* userName, const char* userRealName, const char* kodeBuku) {
    BookNode* book = findBook(kodeBuku);
    if (book == NULL) {
        printf("Buku tidak ditemukan\n");
        return false;
    }

    // Cek apakah user sudah meminjam buku ini
    TransactionNode* current = activeTransactionList;
    while (current != NULL) {
        if (strcmp(current->data.userName, userName) == 0 && 
            strcmp(current->data.kodeBuku, kodeBuku) == 0) {
            printf("Anda sudah meminjam buku ini\n");
            return false;
        }
        current = current->next;
    }

    if (book->stok > 0) {
        // Proses peminjaman normal
        addTransaction(userName, userRealName, kodeBuku, book->judul, "dipinjam");
        book->stok--;
        incrementViewCount(kodeBuku);
        addBookToUserHistory(userName, book->judul, book->genre);
        return true;
    } else {
        // Cek apakah user sudah ada di waiting list
        if (isUserInWaitingList(book, userName)) {
            printf("Anda sudah terdaftar di waiting list untuk buku ini\n");
            return false;
        }
        
        // Tambahkan ke waiting list
        enqueueWaitingList(book, userName);
        saveWaitingList(book);
        printf("Buku sedang dipinjam. Anda telah ditambahkan ke waiting list\n");
        return false;
    }
}

bool processBookReturn(const char* transactionId) {
    TransactionNode* current = activeTransactionList;
    TransactionNode* prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->data.transactionId, transactionId) == 0) {
            // Update status transaksi
            strcpy(current->data.status, "dikembalikan");
            
            // Pindahkan ke history
            if (prev == NULL) {
                activeTransactionList = current->next;
            } else {
                prev->next = current->next;
            }
            current->next = historyTransactionList;
            historyTransactionList = current;
            
            // Update stok buku
            BookNode* book = findBook(current->data.kodeBuku);
            if (book != NULL) {
                book->stok++;
                // Proses waiting list untuk buku ini
                processWaitingList(book);
            }
            
            // Simpan perubahan
            saveActiveTransactions();
            saveTransactionHistory();
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}