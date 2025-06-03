#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct GenreNode {
    char genreName[50];
    struct GenreNode* fs;
    struct GenreNode* nb;
    struct GenreNode* pr;
    struct BookNode* bookList;
} GenreNode;

GenreNode* createGenreNode(const char* name);
GenreNode* insertSubGenre(GenreNode* pr, const char* subGenreName);
void traverseGenreTree(GenreNode* root, int depth);
GenreNode* findGenre(GenreNode* root, const char* name);
void deleteGenre(GenreNode* root, const char* targetName);
GenreNode* loadGenreTreeFromFile(const char* filename);
void saveGenreTree(GenreNode* root, const char* filename);

#endif
