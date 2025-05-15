// Player.h

#ifndef _PLAYER_H
#define _PLAYER_H

#include "Fichas.h"

typedef struct Tablero Tablero;

typedef struct Player {
    Ficha **fichasPerPlayer;
    int cantidad;
} Player;

Player **InitializePlayers(int py);
int Repartir(Ficha **fichas, Player **jugador, int py, int cantidad);
int CheckWinner(Player **jugadores, int pos);
int StarterPlayer(Player **jugadores, int py);
int SelectFicha(Player **jugadores, int pos);
int CheckPieza(Player **jugador, int pos, int ficha, Tablero *tablero);
int SearchPieza(Player **jugador, Tablero *tablero, int pos);
void EatPieza(Player **jugador, Ficha ***fichas, Tablero *tablero, int pos, int *cantidad);

#endif
