#include "../header/booklist.h"

BookNode* createBook(const char* judul, const char* penulis, const char* penerbit, 
                    int tahun, const char* kode, int stok, const char* genre) {
    BookNode* newBook = (BookNode*)malloc(sizeof(BookNode));
    if (newBook == NULL) {
        printf("\t\t\t\t\t\tError: Gagal alokasi memori\n");
        return NULL;
    }

    strcpy(newBook->judul, judul);
    strcpy(newBook->info.penulis, penulis);
    strcpy(newBook->info.penerbit, penerbit);
    strcpy(newBook->info.kode_buku, kode);
    strcpy(newBook->genre, genre);
    newBook->info.tahun_terbit = tahun;
    newBook->viewCount = 0;
    newBook->stok = stok;
    newBook->next = NULL;
    
    // Inisialisasi waiting list
    newBook->front = NULL;
    newBook->rear = NULL;

    return newBook;
}

void addBookToGenre(const char* genreName, BookNode* book) {
    GenreNode* genre = findGenre(genreRoot, genreName);
    if (genre == NULL) {
        printf("\t\t\t\t\t\tError: Genre tidak ditemukan\n");
        getchar();
        return;
    }

    // Add book to genre's book list
    if (genre->bookList == NULL) {
        genre->bookList = book;
    } else {
        BookNode* current = genre->bookList;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = book;
    }

    // Save all books to file
    saveAllBooksToFile(genreName);
}

void removeBookFromGenre(const char* genreName, const char* kodeBuku) {
    GenreNode* genre = findGenre(genreRoot, genreName);
    if (genre == NULL) {
        printf("\t\t\t\t\t\tError: Genre tidak ditemukan\n");
        getchar();
        return;
    }
    
    // Cek apakah buku sedang dipinjam
    TransactionNode* currentTrans = activeTransactionList;
    while (currentTrans != NULL) {
        if (strcmp(currentTrans->data.kodeBuku, kodeBuku) == 0) {
            printf("\t\t\t\t\t\tError: Tidak bisa menghapus buku, buku sedang dipinjam\n");
            getchar();
            return;
        }
        currentTrans = currentTrans->next;
    }

    // Cari dan hapus buku
    BookNode* current = genre->bookList;
    BookNode* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->info.kode_buku, kodeBuku) == 0) {
            // Cek apakah ada user di waiting list
            if (current->front != NULL) {
                printf("\t\t\t\t\t\tError: Tidak bisa menghapus buku, ada user di waiting list\n");
                getchar();
                return;
            }
            
            if (prev == NULL) {
                genre->bookList = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            // Update file
            saveAllBooksToFile(genre->genreName);
            printf("\t\t\t\t\t\tBuku berhasil dihapus\n");
            getchar();
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("\t\t\t\t\t\tError: Buku tidak ditemukan didalam genre\n");
    getchar();
}

void displayBooksInGenre(const char* genreName) {
    GenreNode* genre = findGenre(genreRoot, genreName);
    if (genre == NULL) {
        printf("\t\t\t\t\t\tError: Genre tidak ditemukan\n");
        getchar();
        return;
    }    printf("\t\t\t\t\t\tBooks in genre '%s':\n", genreName);
    printf("\t\t\t\t\t\t----------------------------------------\n");
    
    BookNode* current = genre->bookList;
    while (current != NULL) {        printf("\t\t\t\t\t\tTitle: %s\n", current->judul);
        printf("\t\t\t\t\t\tAuthor: %s\n", current->info.penulis);
        printf("\t\t\t\t\t\tPublisher: %s\n", current->info.penerbit);
        printf("\t\t\t\t\t\tYear: %d\n", current->info.tahun_terbit);
        printf("\t\t\t\t\t\tCode: %s\n", current->info.kode_buku);
        printf("\t\t\t\t\t\tStock: %d\n", current->stok);
        printf("\t\t\t\t\t\tViews: %d\n", current->viewCount);
        printf("\t\t\t\t\t\t----------------------------------------\n");
        current = current->next;
    }
}

// Helper untuk mendapatkan parent genre (Fiksi/Non-Fiksi) dari GenreNode
const char* getParentGenreFolder(GenreNode* genre) {
    if (genre == NULL || genre->parent == NULL) return NULL;
    return genre->parent->genreName;
}

void saveAllBooksToFile(const char* genreName) {
    GenreNode* genre = findGenre(genreRoot, genreName);
    if (genre == NULL) return;
    const char* parentFolder = getParentGenreFolder(genre);
    if (parentFolder == NULL) return;
    
    // Simpan data buku
    char filename[256];
    sprintf(filename, "data/books/%s/%s.txt", parentFolder, genreName);
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("\t\t\t\t\t\tError: Tidak bisa membuka file\n");
        getchar();
        return;
    }
    
    BookNode* current = genre->bookList;
    while (current != NULL) {
        fprintf(file, "%s|%s|%s|%d|%s|%d|%d|%s\n",
                current->judul,
                current->info.penulis,
                current->info.penerbit,
                current->info.tahun_terbit,
                current->info.kode_buku,
                current->stok,
                current->viewCount,
                current->genre);
        current = current->next;
    }
    fclose(file);
}

