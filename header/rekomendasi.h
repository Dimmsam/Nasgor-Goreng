#ifndef REKOMENDASI_H
#define REKOMENDASI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"
#include "tree.h"
#include "booklist.h"
#include "queue.h"

// Struct untuk statistik genre
typedef struct GenreStats {
    char genreName[50];
    int count;
    struct GenreStats* next;
} GenreStats;

// Recommendation Functions
void generateRecommendations(const char* userName);
void displayRecommendationsForUser(const char* userName);
void displayTopBooksByViewCount();

// Genre Analysis
GenreStats* analyzeUserGenrePreference(Stack* riwayat);
char* getMostReadGenre(Stack* riwayat);

#endif // REKOMENDASI_H