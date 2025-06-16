#include "../header/tree.h"

// Global variable initialization
GenreNode* genreRoot = NULL;
GenreNode* fiksiNode = NULL;
GenreNode* nonFiksiNode = NULL;

// Inisialisasi root dengan dua child utama
void initGenreTree() {
    genreRoot = createGenre("Sistem Perpus Digital");
    fiksiNode = createGenre("Fiksi");
    nonFiksiNode = createGenre("Non-Fiksi");
    
    genreRoot->firstChild = fiksiNode;
    fiksiNode->parent = genreRoot;
    fiksiNode->nextSibling = nonFiksiNode;
    nonFiksiNode->parent = genreRoot;
}

// Fungsi untuk mencari node Fiksi/Non-Fiksi
GenreNode* findMainGenre(const char* mainGenreName) {
    if (genreRoot == NULL) return NULL;
    GenreNode* current = genreRoot->firstChild;
    while (current != NULL) {
        if (strcmp(current->genreName, mainGenreName) == 0) {
            return current;
        }
        current = current->nextSibling;
    }
    return NULL;
}

// Helper rekursif untuk saveGenreData
void saveGenreDataRecursive(FILE* file, GenreNode* node) {
    if (node == NULL) return;
    // Hanya simpan genre yang bukan root dan bukan Fiksi/Non-Fiksi
    if (node->parent != NULL && node->parent->parent != NULL) {
        fprintf(file, "%s|%s\n", node->parent->genreName, node->genreName);
    }
    saveGenreDataRecursive(file, node->firstChild);
    saveGenreDataRecursive(file, node->nextSibling);
}

void saveGenreData(GenreNode* root) {
    FILE* file = fopen("data/statistics/genres.txt", "w");
    if (file == NULL) {
        printf("\t\t\t\t\t\tError: Tidak bisa membuka file\n");
        getchar();
        return;
    }
    // Simpan semua genre bertingkat (kecuali root dan Fiksi/Non-Fiksi)
    saveGenreDataRecursive(file, root);
    fclose(file);
}

// Fungsi untuk menambah genre sebagai child dari Fiksi/Non-Fiksi
void addSubGenre(GenreNode* parent, const char* genreName) {
    GenreNode* newGenre = createGenre(genreName);
    if (newGenre == NULL || parent == NULL) {
        return;
    }
    newGenre->parent = parent;
    if (parent->firstChild == NULL) {
        parent->firstChild = newGenre;
    } else {
        GenreNode* current = parent->firstChild;
        while (current->nextSibling != NULL) {
            current = current->nextSibling;
        }
        current->nextSibling = newGenre;
    }
    // Buat file genre di folder parent (fiksi/non-fiksi)
    char filename[256];
    sprintf(filename, "data/books/%s/%s.txt", parent->genreName, genreName);
    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fclose(file);
    }
    // Simpan perubahan genre ke genres.txt
    saveGenreData(genreRoot);
}

GenreNode* createGenre(const char* genreName) {
    GenreNode* newNode = (GenreNode*)malloc(sizeof(GenreNode));
    if (newNode == NULL) {
        printf("\t\t\t\t\t\tError: Gagal alokasi memori\n");
        getchar();
        return NULL;
    }

    strcpy(newNode->genreName, genreName);
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    newNode->parent = NULL;
    newNode->bookList = NULL;

    return newNode;
}

GenreNode* findGenre(GenreNode* root, const char* genreName) {
    if (root == NULL) {
        return NULL;
    }

    if (strcmp(root->genreName, genreName) == 0) {
        return root;
    }

    // Check siblings
    GenreNode* sibling = findGenre(root->nextSibling, genreName);
    if (sibling != NULL) {
        return sibling;
    }

    // Check children
    return findGenre(root->firstChild, genreName);
}

void loadGenreData(GenreNode** root) {
    FILE* file = fopen("data/statistics/genres.txt", "r");
    if (file == NULL) {
        printf("\t\t\t\t\t\tError: Tidak bisa membuka file\n");
        getchar();
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char* parentName = strtok(line, "|");
        char* genreName = strtok(NULL, "|");
        if (parentName && genreName) {
            GenreNode* parent = findMainGenre(parentName);
            if (parent) {
                // Cek apakah genre sudah ada agar tidak double
                GenreNode* check = parent->firstChild;
                int found = 0;
                while (check != NULL) {
                    if (strcmp(check->genreName, genreName) == 0) {
                        found = 1;
                        break;
                    }
                    check = check->nextSibling;
                }
                if (!found) {
                    addSubGenre(parent, genreName);
                }
            }
        }
    }
    fclose(file);
}
