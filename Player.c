#include <stdio.h>
#include <stdlib.h>
#include "Player.h"
#include "Fichas.h"
#include "Tablero.h"
#include "Utility.h"

Player **InitializePlayers(int py) {
    Player **jugador = (Player **)malloc(py * sizeof(Player *));
    for (int i = 0; i < py; i++) {
        jugador[i] = (Player *)malloc(sizeof(Player));
        jugador[i]->fichasPerPlayer = (Ficha **)malloc(7 * sizeof(Ficha *));
        for (int j = 0; j < 7; j++) {
            jugador[i]->fichasPerPlayer[j] = (Ficha *)malloc(sizeof(Ficha));
        }
        jugador[i]->cantidad = 7;
    }
    return jugador;
}

int Repartir(Ficha **fichas, Player **jugador, int py, int cantidad) {
    int fichasPorJugador = cantidad / 4;
    for (int i = 0; i < py; i++) {
        for (int j = 0; j < fichasPorJugador && cantidad > 0; j++) {
            int indexFicha = Random(cantidad);
            *(jugador[i]->fichasPerPlayer[j]) = *(fichas[indexFicha]);
            free(fichas[indexFicha]);
            fichas = Desplazamiento(fichas, cantidad, indexFicha);
            cantidad--;
        }
    }
    return cantidad;
}

int StarterPlayer(Player **jugadores, int py) {
    for (int k = 6; k >= 0; k--) {
        for (int i = 0; i < py; i++) {
            for (int j = 0; j < jugadores[i]->cantidad; j++) {
                if (jugadores[i]->fichasPerPlayer[j]->value[0] == k && jugadores[i]->fichasPerPlayer[j]->value[1] == k) {
                    return i;
                }
            }
        }
    }
    return 0; // fallback
}

int CheckPieza(Player **jugador, int pos, int ficha, Tablero *tablero) {
    if (tablero->cantidad == 0) return 1;

    int jugadorLado0 = jugador[pos]->fichasPerPlayer[ficha]->value[0];
    int jugadorLado1 = jugador[pos]->fichasPerPlayer[ficha]->value[1];

    int tableroIzq = tablero->fichasEnTablero[0]->value[0];
    int tableroDer = tablero->fichasEnTablero[tablero->cantidad - 1]->value[1];

    int puedeIzquierda = (jugadorLado0 == tableroIzq || jugadorLado1 == tableroIzq);
    int puedeDerecha = (jugadorLado0 == tableroDer || jugadorLado1 == tableroDer);

    int opc;
    if (puedeIzquierda && puedeDerecha) {
        do {
            printf("\n¿De qué lado quiere jugar la ficha?\n [1] Izquierda [2] Derecha\n>> ");
            scanf("%d", &opc);
            ClearBuffer();
        } while (opc != 1 && opc != 2);
        return opc;
    }
    if (puedeIzquierda) return 1;
    if (puedeDerecha) return 2;

    return 0;
}

void EatPieza(Player **jugador, Ficha ***fichas, Tablero *tablero, int pos, int *cantidad) {
    if (*cantidad <= 0) {
        printf("No hay más fichas para tomar.\n");
        return;
    }
    Ficha **aux = NULL;
    while (!aux) {
        aux = realloc(jugador[pos]->fichasPerPlayer, (jugador[pos]->cantidad + 1) * sizeof(Ficha *));
    }
    jugador[pos]->fichasPerPlayer = aux;

    int indexFicha = Random(*cantidad);
    jugador[pos]->fichasPerPlayer[jugador[pos]->cantidad] = malloc(sizeof(Ficha));
    *(jugador[pos]->fichasPerPlayer[jugador[pos]->cantidad]) = *(*fichas)[indexFicha];
    jugador[pos]->cantidad++;

    free((*fichas)[indexFicha]);
    for (int i = indexFicha; i < *cantidad - 1; i++) {
        (*fichas)[i] = (*fichas)[i + 1];
    }
    *cantidad -= 1;
    *fichas = realloc(*fichas, (*cantidad) * sizeof(Ficha *));

    if (!SearchPieza(jugador, tablero, pos)) {
        EatPieza(jugador, fichas, tablero, pos, cantidad);
    }
}

int SearchPieza(Player **jugador, Tablero *tablero, int pos) {
    if (tablero->cantidad == 0) return 1;
    int izquierda = tablero->fichasEnTablero[0]->value[0];
    int derecha = tablero->fichasEnTablero[tablero->cantidad - 1]->value[1];

    for (int i = 0; i < jugador[pos]->cantidad; i++) {
        int v0 = jugador[pos]->fichasPerPlayer[i]->value[0];
        int v1 = jugador[pos]->fichasPerPlayer[i]->value[1];
        if (v0 == izquierda || v1 == izquierda || v0 == derecha || v1 == derecha) return 1;
    }
    return 0;
}

int SelectFicha(Player **jugadores, int pos) {
    int ficha = 0;
    printf("\nJugador %d\n", pos + 1);
    for (int j = 0; j < jugadores[pos]->cantidad; j++) {
        printf("[%d] %d - %d\n", j, jugadores[pos]->fichasPerPlayer[j]->value[0], jugadores[pos]->fichasPerPlayer[j]->value[1]);
    }
    do {
        printf("\nSelecciona tu ficha a jugar\n>> ");
        scanf("%d", &ficha);
        ClearBuffer();
    } while (ficha < 0 || ficha >= jugadores[pos]->cantidad);
    return ficha;
}

int CheckWinner(Player **jugadores, int pos) {
    if (jugadores[pos]->cantidad == 0) {
        printf("Gano el jugador %d!!!\n", pos + 1);
        return 1;
    }
    return 0;
}

