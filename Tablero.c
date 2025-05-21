// Tablero.c

#include <stdio.h>
#include <stdlib.h>
#include "Tablero.h"
#include "struct.h"
#include "Player.h"
#include "Fichas.h"
#include "Utility.h"

Tablero *InitializeTablero() {
    Tablero *tablero = (Tablero *)malloc(sizeof(Tablero));
    tablero->fichasEnTablero = NULL;
    tablero->cantidad = 0;
    return tablero;
}

void ShowTablero(Tablero *tablero) {
    printf("\nTablero Actual\n");
    for (int i = 0; i < tablero->cantidad; i++) {
        printf("[%d-%d] ", tablero->fichasEnTablero[i]->value[0], tablero->fichasEnTablero[i]->value[1]);
    }
    printf("\n");
}

void UpdateTablero(Tablero *tablero, Player **jugador, int fichaIndex, int pos, int lado) {
    Ficha **aux = NULL;
    while (!aux) {
        aux = realloc(tablero->fichasEnTablero, (tablero->cantidad + 1) * sizeof(Ficha *));
    }
    tablero->fichasEnTablero = aux;

    if (lado == 1) {
        for (int i = tablero->cantidad; i > 0; i--) {
            tablero->fichasEnTablero[i] = tablero->fichasEnTablero[i - 1];
        }
        tablero->fichasEnTablero[0] = (Ficha *)malloc(sizeof(Ficha));
        *(tablero->fichasEnTablero[0]) = *(jugador[pos]->fichasPerPlayer[fichaIndex]);
        if (tablero->cantidad > 0 &&
            tablero->fichasEnTablero[0]->value[1] != tablero->fichasEnTablero[1]->value[0]) {
            int auxVal = tablero->fichasEnTablero[0]->value[0];
            tablero->fichasEnTablero[0]->value[0] = tablero->fichasEnTablero[0]->value[1];
            tablero->fichasEnTablero[0]->value[1] = auxVal;
        }
    } else {
        tablero->fichasEnTablero[tablero->cantidad] = malloc(sizeof(Ficha));
        *(tablero->fichasEnTablero[tablero->cantidad]) = *(jugador[pos]->fichasPerPlayer[fichaIndex]);
        if (tablero->cantidad > 0 &&
            tablero->fichasEnTablero[tablero->cantidad - 1]->value[1] !=
                tablero->fichasEnTablero[tablero->cantidad]->value[0]) {
            int auxVal = tablero->fichasEnTablero[tablero->cantidad]->value[0];
            tablero->fichasEnTablero[tablero->cantidad]->value[0] =
                tablero->fichasEnTablero[tablero->cantidad]->value[1];
            tablero->fichasEnTablero[tablero->cantidad]->value[1] = auxVal;
        }
    }
    tablero->cantidad++;

    printf("\nTablero Actual\n");
    for (int i = 0; i < tablero->cantidad; i++) {
        printf("[%d-%d] ", tablero->fichasEnTablero[i]->value[0], tablero->fichasEnTablero[i]->value[1]);
    }
    printf("\n");

    free(jugador[pos]->fichasPerPlayer[fichaIndex]);
    for (int i = fichaIndex; i < jugador[pos]->cantidad - 1; i++) {
        jugador[pos]->fichasPerPlayer[i] = jugador[pos]->fichasPerPlayer[i + 1];
    }

    jugador[pos]->cantidad--;

    aux = NULL;
    while (!aux) {
        aux = realloc(jugador[pos]->fichasPerPlayer, jugador[pos]->cantidad * sizeof(Ficha *));
    }
    jugador[pos]->fichasPerPlayer = aux;
}
