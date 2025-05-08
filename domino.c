/*
 * Ramon Manriquez Guerrero
 * 2210376
 * Domino Simplificado
 * Programacion Estructurada
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Incluir libreria de funciones

// Constantes

// Estructuras
typedef struct {
	char name[3];
	int value[2];
	int available;
}Ficha;

// Prototipos
void Domino();


int main(void) {
	Domino();
	return 0;
}

// Procedimientos
void Domino() {
	int cantidad = 28;
	Ficha fichas[cantidad];

	// Inicializacion de fichas
	for(int i = 0; i < 7; i++) {
		for(int j = i; j < 7 - i; j++) {
			//fichas[i].name =
			fichas[i].value[0] = i;
			fichas[i].value[1] = j;
			fichas[i].available = 1;
		}
	}

	// Imprimir fichas
	for(int i = 0; i < cantidad; i++) {
		printf("%d - %d\n", fichas[i].value[0], fichas[i].value[1]);
	}
	
}
