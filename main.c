#include "header/menu.h"

int main() {
    initGenreTree();

    // Memuat semua data sebelum program dimulai
    loadAdminData();
    loadGenreData(&genreRoot);
    loadAllBooks();
    loadActiveTransactions();
    loadTransactionHistory();

    int choice;
    do {
        displayMainMenu();
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                handleAdminLogin();
                break;
            case 2:
                handleUserLogin();
                break;
            case 3:
                printf("Terima Kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (choice != 3);

    // Simpan semua data sebelum keluar
    saveAllBooks();
    saveActiveTransactions();
    saveTransactionHistory();
    saveGenreData(genreRoot);

    return 0;
}