#include "../header/tree.h"

// Buat deklarasi variabel global
GenreNode* genreRoot = NULL;
GenreNode* fiksiNode = NULL;
GenreNode* nonFiksiNode = NULL;

void initGenreTree() {
    genreRoot = createGenre("Sistem Perpus Digital");
    fiksiNode = createGenre("Fiksi");
    nonFiksiNode = createGenre("Non-Fiksi");
    
    genreRoot->firstChild = fiksiNode;
    fiksiNode->parent = genreRoot;
    fiksiNode->nextSibling = nonFiksiNode;
    nonFiksiNode->parent = genreRoot;
}

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
    char filename[256];
    sprintf(filename, "data/books/%s/%s.txt", parent->genreName, genreName);
    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fclose(file);
    }
    saveGenreData(genreRoot);
}

GenreNode* createGenre(const char* genreName) {
    GenreNode* newNode = (GenreNode*)malloc(sizeof(GenreNode));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed\n");
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
    GenreNode* sibling = findGenre(root->nextSibling, genreName);
    if (sibling != NULL) {
        return sibling;
    }
    return findGenre(root->firstChild, genreName);
}

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

void saveGenreData(GenreNode* root) {
    FILE* file = fopen("data/statistics/genres.txt", "w");
    if (file == NULL) {
        printf("Error: Cannot open genre file for writing\n");
        return;
    }
    saveGenreDataRecursive(file, root);
    fclose(file);
}

void loadGenreData(GenreNode** root) {
    FILE* file = fopen("data/statistics/genres.txt", "r");
    if (file == NULL) {
        printf("Error: Cannot open genre file for reading\n");
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

// Modul rekursif buat penyimpanan data genre
void saveGenreDataRecursive(FILE* file, GenreNode* node) {
    if (node == NULL) return;
    // Hanya simpan genre yang bukan root dan bukan Fiksi/Non-Fiksi
    if (node->parent != NULL && node->parent->parent != NULL) {
        fprintf(file, "%s|%s\n", node->parent->genreName, node->genreName);
    }
    saveGenreDataRecursive(file, node->firstChild);
    saveGenreDataRecursive(file, node->nextSibling);
}