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

// Estructuras


typedef struct {
	int value[2];
} Ficha;

typedef struct {
	Ficha **fichasPerPlayer;
} Player;

typedef struct {
	Ficha **fichasEnTablero;
	int cantidad;
} Tablero;

// Prototipos
void Domino();

// Prototipos para la inicializacion del juego
int Random(int );
void ClearBuffer();
Tablero **InitializeTablero();
Ficha **Initialize(int);
int Repartir(Ficha**, Player**, int, int);
Player **InitializePlayers(int);
Ficha **Desplazamiento(Ficha **, int, int);
void ImpresionFichas(Ficha **, int);


// Prototipos del juego
int CheckWinner(Player**, int);
int StarterPlayer(Player**, int);
int SelectFicha(Player **, int);
void UpdateTablero(Tablero **, int , Player **, int , int, int, int);

// Prototipo para terminar
void FreeMemory(Ficha **, Player **, int, int);

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

	// Inicializacion de tableros
	int size = 1;
	Tablero **tablero = InitializeTablero();

	// Repartir fichas
	cantidad = Repartir(fichas, jugadores, py, cantidad);

	for(int i = 0; i < py; i++) {
		printf("Jugador %d\n", i + 1);
		for(int j = 0; j < 7; j++) {
			printf("%d - %d", (jugadores[i])->fichasPerPlayer[j]->value[0], (jugadores[i])->fichasPerPlayer[j]->value[1]);
			printf("\n");
		}
	}

	// Impresion de fichas sin agarrar
	ImpresionFichas(fichas, cantidad);

	// Juego Domino

	int cantJ1 = 7, cantJ2 = 7, cantJ3 = 7, cantJ7 = 7;

	// Decidir jugador inicial
	int pos = StarterPlayer(jugadores, py);
	printf("Comienza el jugador %d!\n", pos + 1);

	// Establecer orden
	int orden[py];
	for(int i = 0; i < py; i++) {
		orden[i] = (pos + i) % py; 
		printf("%d.- Jugador %d\n", i + 1, orden[i] + 1);
	}

	// Seleccion de ficha a jugar del jugador
	int ficha = 0;
	ficha = SelectFicha(jugadores, 0);
	int lado = 0;
	UpdateTablero(tablero, size, jugadores, ficha, orden[0], cantJ1, lado);
	/*while(!CheckWinner(jugadores, py)) {
		
	}*/

	// Liberacion de memoria
	FreeMemory(fichas, jugadores, cantidad, py);

}

Player **InitializePlayers(int py) {
	printf("Inicializando jugadores\n");
	Player **jugador = (Player **)malloc(py * sizeof(Player *)); // Generamos un arreglo dinamico dependiendo de la cantidad de jugadores
	for(int i = 0; i < py; i++) { 
		jugador[i] = (Player *)malloc(sizeof(Player)); // Asignamos memoria para cada jugador para almacenar un estructura de tipo Player
		jugador[i]->fichasPerPlayer = (Ficha**)malloc(7 * sizeof(Ficha*)); // Generamos un arreglo de apuntadores dentro de cada estructura para las fichas
		for(int j = 0; j < 7; j++) {
			jugador[i]->fichasPerPlayer[j] = (Ficha*)malloc(sizeof(Ficha)); // Generamos espacio para 7 fichas por jugador
		}
	}
	return jugador;
}

Tablero **InitializeTablero() {
	Tablero **tablero = (Tablero**)malloc(sizeof(Tablero*));
	*tablero = (Tablero*)malloc(sizeof(Tablero));
	(*tablero)->fichasEnTablero = NULL;
	(*tablero)->cantidad = 0;
	return tablero;
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

            // Mover y redimensionar las fichas
			fichas = Desplazamiento(fichas, cantidad, indexFicha);
			// Reducir cantidad
            cantidad--;
        }
    }
	return cantidad;
}

void ClearBuffer(){
    char c;
	while((c = getchar() ) != '\n' && c != EOF);
}

Ficha **Desplazamiento(Ficha **Dezplazar, int cantidad, int index) {
	// Desplzar fichas
	for(int i = index; i < cantidad - 1; i++) {
		Dezplazar[i] = Dezplazar[i + 1];
	}
	// Redimensionar el arreglo
    Ficha **aux = NULL;
    while(aux == NULL) {
        aux = realloc(Dezplazar, (cantidad-1) * sizeof(Ficha *));
    }
	return aux;
}

