#include "../header/menu.h"

// Inisialisasi variabel global
bool isAdminLoggedIn = false;
bool isUserLoggedIn = false;
char currentUserName[50];

void displayHeader() {
    printf("\n");
    printf(" _____ _     _                  ______                         _        _                      ______ _       _ _        _ \n");
    printf("/  ___(_)   | |                 | ___ \\                       | |      | |                     |  _  (_)     (_) |      | |\n");
    printf("\\ `--. _ ___| |_ ___ _ __ ___   | |_/ /__ _ __ _ __  _   _ ___| |_ __ _| | ____ _  __ _ _ __   | | | |_  __   _| |_ __ _| |\n");
    printf(" `--. \\ / __| __/ _ \\ '_ ` _ \\  |  __/ _ \\ '__| '_ \\| | | / __| __/ _` | |/ / _` |/ _` | '_ \\  | | | | |/ _` | | __/ _` | |\n");
    printf("/\\__/ / \\__ \\ ||  __/ | | | | | | | |  __/ |  | |_) | |_| \\__ \\ || (_| |   < (_| | (_| | | | | | |/ /| | (_| | | || (_| | |\n");
    printf("\\____/|_|___/\\__\\___|_| |_| |_| \\_|  \\___|_|  | .__/ \\__,_|___/\\__\\__,_|_|\\_\\__,_|\\__,_|_| |_| |___/ |_|\\__, |_|\\__\\__,_|_|\n");
    printf("                                              | |                                                       __/ |             \n");
    printf("                                              |_|                                                      |___/              \n\n");
}

void displayMainMenu() {
    system("cls");
    displayHeader();
    printf("\t\t\t\t\t\t[1] Login sebagai Admin\n");
    printf("\t\t\t\t\t\t[2] Login sebagai User\n");
    printf("\t\t\t\t\t\t[3] Keluar\n");
    printf("\t\t\t\t\t\tMasukkan Pilihanmu: ");
}

void displayAdminMenu() {
    printf("\t\t\t\t\t\t======= Menu Admin =======\n");
    printf("\t\t\t\t\t\t[1] Tambah Genre Baru\n");
    printf("\t\t\t\t\t\t[2] Tambahkan Buku\n");
    printf("\t\t\t\t\t\t[3] Hapus Buku\n");
    printf("\t\t\t\t\t\t[4] Lihat List Buku\n");
    printf("\t\t\t\t\t\t[5] Atur Stok Buku\n");
    printf("\t\t\t\t\t\t[6] Logout\n");
    printf("\t\t\t\t\t\tMasukkan pilihanmu: ");
}

void displayUserMenu() {
    printf("\t\t\t\t\t\t======= Menu User =======\n");
    printf("\t\t\t\t\t\t[1] Lihat Koleksi Buku\n");
    printf("\t\t\t\t\t\t[2] Pinjam Buku\n");
    printf("\t\t\t\t\t\t[3] Kembalikan Buku\n");
    printf("\t\t\t\t\t\t[4] Lihat Riwayat Bacaan\n");
    printf("\t\t\t\t\t\t[5] Lihat Rekomendasi Buku\n");
    printf("\t\t\t\t\t\t[6] Lihat Buku Terpopuler\n");
    printf("\t\t\t\t\t\t[7] Lihat Transaksi User\n");
    printf("\t\t\t\t\t\t[8] Hapus semua riwayat bacaan\n");
    printf("\t\t\t\t\t\t[9] Logout\n");
    printf("\t\t\t\t\t\tMasukkan pilihanmu: ");
}

