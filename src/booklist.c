#include "../header/booklist.h"

BookNode* createBook(const char* judul, const char* penulis, const char* penerbit, 
                    int tahun, const char* kode, int stok, const char* genre) {
    BookNode* newBook = (BookNode*)malloc(sizeof(BookNode));
    if (newBook == NULL) {
        printf("Error: Alokasi memori gagal\n");
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

    newBook->front = NULL;
    newBook->rear = NULL;

    return newBook;
}


void addBookToGenre(const char* genreName, BookNode* book) {
    GenreNode* genre = findGenre(genreRoot, genreName);
    if (genre == NULL) {
        printf("Error: Genre tidak ditemukan\n");
        return;
    }
    if (genre->bookList == NULL) {
        genre->bookList = book;
    } else {
        BookNode* current = genre->bookList;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = book;
    }
    saveAllBooksToFile(genreName);
}

void removeBookFromGenre(const char* genreName, const char* kodeBuku) {
    GenreNode* genre = findGenre(genreRoot, genreName);
    if (genre == NULL) {
        printf("Error: Genre tidak ditemukan\n");
        return;
    }
    TransactionNode* currentTrans = activeTransactionList;
    while (currentTrans != NULL) {
        if (strcmp(currentTrans->data.kodeBuku, kodeBuku) == 0) {
            printf("Error: Tidak dapat menghapus buku. Buku sedang dipinjam\n");
            return;
        }
        currentTrans = currentTrans->next;
    }

    BookNode* current = genre->bookList;
    BookNode* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->info.kode_buku, kodeBuku) == 0) {
            if (current->front != NULL) {
                printf("Error: Tidak dapat menghapus buku. Terdapat pengguna dalam waiting list\n");
                return;
            }
            
            if (prev == NULL) {
                genre->bookList = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            saveAllBooksToFile(genre->genreName);
            printf("Buku Berhasil Dihapus\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Error: Buku Tidak Ditemukan\n");
}

void saveAllBooksToFile(const char* genreName) {
    GenreNode* genre = findGenre(genreRoot, genreName);
    if (genre == NULL) return;
    const char* parentFolder = getParentGenreFolder(genre);
    if (parentFolder == NULL) return;
    char filename[256];
    sprintf(filename, "data/books/%s/%s.txt", parentFolder, genreName);
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file untuk menyimpan\n");
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

// Modul buat nyari parent
const char* getParentGenreFolder(GenreNode* genre) {
    if (genre == NULL || genre->parent == NULL) return NULL;
    return genre->parent->genreName;
}

void displayBooksInGenre(const char* genreName) {
    GenreNode* genre = findGenre(genreRoot, genreName);
    if (genre == NULL) {
        printf("Error: Genre Tidak Ditemukan\n");
        return;
    }

    printf("\nBuku di Genre '%s':\n", genreName);
    printf("----------------------------------------\n");
    
    BookNode* current = genre->bookList;
    while (current != NULL) {
        printf("Judul: %s\n", current->judul);
        printf("Penulis: %s\n", current->info.penulis);
        printf("Penerbit: %s\n", current->info.penerbit);
        printf("Tahun: %d\n", current->info.tahun_terbit);
        printf("Kode Buku: %s\n", current->info.kode_buku);
        printf("Stok: %d\n", current->stok);
        printf("Jumlah View: %d\n", current->viewCount);
        printf("----------------------------------------\n");
        current = current->next;
    }
}

void displayAllBooks() {
    if (genreRoot == NULL) {
        printf("Genre Belum Dibuat\n");
        return;
    }
    GenreNode* mainGenre = genreRoot->firstChild;
    while (mainGenre != NULL) {
        printf("\n=== %s ===\n", mainGenre->genreName);
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
        printf("Tidak ada Buku\n");
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
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = 0; j < bookCount - i - 1; j++) {
            if (allBooks[j]->viewCount < allBooks[j + 1]->viewCount) {
                BookNode* temp = allBooks[j];
                allBooks[j] = allBooks[j + 1];
                allBooks[j + 1] = temp;
            }
        }
    }
    printf("\nBuku yang Paling Sering Dilihat:\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < bookCount && i < 10; i++) {
        printf("%d. %s\n", i + 1, allBooks[i]->judul);
        printf("   Jumlah View: %d\n", allBooks[i]->viewCount);
        printf("   Penulis: %s\n", allBooks[i]->info.penulis);
        printf("----------------------------------------\n");
    }
}
