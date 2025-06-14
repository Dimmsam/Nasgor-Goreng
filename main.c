#include "header/menu.h"

int main() {
    int choice;
    do {
        displayMainMenu();
        scanf("%d", &choice);
        getchar(); // Clear buffer

        switch (choice) {
            case 1:
                handleAdminLogin();
                break;
            case 2:
                handleUserLogin();
                break;
            case 3:
                printf("Terima kasih sudah mampir di Perpustkaan Digital!\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (choice != 3);
    return 0;
}
