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
#define MAX 28
#define MAX_VALOR 6

// Estructuras
typedef struct {
	//char name[3];
	int value[2];
	int available;
} Ficha;

// Prototipos
void Domino();


int main(void) {
	Domino();
	return 0;
}

// Procedimientos
void Domino() {
	int cantidad = MAX;
	Ficha fichas[cantidad];

	// Inicializacion de fichas
	int index = 0;
    for (int j = 0; j <= MAX_VALOR; j++) {
        for (int k = j; k <= MAX_VALOR; k++) {
            fichas[index].value[0] = j;
            fichas[index].value[1] = k;
            fichas[index].available = 1;
            //snprintf(fichas[index].name, sizeof(fichas[index].name), "%d-%d", j, k);
            index++;
        }
    }

	// Imprimir fichas
	for(int i = 0; i < cantidad; i++) {
		printf("%d - %d\n", fichas[i].value[0], fichas[i].value[1]);
	}
	
}
