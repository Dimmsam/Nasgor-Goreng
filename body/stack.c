#include <stdlib.h>
#include <string.h>
#include "stack.h"


void tambahRiwayat(RiwayatNode** top, const char* judul){
    RiwayatNode* nodeBaru = (RiwayatNode*)malloc(sizeof(RiwayatNode));
    strcpy(nodeBaru->judul, judul, sizeof(nodeBaru->judul) - 1);
    nodeBaru->judul[sizeof(nodeBaru->judul) - 1];
    nodeBaru->next = *top;
    *top = nodeBaru;
}

void hapusRiwayatTerakhir(RiwayatNode** top){
    if(top == NULL){
        printf("Riwayat Kosong\n");
        return;
    }
    RiwayatNode* temp = *top;
    *top = (*top)->next;
    free(temp);
}

void lihatBukuTerakhir(RiwayatNode* top){
    if(top == NULL){
        printf("Belum ada riwayat baca");
    }else{
        printf("Buku terakhir yang dibaca: %s\n", top->judul);
    }
}

void tampilkanRiwayat(RiwayatNode* top){
    RiwayatNode* current = top;
    int counter = 1;
    while (current != NULL) {
        printf("%d. %s\n", counter++, current->judul);
        current = current->next;
    }
    if(counter == 1){
        printf("Riwayat kosong\n");
        printf("===============\n");
    }
}

void resetRiwayat(RiwayatNode** top){
    while(*top != NULL){
        hapusRiwayatTerakhir(top);
    }
}