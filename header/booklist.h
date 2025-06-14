#ifndef BOOKLIST_H
#define BOOKLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "queue.h"
#include "transaksi.h"
#include "tree.h"

// Struct diambil dari queue
struct WaitingNode;
typedef struct WaitingNode WaitingNode;

// Struct untuk spesifikasi buku
typedef struct Spesifikasi {
    char penulis[100];
    char penerbit[100];
    int tahun_terbit;
    char kode_buku[20];
} Spesifikasi;

// Struct untuk node Buku (Linked List)
typedef struct BookNode {
    char judul[100];
    Spesifikasi info;
    int viewCount;
    int stok;
    char genre[50];
    WaitingNode* front;
    WaitingNode* rear;
    struct BookNode* next;
} BookNode;

// Modul modul operasi pada buku
BookNode* createBook(const char* judul, const char* penulis, const char* penerbit, 
                    int tahun, const char* kode, int stok, const char* genre);
void addBookToGenre(const char* genreName, BookNode* book);
void removeBookFromGenre(const char* genreName, const char* kodeBuku);

// Modul-modul untuk menampilkan buku
void displayBooksInGenre(const char* genreName);
void displayAllBooks();

// Modul-modul penyimpanan buku
void saveAllBooksToFile(const char* genreName);

#endif