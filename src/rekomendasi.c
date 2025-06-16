#include "../header/rekomendasi.h"

void generateRecommendations(const char* userName) {
    Stack* userStack = getUserStack(userName);
    if (userStack == NULL) {
        printf("\t\t\t\t\t\tTidak ditemukan riwayat bacaan untuk user %s\n", userName);
        return;
    }

    // preference genre analisis
    GenreStats* genreStats = analyzeUserGenrePreference(userStack);
    if (genreStats == NULL) {
        printf("\t\t\t\t\t\tTidak ditemukan preferensi genre yang mendukung\n");
        return;
    }

    // ngambil buku terbanyak dibaca
    char* mostReadGenre = getMostReadGenre(userStack);
    if (mostReadGenre == NULL) {
        printf("\t\t\t\t\t\tTidak ditemukan preferensi genre yang mendukung\n");
        return;
    }

    // Display rekomendasi dari buku
    printf("\t\t\t\t\t\tRekomendasi untuk User %s:\n", userName);
    printf("\t\t\t\t\t\t----------------------------------------\n");
    printf("\t\t\t\t\t\tBerdasarkan riwayat bacaan yang kamu baca, kamu mungkin suka:\n\n");

    // Display Buku Dari Genre Terbanyak
    GenreNode* genre = findGenre(genreRoot, mostReadGenre);
    if (genre != NULL) {
        BookNode* current = genre->bookList;
        int count = 0;
        while (current != NULL && count < 5) {
            printf("\t\t\t\t\t\t%d. %s\n", count + 1, current->judul);
            printf("\t\t\t\t\t\t   Penulis: %s\n", current->info.penulis);
            printf("\t\t\t\t\t\t   Penerbit: %s\n", current->info.penerbit);
            printf("\t\t\t\t\t\t   Tahun Terbit: %d\n", current->info.tahun_terbit);
            printf("\t\t\t\t\t\t----------------------------------------\n");
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
                printf("\t\t\t\t\t\tError: Gagal alokasi memori\n");
                getchar();
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
