// struct.h

#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct {
	int value[2];
} Ficha;

typedef struct {
	Ficha **fichasPerPlayer;
	int cantidad;
} Player; 

typedef struct {
	Ficha **fichasEnTablero;
	int cantidad;
} Tablero;

#endif
