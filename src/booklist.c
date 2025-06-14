#include "../header/booklist.h"

BookNode* createBook(const char* judul, const char* penulis, const char* penerbit, 
                    int tahun, const char* kode, int stok, const char* genre) {
    BookNode* newBook = (BookNode*)malloc(sizeof(BookNode));
    if (newBook == NULL) {
        printf("Error: Memory allocation failed\n");
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
        printf("Error: Genre not found\n");
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
        printf("Error: Genre not found\n");
        return;
    }
    TransactionNode* currentTrans = activeTransactionList;
    while (currentTrans != NULL) {
        if (strcmp(currentTrans->data.kodeBuku, kodeBuku) == 0) {
            printf("Error: Cannot remove book. It is currently borrowed\n");
            return;
        }
        currentTrans = currentTrans->next;
    }

    BookNode* current = genre->bookList;
    BookNode* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->info.kode_buku, kodeBuku) == 0) {
            if (current->front != NULL) {
                printf("Error: Cannot remove book. There are users in the waiting list\n");
                return;
            }
            
            if (prev == NULL) {
                genre->bookList = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            saveAllBooksToFile(genre->genreName);
            printf("Book successfully removed\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Error: Book not found in genre\n");
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
        printf("Error: Cannot open book file for writing\n");
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
        printf("Error: Genre not found\n");
        return;
    }

    printf("\nBooks in genre '%s':\n", genreName);
    printf("----------------------------------------\n");
    
    BookNode* current = genre->bookList;
    while (current != NULL) {
        printf("Title: %s\n", current->judul);
        printf("Author: %s\n", current->info.penulis);
        printf("Publisher: %s\n", current->info.penerbit);
        printf("Year: %d\n", current->info.tahun_terbit);
        printf("Code: %s\n", current->info.kode_buku);
        printf("Stock: %d\n", current->stok);
        printf("Views: %d\n", current->viewCount);
        printf("----------------------------------------\n");
        current = current->next;
    }
}

void displayAllBooks() {
    if (genreRoot == NULL) {
        printf("No genres available\n");
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