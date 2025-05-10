/*
 * Ramon Manriquez Guerrero
 * 2210376
 * Domino Simplificado
 * Programacion Estructurada
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Incluir libreria de funciones #include "funciones.h"

// Constantes
#define MAX 28
#define MAX_VALOR 6
#define PLAYERS 4

// Estructuras
typedef struct {
	int value[2];
	int available;
} Ficha;

typedef struct {
	int fichas[7];
} Player;

// Prototipos
void Domino();
int Random();
void ClearBuffer();
void Initialize(Ficha*);
void Repartir(Ficha*, Player**, int);
void InitializePlayers(Player***, int);

int main(void) {
	srand(time(NULL));
	Domino();
	return 0;
}

// Procedimientos
void Domino() {
	// Seleccion de jugadores
	int py = 0;
	do {
		printf("\nCuantos jugadores van a jugar?\n");
		printf("[1] Salir [2] 2 jugadores [3] 3 Jugadores [4] 4 Jugadores\n>> ");
		scanf("%d", &py);
		ClearBuffer();
	}while(py >= 5);

	if(py == 1) {
		return;
	}
	// Generacion de jugadores
	Player **jugadores = NULL;
	InitializePlayers(&jugadores, py);

	// Inicializacion de fichas
	int cantidad = MAX;
	Ficha fichas[cantidad];
	Initialize(fichas);

	// Repartir fichas
	Repartir(fichas, jugadores, py);
}

void InitializePlayers(Player ***jugador, int py) {
	
	*jugador = (Player **)malloc(py * sizeof(Player *)); // Generamos un arreglo dinamico dependiendo de la cantidad de jugadores
	for(int i = 0; i < py; i++) { // Asignamos memoria para cada jugador para almacenar un estructura de tipo Player
		(*jugador)[i] = (Player *)malloc(sizeof(Player));
	}
}

void Initialize(Ficha *fichas) {
	
	int index = 0;
    for (int j = 0; j <= MAX_VALOR; j++) {
        for (int k = j; k <= MAX_VALOR; k++) {
            fichas[index].value[0] = j;
            fichas[index].value[1] = k;
            fichas[index].available = 1;
            index++;
        }
    }
}

int Random() {
	return rand() % MAX;
}

void Repartir(Ficha *fichas, Player **jugador, int py) {
	int fichasPorJugador = 7;
	int indexFicha = Random();
	for(int i = 0; i < py; i++) { // Iteramos sobre los jugadores
		for(int j = 0; j < fichasPorJugador; j++) { // Son 7 fichas por jugador
			while(!fichas[indexFicha].available) {
				indexFicha = Random(); // En caso que la ficha no este disponible generamos un nuevo index
			}
			jugador[i] -> fichas[j] = indexFicha;
			fichas[indexFicha].available = 0;
			indexFicha = Random();
		}
	}
}

void ClearBuffer(){
    char c;
	while((c = getchar() ) != '\n' && c != EOF);
}