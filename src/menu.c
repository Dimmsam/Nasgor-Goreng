#include "../header/menu.h"

// Inisialisasi variabel global
bool isAdminLoggedIn = false;
bool isUserLoggedIn = false;
char currentUserName[50];
char currentUserRealName[50];

void displayMainMenu() {
    printf("\n=== Sistem Perpustakaan Digital ===\n");
    printf("1. Login sebagai Admin\n");
    printf("2. Login sebagai User\n");
    printf("3. Keluar\n");
    printf("Masukkan pilihanmu: ");
}

void displayAdminMenu() {
    printf("\n=== Menu Admin ===\n");
    printf("Masukkan pilihanmu: ");
}

void displayUserMenu() {
    printf("\n=== Menu User ===\n");
    printf("1. Lihat Transaksi User\n");
    printf("2. Logout\n");
    printf("Masukkan pilihanmu: ");
}

void handleAdminLogin() {
    char username[50];
    char password[50];

    printf("\n=== Admin Login ===\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (loginAdmin(username, password)) {
        isAdminLoggedIn = true;
        printf("Login berhasil!\n");
        handleAdminMenu();
    } else {
        printf("Username & Password tidak ditemukan!\n");
    }
}

void handleUserLogin() {
    printf("\n=== User Login ===\n");
    printf("Enter your name: ");
    scanf("%s", currentUserRealName);
    printf("Enter your username: ");
    scanf("%s", currentUserName);

    isUserLoggedIn = true;
    printf("Welcome, %s!\n", currentUserRealName);
    handleUserMenu();
}

void handleAdminMenu() {
    int choice;
    do {
        displayAdminMenu();
        scanf("%d", &choice);
        getchar(); // Clear buffer

        switch (choice) { // Tinggal tambahin case sesuai menu admin buat nambah fitur
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (isAdminLoggedIn);
}

void handleUserMenu() {
    int choice;
    do {
        displayUserMenu();
        scanf("%d", &choice);
        getchar(); // Clear buffer

        switch (choice) { // Tinggal tambahin case sesuai menu user buat nambah fitur
            case 1:
                displayUserTransactions(currentUserName);
                break;
            case 2:
                isUserLoggedIn = false;
                printf("Logged out berhasil!\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (isUserLoggedIn);
}

void handleBorrowBook() {
    char kodeBuku[20];
    printf("Masukkan kode buku: ");
    scanf("%s", kodeBuku);
    getchar();

    BookNode* book = findBook(kodeBuku);
    if (book == NULL) {
        printf("Error: Buku tidak ditemukan!\n");
        printf("Tekan Enter untuk melanjutkan...");
        getchar();
        return;
    }

    if (processBookBorrow(currentUserName, currentUserRealName, kodeBuku)) {
        printf("Buku berhasil dipinjam!\n");
        addBookToUserHistory(currentUserName, book->judul, book->genre);
    } else {
        printf("Tekan Enter untuk melanjutkan...");
        getchar();
    }
}

void handleReturnBook() {
    char transactionId[20];
    printf("Masukkan ID Transaksi: ");
    scanf("%s", transactionId);

    if (processBookReturn(transactionId)) {
        printf("Buku berhasil dikembalikan!\n");
    } else {
        printf("ID Transaksi tidak valid!\n");
    }
}