void ImpresionFichas(Ficha **fichas, int cantidad) {
	if (fichas != NULL && cantidad > 0) {
    printf("Fichas sin jugar: %d\n", cantidad);
    for (int i = 0; i < cantidad; i++) {
        printf("%d - %d\n", fichas[i]->value[0], fichas[i]->value[1]);
    }
	} else {
    printf("No hay fichas sin jugar.\n");
	}
}

void FreeMemory(Ficha **fichas, Player **jugadores, int cantidad, int py) {
	for(int i = 0; i < py; i++) {
		for(int j = 0; j < 7; j++) {
			free(jugadores[i]->fichasPerPlayer[j]);
		}
		free(jugadores[i]->fichasPerPlayer);
		free(jugadores[i]);
	}
	free(jugadores);
	
	for(int i = 0; i < cantidad; i++) {
		free(fichas[i]);
	}
	free(fichas);
}

int CheckWinner(Player **jugadores, int py) {
	for(int i = 0; i < py; i++) {
		if(jugadores[i]->fichasPerPlayer == NULL) {
			return i; // Se regresa el index del ganador
		}
	}
	return 0; // Mientras sea 0 el juego continua
}

int StarterPlayer(Player **jugadores, int py) {
	int doble = 6;
	//int index = 0;
	for(int k = 6; k > 0; k--) {
		for(int i = 0; i < py; i++) {
			for(int j = 0; j < 7; j++) {
				// Verificacion del jugador con el doble mas alto
				if(jugadores[i]->fichasPerPlayer[j]->value[0] == k && jugadores[i]->fichasPerPlayer[j]->value[1] == k) {
					return i;
				}
			}
		}
	}
}

int SelectFicha(Player **jugadores, int pos) {
	int ficha = 0;
	printf("Jugador %d\n", pos + 1);
	for(int j = 0; j < 7; j++) {
		printf("[%d] %d - %d", j, jugadores[pos]->fichasPerPlayer[j]->value[0], jugadores[pos]->fichasPerPlayer[j]->value[1]);
		printf("\n");
	}
	scanf("%d", &ficha);
	ClearBuffer();
	return ficha;
}

void UpdateTablero(Tablero **tablero, int size, Player **jugador, int fichaIndex, int pos, int cant, int lado) {
    Ficha *fichaSeleccionada = jugador[pos]->fichasPerPlayer[fichaIndex];

    // Aumentar el tamaño del arreglo
    (*tablero)->fichasEnTablero = realloc((*tablero)->fichasEnTablero, ((*tablero)->cantidad + 1) * sizeof(Ficha*));

    // Mover fichas si se inserta a la izquierda
    if (lado == 0) {
        for (int i = (*tablero)->cantidad; i > 0; i--) {
            (*tablero)->fichasEnTablero[i] = (*tablero)->fichasEnTablero[i - 1];
        }
        (*tablero)->fichasEnTablero[0] = malloc(sizeof(Ficha));
        (*tablero)->fichasEnTablero[0]->value[0] = fichaSeleccionada->value[0];
        (*tablero)->fichasEnTablero[0]->value[1] = fichaSeleccionada->value[1];
    } else { // Insertar a la derecha
        (*tablero)->fichasEnTablero[(*tablero)->cantidad] = malloc(sizeof(Ficha));
        (*tablero)->fichasEnTablero[(*tablero)->cantidad]->value[0] = fichaSeleccionada->value[0];
        (*tablero)->fichasEnTablero[(*tablero)->cantidad]->value[1] = fichaSeleccionada->value[1];
    }

    (*tablero)->cantidad++;

    // Mostrar tablero
    printf("\nTablero actual:\n");
    for (int i = 0; i < (*tablero)->cantidad; i++) {
        printf("[%d-%d] ", (*tablero)->fichasEnTablero[i]->value[0], (*tablero)->fichasEnTablero[i]->value[1]);
    }
    printf("\n");

    // Eliminar ficha del jugador
    free(jugador[pos]->fichasPerPlayer[fichaIndex]);
    for (int i = fichaIndex; i < cant - 1; i++) {
        jugador[pos]->fichasPerPlayer[i] = jugador[pos]->fichasPerPlayer[i + 1];
    }

    Ficha **nuevoArreglo = realloc(jugador[pos]->fichasPerPlayer, (cant - 1) * sizeof(Ficha*));
    if (nuevoArreglo) {
        jugador[pos]->fichasPerPlayer = nuevoArreglo;
    } else {
        fprintf(stderr, "Error: No se pudo redimensionar el arreglo de fichas.\n");
    }
}
