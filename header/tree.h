#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "booklist.h"

typedef struct GenreNode {
    char genreName[50];
    struct GenreNode* firstChild;
    struct GenreNode* nextSibling;
    struct GenreNode* parent;
    BookNode* bookList;
} GenreNode;

// Modul-modul buat operasi tree genrenya
GenreNode* createGenre(const char* genreName);
GenreNode* findGenre(GenreNode* root, const char* genreName);
GenreNode* findMainGenre(const char* mainGenreName);
void addSubGenre(GenreNode* parent, const char* genreName);
void initGenreTree();

// Modul-modul buat penyimpanan genre
void saveGenreData(GenreNode* root);
void loadGenreData(GenreNode** root);

//Buat dipake folder lain kalo butuh
extern GenreNode* genreRoot;

#endif

