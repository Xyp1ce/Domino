// Utility.h

#ifndef _UTILITY_H
#define _UTILITY_H

#include "Fichas.h"
#include "Player.h"
#include "Tablero.h"

int Random(int cantidad);
void ClearBuffer();
void FreeMemory(Ficha **fichas, Player **jugadores, Tablero *tablero, int cantidad, int py);

#endif


