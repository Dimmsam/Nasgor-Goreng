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
    printf("1. Tambah Genre\n");
    printf("2. Tambahkan Buku ke Genre\n");
    printf("3. Hapus Buku\n");
    printf("4. Lihat Daftar Buku\n");
    printf("5. Atur Stok Buku\n");
    printf("6. Logout\n");
    printf("Masukkan pilihanmu: ");
}

void displayUserMenu() {
    printf("\n=== Menu User ===\n");
    printf("1. Lihat Koleksi Buku\n");
    printf("2. Pinjam Buku\n");
    printf("3. Kembalikan Buku\n");
    printf("4. Lihat Riwayat Bacaan\n");
    printf("5. Lihat Rekomendasi Buku\n");
    printf("6. Lihat Buku Terpopuler\n");
    printf("7. Lihat Transaksi User\n");
    printf("8. Logout\n");
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
        getchar();

        switch (choice) {
            case 1:
                handleAddGenre();
                break;
            case 2:
                handleAddBook();
                break;
            case 3:
                handleRemoveBook();
                break;
            case 4:
                displayAllBooks();
                break;
            case 5:
                handleUpdateStock();
                break;
            case 6:
                isAdminLoggedIn = false;
                printf("Log Out Berhasil\n");
                break;
            default:
                printf("Pilihan Tidak Valid\n");
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
                displayAllBooks();
                break;
            case 2:
                handleBorrowBook();
                break;
            case 3:
                handleReturnBook();
                break;
            case 4:
                displayUserHistory(currentUserName);
                break;
            case 5:
                displayRecommendationsForUser(currentUserName);
                break;
            case 6:
                displayTopBooksByViewCount();
                break;
            case 7:
                displayUserTransactions(currentUserName);
                break;
            case 8:
                isUserLoggedIn = false;
                printf("Logged out successfully!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (isUserLoggedIn);
}

void handleAddGenre() {
    int parentChoice;
    char genreName[50];
    printf("\nPilih parent genre:\n");
    printf("1. Fiksi\n");
    printf("2. Non-Fiksi\n");
    printf("Masukkan pilihan (1/2): ");
    scanf("%d", &parentChoice);
    getchar();
    GenreNode* parent = NULL;
    if (parentChoice == 1) {
        parent = findMainGenre("Fiksi");
    } else if (parentChoice == 2) {
        parent = findMainGenre("Non-Fiksi");
    } else {
        printf("Pilihan tidak valid!\n");
        return;
    }
    printf("Masukkan nama genre baru: ");
    scanf("%s", genreName);
    addSubGenre(parent, genreName);
    printf("Genre '%s' berhasil ditambahkan di bawah %s!\n", genreName, parent->genreName);
}

void handleAddBook() {
     char genreName[50];
    char judul[100];
    char penulis[100];
    char penerbit[100];
    char kode[20];
    int tahun, stok;

    printf("Masukkan Nama Genre : ");
    scanf("%s", genreName);
    printf("Masukkan Judul Buku : ");
    scanf(" %[^\n]s", judul);
    printf("Masukkan Penulis Buku : ");
    scanf(" %[^\n]s", penulis);
    printf("Masukkan Penerbit Buku : ");
    scanf(" %[^\n]s", penerbit);
    printf("Masukkan Tahun Terbit Buku : ");
    scanf("%d", &tahun);
    printf("Masukkan Kode Buku : ");
    scanf("%s", kode);
    printf("Masukkan Stok Buku : ");
    scanf("%d", &stok);

    BookNode* newBook = createBook(judul, penulis, penerbit, tahun, kode, stok, genreName);
    if (newBook != NULL) {
        addBookToGenre(genreName, newBook);
    }
}

void handleRemoveBook() {
    char genreName[50];
    char kodeBuku[20];

    printf("Masukkan Nama Genre: ");
    scanf("%s", genreName);
    printf("Masukkan Kode Buku: ");
    scanf("%s", kodeBuku);

    removeBookFromGenre(genreName, kodeBuku);
}

void handleUpdateStock() {
    char kodeBuku[20];
    int newStock;

    printf("Masukkan Kode Buku : ");
    scanf("%s", kodeBuku);
    printf("Masukkan Stok Baru: ");
    scanf("%d", &newStock);

    updateBookStock(kodeBuku, newStock);
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