void loadBooksFromFile(const char* parentFolder, const char* genreName) {    
    char filename[256];
    sprintf(filename, "data/books/%s/%s.txt", parentFolder, genreName);
    FILE* file = fopen(filename, "r");
    if (file == NULL) return;
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char judul[100], penulis[50], penerbit[50], kode[20], genre[50];
        int tahun, stok, viewCount;
        
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%d|%d|%[^\n]",
               judul, penulis, penerbit, &tahun, kode, &stok, &viewCount, genre);
        
        BookNode* book = createBook(judul, penulis, penerbit, tahun, kode, stok, genre);
        if (book != NULL) {
            book->viewCount = viewCount;
            addBookToGenre(genre, book);
            loadWaitingList(book);
        }
    }
    fclose(file);
}

void displayAllBooks() {
    if (genreRoot == NULL) {
        printf("\t\t\t\t\t\tTidak ada genre tersedia\n");
        getchar();
        return;
    }
    GenreNode* mainGenre = genreRoot->firstChild;
    while (mainGenre != NULL) {
        printf("\t\t\t\t\t\t=== %s ===\n", mainGenre->genreName);
        GenreNode* genre = mainGenre->firstChild;
        while (genre != NULL) {
            displayBooksInGenre(genre->genreName);
            genre = genre->nextSibling;
        }
        mainGenre = mainGenre->nextSibling;
    }
}

void updateBookStock(const char* kodeBuku, int newStock) {
    if (genreRoot == NULL) return;
    GenreNode* mainGenre = genreRoot->firstChild;
    while (mainGenre != NULL) {
        GenreNode* genre = mainGenre->firstChild;
        while (genre != NULL) {
            BookNode* currentBook = genre->bookList;
            while (currentBook != NULL) {
                if (strcmp(currentBook->info.kode_buku, kodeBuku) == 0) {
                    currentBook->stok = newStock;
                    saveAllBooksToFile(genre->genreName);
                    return;
                }
                currentBook = currentBook->next;
            }
            genre = genre->nextSibling;
        }
        mainGenre = mainGenre->nextSibling;
    }
}

BookNode* findBook(const char* kodeBuku) {
    if (genreRoot == NULL) return NULL;
    GenreNode* mainGenre = genreRoot->firstChild;
    while (mainGenre != NULL) {
        GenreNode* genre = mainGenre->firstChild;
        while (genre != NULL) {
            BookNode* currentBook = genre->bookList;
            while (currentBook != NULL) {
                if (strcmp(currentBook->info.kode_buku, kodeBuku) == 0) {
                    return currentBook;
                }
                currentBook = currentBook->next;
            }
            genre = genre->nextSibling;
        }
        mainGenre = mainGenre->nextSibling;
    }
    return NULL;
}

bool isBookAvailable(const char* kodeBuku) {
    BookNode* book = findBook(kodeBuku);
    return (book != NULL && book->stok > 0);
}

void saveAllBooks() {
    if (genreRoot == NULL) return;
    GenreNode* mainGenre = genreRoot->firstChild;
    while (mainGenre != NULL) {
        GenreNode* genre = mainGenre->firstChild;
        while (genre != NULL) {
            saveAllBooksToFile(genre->genreName);
            genre = genre->nextSibling;
        }
        mainGenre = mainGenre->nextSibling;
    }
}

void incrementViewCount(const char* kodeBuku) {
    BookNode* book = findBook(kodeBuku);
    if (book != NULL) {
        book->viewCount++;
        saveAllBooksToFile(book->genre);
    }
}

void displayTopBooks() {
    if (genreRoot == NULL) {
        printf("\t\t\t\t\t\tTidak ada buku yang tersedia\n");
        getchar();
        return;
    }
    BookNode* allBooks[1000];
    int bookCount = 0;
    GenreNode* mainGenre = genreRoot->firstChild;
    while (mainGenre != NULL) {
        GenreNode* genre = mainGenre->firstChild;
        while (genre != NULL) {
            BookNode* currentBook = genre->bookList;
            while (currentBook != NULL) {
                allBooks[bookCount++] = currentBook;
                currentBook = currentBook->next;
            }
            genre = genre->nextSibling;
        }
        mainGenre = mainGenre->nextSibling;
    }
    // Urutkan buku berdasarkan View Count (bubble sort)
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = 0; j < bookCount - i - 1; j++) {
            if (allBooks[j]->viewCount < allBooks[j + 1]->viewCount) {
                BookNode* temp = allBooks[j];
                allBooks[j] = allBooks[j + 1];
                allBooks[j + 1] = temp;
            }
        }
    }    printf("\t\t\t\t\t\tBuku teratas:\n");
    printf("\t\t\t\t\t\t----------------------------------------\n");
    for (int i = 0; i < bookCount && i < 10; i++) {
        printf("\t\t\t\t\t\t%d. %s\n", i + 1, allBooks[i]->judul);
        printf("\t\t\t\t\t\t   Views: %d\n", allBooks[i]->viewCount);
        printf("\t\t\t\t\t\t   Author: %s\n", allBooks[i]->info.penulis);
        printf("\t\t\t\t\t\t----------------------------------------\n");
    }
}

void loadAllBooks() {
    if (genreRoot == NULL) {
        return;
    }
    GenreNode* mainGenre = genreRoot->firstChild;
    while (mainGenre != NULL) {
        GenreNode* genre = mainGenre->firstChild;
        while (genre != NULL) {
            loadBooksFromFile(mainGenre->genreName, genre->genreName);
            genre = genre->nextSibling;
        }
        mainGenre = mainGenre->nextSibling;
    }
}