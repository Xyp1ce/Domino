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
} Ficha;

typedef struct {
	Ficha **fichasPerPlayer;
} Player;

// Prototipos
void Domino();
int Random(int );
void ClearBuffer();
Ficha **Initialize(int);
int Repartir(Ficha**, Player**, int, int);
Player **InitializePlayers(int);

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
	Player **jugadores = InitializePlayers(py);
	
	// Inicializacion de fichas
	int cantidad = MAX;
	Ficha **fichas = Initialize(cantidad);

	// Repartir fichas
	cantidad = Repartir(fichas, jugadores, py, cantidad);

	// Impresion de fichas por jugador
	for(int i = 0; i < py; i++) {
		printf("Jugador %d\n", i + 1);
		for(int j = 0; j < 7; j++) {
			printf("%d - %d", (jugadores[i])->fichasPerPlayer[j]->value[0], (jugadores[i])->fichasPerPlayer[j]->value[1]);
			printf("\n");
		}
	}

	
	// Impresion de fichas sin agarrar
	if (fichas != NULL && cantidad > 0) {
    printf("Fichas sin jugar: %d\n", cantidad);
    for (int i = 0; i < cantidad; i++) {
        printf("%d - %d\n", fichas[i]->value[0], fichas[i]->value[1]);
    }
	} else {
    printf("No hay fichas sin jugar.\n");
	}
	

	// Liberacion de memoria
	for(int i = 0; i < py; i++) {
		free(jugadores[i]);
	}
	free(jugadores);

}

Player **InitializePlayers(int py) {
	printf("Inicializando jugadores\n");
	Player **jugador = (Player **)malloc(py * sizeof(Player *)); // Generamos un arreglo dinamico dependiendo de la cantidad de jugadores
	for(int i = 0; i < py; i++) { // Asignamos memoria para cada jugador para almacenar un estructura de tipo Player
		jugador[i] = (Player *)malloc(sizeof(Player));
		jugador[i]->fichasPerPlayer = (Ficha**)malloc(7 * sizeof(Ficha*));
		for(int j = 0; j < 7; j++) {
			jugador[i]->fichasPerPlayer[j] = (Ficha*)malloc(sizeof(Ficha));
		}
	}
	return jugador;
}

Ficha **Initialize(int cantidad) {
	printf("Inicializando Fichas\n");
	Ficha **fichas = (Ficha**)malloc(cantidad * sizeof(Ficha*));
	for(int i = 0; i < cantidad; i++) {
		fichas[i] = (Ficha*)malloc(sizeof(Ficha));
	}

	int index = 0;
    for (int j = 0; j <= MAX_VALOR; j++) {
        for (int k = j; k <= MAX_VALOR; k++) {
            fichas[index]->value[0] = j;
			fichas[index]->value[1] = k;
            index++;
        }
    }
	return fichas;
}

int Random(int cantidad) {
	return rand() % cantidad;
}

int Repartir(Ficha **fichas, Player **jugador, int py, int cantidad) {
    printf("Repartiendo Fichas\n");
    int fichasPorJugador = 7;

    for (int i = 0; i < py; i++) {
        for (int j = 0; j < fichasPorJugador && cantidad > 0; j++) {
            int indexFicha = Random(cantidad);

            // Copiar la ficha al jugador
            *(jugador[i]->fichasPerPlayer[j]) = *(fichas[indexFicha]);

            // Liberar la ficha seleccionada
            free(fichas[indexFicha]);

            // Mover las fichas restantes
            for (int k = indexFicha; k < cantidad - 1; k++) {
                fichas[k] = fichas[k + 1];
            }

            cantidad--;

            // Redimensionar el arreglo
            Ficha **aux = NULL;
            if (aux == NULL && cantidad > 0) {
                aux = realloc(fichas, cantidad * sizeof(Ficha *));
            }
            fichas = aux;
        }
    }
	return cantidad;
}

void ClearBuffer(){
    char c;
	while((c = getchar() ) != '\n' && c != EOF);
}