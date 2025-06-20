#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "admin.h"
#include "booklist.h"
#include "tree.h"
#include "queue.h"
#include "stack.h"
#include "transaksi.h"
#include "rekomendasi.h"

// Variabel Global
extern bool isAdminLoggedIn;
extern bool isUserLoggedIn;
extern char currentUserName[50];

// Fungsi untuk menampilkan menu utama, menu admin, dan menu user
void displayHeader();
void displayMainMenu();
void displayAdminMenu();
void displayUserMenu();

// Fungsi untuk menangani login admin dan user
void handleAdminLogin();
void handleUserLogin();

// Fungsi untuk menangani menu admin dan user
void handleAdminMenu();
void handleUserMenu();

// Fungsi operasi admin
void handleAddGenre();
void handleAddBook();
void handleRemoveBook();
void handleUpdateStock();

// Fungsi User
void handleBorrowBook();
void handleReturnBook();

#endif // MENU_H
