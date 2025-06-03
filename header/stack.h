#ifndef STACK_H
#define STACK_H

typedef struct RiwayatNode { 
    char judul[100]; 
    struct RiwayatNode* next; 
} RiwayatNode;


void tambahRiwayat(RiwayatNode** top, const char* judul);
// IS : top menunjuk ke node teratas stack atau NULL jika kosong
// FS :  menunjuk ke node baru yang berisi judul, dengan next menunjuk ke node sebelumnya.

void hapusRiwayatTerakhir(RiwayatNode** top);
// IS : top menunjuk ke node teratas stack jika tidak NULL
// FS : top menunjuk ke node sebelumnya, dan memory node teratas dibebaskan.

void lihatBukuTerakhir(RiwayatNode* top);
// IS : top menunjuk ke node teratas stack jika tidak NULL
// FS : menampilkan judul buku terakhir yang ditambahkan ke stack.

void tampilkanRiwayat(RiwayatNode* top);
// IS : top menunjuk ke node teratas stack jika tidak NULL
// FS : menampilkan judul buku yang ditambahkan dari atas kebawah.

void resetRiwayat(RiwayatNode** top);
// IS : top menunjuk ke node teratas stack jika tidak NULL
// FS : top menunjuk ke NULL, dan semua node di stack dibebaskan.

#endif