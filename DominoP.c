// DominoP.c

#include <stdio.h>
#include <stdlib.h>
#include "Domino.h"
#include "Struct.h"
#include "Player.h"
#include "Fichas.h"
#include "Tablero.h"
#include "Utility.h"

#define MAX 28

void Domino() {
    int py = 0;
    do {
        printf("\nCuantos jugadores van a jugar?\n");
        printf("[1] Salir [2] 2 jugadores [3] 3 Jugadores [4] 4 Jugadores\n>> ");
        scanf("%d", &py);
        ClearBuffer();
    } while (py > 4 || py < 1);

    if (py == 1) {
        return;
    }

    Player **jugadores = InitializePlayers(py);
    int cantidad = MAX;
    Ficha **fichas = Initialize(cantidad);
    Tablero *tablero = InitializeTablero();

    cantidad = Repartir(fichas, jugadores, py, cantidad);

    int pos = StarterPlayer(jugadores, py);
    printf("\nComienza el jugador %d!\n", pos + 1);

    int orden[py];
    for (int i = 0; i < py; i++) {
        orden[i] = (pos + i) % py;
        printf("%d.- Jugador %d\n", i + 1, orden[i] + 1);
    }

    int pasar = 0;
    int turno = orden[0];
    int i = 0;

    while (!CheckWinner(jugadores, turno)) {
        turno = (turno + i) % py;
        if (!SearchPieza(jugadores, tablero, turno)) {
            EatPieza(jugadores, &fichas, tablero, turno, &cantidad);
        }
        if (!SearchPieza(jugadores, tablero, turno) && cantidad == 0) {
            pasar++;
            printf("El jugador %d pasa turno\n", turno + 1);
            if(pasar < py)
                continue;
        } else {
            pasar = 0; // Reiniciar contador si el jugador pudo jugar
        }
        // Si todos pasaron consecutivamente
        if (pasar == py) {
            printf("Empate!!\n");
            break;
        }

        int ficha = SelectFicha(jugadores, turno);
        int lado = CheckPieza(jugadores, turno, ficha, tablero);
        while (!lado) {
            ShowTablero(tablero);
            printf("Selecciona otra ficha\n");
            ficha = SelectFicha(jugadores, turno);
            lado = CheckPieza(jugadores, turno, ficha, tablero);
        }
        UpdateTablero(tablero, jugadores, ficha, turno, lado);
        i = 1;
    }

    ImpresionFichas(fichas, cantidad);
    FreeMemory(fichas, jugadores, tablero, cantidad, py);
}
