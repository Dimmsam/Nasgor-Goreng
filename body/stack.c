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