#include "../header/rekomendasi.h"

void generateRecommendations(const char* userName) {
    Stack* userStack = getUserStack(userName);
    if (userStack == NULL) {
        printf("No reading history found for user %s\n", userName);
        return;
    }

    // preference genre analisis
    GenreStats* genreStats = analyzeUserGenrePreference(userStack);
    if (genreStats == NULL) {
        printf("No genre preferences found\n");
        return;
    }

    // ngambil buku terbanyak dibaca
    char* mostReadGenre = getMostReadGenre(userStack);
    if (mostReadGenre == NULL) {
        printf("No genre preferences found\n");
        return;
    }

    // Display rekomendasi dari buku
    printf("\nRecommendations for user %s:\n", userName);
    printf("----------------------------------------\n");
    printf("Based on your reading history, you might enjoy these books:\n\n");

    // Display Buku Dari Genre Terbanyak
    GenreNode* genre = findGenre(genreRoot, mostReadGenre);
    if (genre != NULL) {
        BookNode* current = genre->bookList;
        int count = 0;
        while (current != NULL && count < 5) {
            printf("%d. %s\n", count + 1, current->judul);
            printf("   Author: %s\n", current->info.penulis);
            printf("   Publisher: %s\n", current->info.penerbit);
            printf("   Year: %d\n", current->info.tahun_terbit);
            printf("----------------------------------------\n");
            current = current->next;
            count++;
        }
    }

    // Buat Free memory
    GenreStats* current = genreStats;
    while (current != NULL) {
        GenreStats* temp = current;
        current = current->next;
        free(temp);
    }
}

void displayRecommendationsForUser(const char* userName) {
    generateRecommendations(userName);
}

void displayTopBooksByViewCount() {
    displayTopBooks();
}

GenreStats* analyzeUserGenrePreference(Stack* riwayat) {
    if (riwayat == NULL || isStackEmpty(riwayat)) {
        return NULL;
    }

    GenreStats* stats = NULL;
    RiwayatNode* current = riwayat->top;

    while (current != NULL) {
        // Find or create genre stat
        GenreStats* currentStat = stats;
        GenreStats* prevStat = NULL;
        bool found = false;

        while (currentStat != NULL) {
            if (strcmp(currentStat->genreName, current->genre) == 0) {
                currentStat->count++;
                found = true;
                break;
            }
            prevStat = currentStat;
            currentStat = currentStat->next;
        }

        if (!found) {
            // buat genre baru
            GenreStats* newStat = (GenreStats*)malloc(sizeof(GenreStats));
            if (newStat == NULL) {
                printf("Error: Memory allocation failed\n");
                continue;
            }

            strcpy(newStat->genreName, current->genre);
            newStat->count = 1;
            newStat->next = NULL;

            if (prevStat == NULL) {
                stats = newStat;
            } else {
                prevStat->next = newStat;
            }
        }

        current = current->next;
    }

    return stats;
}

char* getMostReadGenre(Stack* riwayat) {
    GenreStats* stats = analyzeUserGenrePreference(riwayat);
    if (stats == NULL) {
        return NULL;
    }

    GenreStats* current = stats;
    GenreStats* mostRead = stats;
    int maxCount = stats->count;

    while (current != NULL) {
        if (current->count > maxCount) {
            maxCount = current->count;
            mostRead = current;
        }
        current = current->next;
    }

    char* result = strdup(mostRead->genreName);

    // Buat Free memory
    current = stats;
    while (current != NULL) {
        GenreStats* temp = current;
        current = current->next;
        free(temp);
    }

    return result;
}