void handleAdminLogin() {
    char username[50];
    char password[50];

    system("cls");
    displayHeader();
    printf("\n\t\t\t\t\t\t=== Admin Login ===\n");
    printf("\t\t\t\t\t\tUsername: ");
    scanf("%s", username);
    printf("\t\t\t\t\t\tPassword: ");
    scanf("%s", password);

     if (loginAdmin(username, password)) {
        isAdminLoggedIn = true;
        system("cls");
        displayHeader();
        printf("\t\t\t\t\t\tLogin berhasil!\n");
        printf("\t\t\t\t\t\tSelamat datang, %s!\n", username);
        printf("\n\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
        getchar();
        getchar();
        handleAdminMenu();
    } else {
        printf("\n\t\t\t\t\t\tUsername & Password tidak ditemukan!\n");
        printf("\t\t\t\t\t\tTekan Enter untuk kembali...");
        getchar();
        getchar();
    }
}

void handleUserLogin() {
    system("cls");
    displayHeader();
    printf("\n\t\t\t\t\t\t=== User Login ===\n");
    printf("\t\t\t\t\t\tEnter your username: ");
    scanf("%s", currentUserName);

    system("cls");
    displayHeader();
    printf("\t\t\t\t\t\tLogin berhasil!\n");
    printf("\t\t\t\t\t\tSelamat datang, %s!\n", currentUserName);
    printf("\n\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
    getchar();
    getchar();
    
    isUserLoggedIn = true;
    handleUserMenu();
}

void handleAdminMenu() {
    int choice;
    do {
        system("cls");
        displayHeader();
        displayAdminMenu();
        scanf("%d", &choice);
        getchar(); // Clear buffer

        system("cls");
        displayHeader();

        switch (choice) {
            case 1:
                handleAddGenre();
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
                break;
            case 2:
                handleAddBook();
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
                break;
            case 3:
                handleRemoveBook();
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
                break;
            case 4:
                displayAllBooks();
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
                break;
            case 5:
                handleUpdateStock();
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
                break;
            case 6:
                isAdminLoggedIn = false;
                printf("\t\t\t\t\t\tLog out berhasil!\n");
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
                break;
            default:
                printf("\t\t\t\t\t\tPilihan tidak valid!\n");
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
        }
    } while (isAdminLoggedIn);
}

void handleUserMenu() {
    int choice;
    do {
        system("cls");
        displayHeader();
        displayUserMenu();
        scanf("%d", &choice);
        getchar(); // Clear buffer

        system("cls");
        displayHeader();

        switch (choice) { // Tinggal tambahin case sesuai menu user buat nambah fitur
            case 1:
                displayAllBooks();
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
                break;
            case 2:
                handleBorrowBook();
                break;
            case 3:
                handleReturnBook();
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
                break;
            case 4:
                displayUserHistory(currentUserName);
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
                break;
            case 5:
                displayRecommendationsForUser(currentUserName);
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
                break;
            case 6:
                displayTopBooksByViewCount();
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
                break;
            case 7:
                displayUserTransactions(currentUserName);
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
                break;
            case 8:
                clearAllHistory(getUserStack(currentUserName));
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
                break;
            case 9:
                isUserLoggedIn = false;
                printf("\t\t\t\t\t\tLog out berhasil!\n");
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
                break;
            default:
                printf("\t\t\t\t\t\tPilihan tidak valid!\n");
                printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                getchar();
        }
    } while (isUserLoggedIn);
}

void handleAddGenre() {
    int parentChoice;
    char genreName[50];
    printf("\t\t\t\t\t\tPilih parent genre:\n");
    printf("\t\t\t\t\t\t1. Fiksi\n");
    printf("\t\t\t\t\t\t2. Non-Fiksi\n");
    printf("\t\t\t\t\t\tMasukkan pilihan (1/2): ");
    scanf("%d", &parentChoice);
    getchar();
    GenreNode* parent = NULL;
    if (parentChoice == 1) {
        parent = findMainGenre("Fiksi");
    } else if (parentChoice == 2) {
        parent = findMainGenre("Non-Fiksi");
    } else {
        printf("\t\t\t\t\t\tPilihan tidak valid!\n");
        return;
    }
    printf("\t\t\t\t\t\tMasukkan nama genre baru: ");
    scanf("%s", genreName);
    addSubGenre(parent, genreName);
    printf("\t\t\t\t\t\tGenre '%s' berhasil ditambahkan di bawah %s!\n", genreName, parent->genreName);
    getchar();
}

void handleAddBook() {
     char genreName[50];
    char judul[100];
    char penulis[100];
    char penerbit[100];
    char kode[20];
    int tahun, stok;

    printf("\t\t\t\t\t\tMasukkan Nama Genre: ");
    scanf("%s", genreName);
    printf("\t\t\t\t\t\tMasukkan Judul Buku: ");
    scanf(" %[^\n]s", judul);
    printf("\t\t\t\t\t\tMasukkan Penulis: ");
    scanf(" %[^\n]s", penulis);
    printf("\t\t\t\t\t\tMasukkan Penerbit: ");
    scanf(" %[^\n]s", penerbit);
    printf("\t\t\t\t\t\tMasukkan Tahun Terbit: ");
    scanf("%d", &tahun);
    printf("\t\t\t\t\t\tMasukkan Kode Buku: ");
    scanf("%s", kode);
    printf("\t\t\t\t\t\tMasukkan Stok: ");
    scanf("%d", &stok);

    BookNode* newBook = createBook(judul, penulis, penerbit, tahun, kode, stok, genreName);
    if (newBook != NULL) {
        addBookToGenre(genreName, newBook);
    }

    printf("\t\t\t\t\t\tBuku '%s' berhasil ditambahkan ke genre '%s'!\n", judul, genreName);
}

void handleRemoveBook() {
    char genreName[50];
    char kodeBuku[20];

    printf("\t\t\t\t\t\tMasukkan Nama Genre: ");
    scanf("%s", genreName);
    printf("\t\t\t\t\t\tMasukkan Kode Buku: ");
    scanf("%s", kodeBuku);

    removeBookFromGenre(genreName, kodeBuku);
}

void handleUpdateStock() {
    char kodeBuku[20];
    int newStock;

    printf("\t\t\t\t\t\tMasukkan Kode Buku : ");
    scanf("%s", kodeBuku);
    printf("\t\t\t\t\t\tMasukkan Stok Baru : ");
    scanf("%d", &newStock);

    updateBookStock(kodeBuku, newStock);
}

void handleBorrowBook() {
    char kodeBuku[20];
    printf("\t\t\t\t\t\tMasukkan kode buku: ");
    scanf("%s", kodeBuku);
    getchar();

    BookNode* book = findBook(kodeBuku);
    if (book == NULL) {
        printf("\t\t\t\t\t\tError: Buku tidak ditemukan!\n");
        printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
        getchar();
        return;
    }

    if (processBookBorrow(currentUserName, kodeBuku)) {
        printf("\t\t\t\t\t\tBuku berhasil dipinjam!\n");
        printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
        getchar();
    } else {
        printf("\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
        getchar();
    }
}

void handleReturnBook() {
    char transactionId[20];
    printf("\t\t\t\t\t\tMasukkan ID Transaksi: ");
    scanf("%s", transactionId);

    if (processBookReturn(transactionId)) {
        printf("\t\t\t\t\t\tBuku berhasil dikembalikan!\n");
        getchar();
    } else {
        printf("\t\t\t\t\t\tID Transaksi tidak valid!\n");
        getchar();
    }
}