// Tablero.h

#ifndef _TABLERO_H
#define _TABLERO_H

#include "struct.h"

Tablero *InitializeTablero();
void UpdateTablero(Tablero *, Player **, int, int, int);
void ShowTablero(Tablero *);

#endif
