#ifndef STACK_H
#define STACK_H

typedef struct RiwayatNode { 
    char judul[100]; 
    struct RiwayatNode* next; 
} RiwayatNode;


void tambahRiwayat(RiwayatNode** top, const char* judul);

void hapusRiwayatTerakhir(RiwayatNode** top);

#endif