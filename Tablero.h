// Tablero.h

#ifndef _TABLERO_H
#define _TABLERO_H

#include "Fichas.h"

typedef struct Player Player;

typedef struct {
    Ficha **fichasEnTablero;
    int cantidad;
} Tablero;

Tablero *InitializeTablero();
void UpdateTablero(Tablero *, Player **, int, int, int);
void ShowTablero(Tablero *);

#endif
