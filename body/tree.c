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

void displayGenreTree(GenreNode* root) {
    if (root == NULL) {
        printf("No genres available\n");
        return;
    }
    printf("\nGenre Tree:\n");
    printf("----------------------------------------\n");
    displayGenreTreeRecursive(root, 0);
    printf("----------------------------------------\n");
}

void displayAllGenres(GenreNode* root) {
    if (root == NULL) {
        printf("No genres available\n");
        return;
    }
    printf("\nAll Genres:\n");
    printf("----------------------------------------\n");
    GenreNode* mainGenre = root->firstChild;
    while (mainGenre != NULL) {
        printf("%s:\n", mainGenre->genreName);
        GenreNode* genre = mainGenre->firstChild;
        while (genre != NULL) {
            printf("  - %s\n", genre->genreName);
            genre = genre->nextSibling;
        }
        mainGenre = mainGenre->nextSibling;
    }
    printf("----------------------------------------\n");
}

// Modul rekursif biar sedikit lebih simpel
void displayGenreTreeRecursive(GenreNode* node, int level) {
    if (node == NULL) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("- %s\n", node->genreName);
    displayGenreTreeRecursive(node->firstChild, level + 1);
    displayGenreTreeRecursive(node->nextSibling, level);
}