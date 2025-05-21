// Utility.c

#include <stdio.h>
#include <stdlib.h>
#include "Utility.h"

int Random(int cantidad) {
    return rand() % cantidad;
}

void ClearBuffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void FreeMemory(Ficha **fichas, Player **jugadores, Tablero *tablero, int cantidad, int py) {
    for (int i = 0; i < py; i++) {
        for (int j = 0; j < jugadores[i]->cantidad; j++) {
            free(jugadores[i]->fichasPerPlayer[j]);
        }
        free(jugadores[i]->fichasPerPlayer);
        free(jugadores[i]);
    }
    free(jugadores);

    for (int i = 0; i < cantidad; i++) {
        free(fichas[i]);
    }
    free(fichas);

    free(tablero->fichasEnTablero);
    free(tablero);
}
