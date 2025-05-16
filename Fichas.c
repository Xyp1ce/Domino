// Fichas.c
#include <stdio.h>
#include <stdlib.h>
#include "Fichas.h"
#include "struct.h"
#include "Utility.h"

#define MAX_VALOR 6

Ficha **Initialize(int cantidad) {
    Ficha **fichas = (Ficha**)malloc(cantidad * sizeof(Ficha*));
    for (int i = 0; i < cantidad; i++) {
        fichas[i] = (Ficha*)malloc(sizeof(Ficha));
    }

    int index = 0;
    for (int j = 0; j <= MAX_VALOR; j++) {
        for (int k = j; k <= MAX_VALOR; k++) {
            fichas[index]->value[0] = j;
            fichas[index]->value[1] = k;
            index++;
        }
    }
    return fichas;
}

Ficha **Desplazamiento(Ficha **fichas, int cantidad, int index) {
    for (int i = index; i < cantidad - 1; i++) {
        fichas[i] = fichas[i + 1];
    }
    fichas = realloc(fichas, (cantidad - 1) * sizeof(Ficha*));
    return fichas;
}

void ImpresionFichas(Ficha **fichas, int cantidad) {
    if (fichas != NULL && cantidad > 0) {
        printf("\nFichas sin jugar: %d\n", cantidad);
        for (int i = 0; i < cantidad; i++) {
            printf("%d - %d\n", fichas[i]->value[0], fichas[i]->value[1]);
        }
    } else {
        printf("\nNo hay fichas sin jugar.\n");
    }
}

