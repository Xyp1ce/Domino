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
	int cantidad;
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
void UpdateTablero(Tablero **, Player **, int , int, int);
int CheckPieza(Player**, int, int, Tablero**);

// Prototipo para terminar
void FreeMemory(Ficha **, Player **, Tablero**, int, int);

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
	int ficha = SelectFicha(jugadores, orden[0]);
	int lado = CheckPieza(jugadores, orden[0], ficha, tablero);
	UpdateTablero(tablero, jugadores, ficha, orden[0], lado);

	/*while(!CheckWinner(jugadores, py)) {
		
	}*/

	// Liberacion de memoria
	FreeMemory(fichas, jugadores, tablero, cantidad, py);
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
		jugador[i]->cantidad = 7;
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

void FreeMemory(Ficha **fichas, Player **jugadores, Tablero **tablero, int cantidad, int py) {

	// Liberacion de jugadores
	for(int i = 0; i < py; i++) {
		for(int j = 0; j < jugadores[i]->cantidad; j++) {
			free(jugadores[i]->fichasPerPlayer[j]);
		}
		free(jugadores[i]->fichasPerPlayer);
		free(jugadores[i]);
	}
	free(jugadores);
	
	// Liberacion de fichas
	for(int i = 0; i < cantidad; i++) {
		free(fichas[i]);
	}
	free(fichas);

	// Liberacion de tablero
	for(int i = 0; i < (*tablero)->cantidad; i++) {
		free((*tablero)->fichasEnTablero[i]);
	}
	free((*tablero)->fichasEnTablero);
	free(tablero);
}

int CheckWinner(Player **jugadores, int py) {
	for(int i = 0; i < py; i++) {
		if(jugadores[i]->cantidad == 0) {
			return i; // Se regresa el index del ganador
		}
	}
	return 0; // Mientras sea 0 el juego continua
}

int StarterPlayer(Player **jugadores, int py) {
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

void UpdateTablero(Tablero **tablero, Player **jugador, int fichaIndex, int pos, int lado) {

    // Aumentar el tamaño del arreglo del tablero
    Ficha **aux = NULL;
    while(!aux) {
		aux = realloc((*tablero)->fichasEnTablero, ((*tablero)->cantidad + 1) * sizeof(Ficha*));
	}
    (*tablero)->fichasEnTablero = aux;

    // Inserta al inicio o al final
    if (lado == 1) { // Inserta al inicio
        for (int i = (*tablero)->cantidad; i > 0; i--) {
            (*tablero)->fichasEnTablero[i] = (*tablero)->fichasEnTablero[i - 1];
        }
		(*tablero)->fichasEnTablero[0] = malloc(sizeof(Ficha));
        *((*tablero)->fichasEnTablero[0]) = *(jugador[pos]->fichasPerPlayer[fichaIndex]);
    } else { // Inserta al final
		(*tablero)->fichasEnTablero[(*tablero)->cantidad] = malloc(sizeof(Ficha));
        *((*tablero)->fichasEnTablero[(*tablero)->cantidad]) = *(jugador[pos]->fichasPerPlayer[fichaIndex]);
    }

    (*tablero)->cantidad++;

   // Imprimimos el tablero
   printf("Tablero Actual\n");
   for(int i = 0; i < (*tablero)->cantidad; i++) {
		printf("[%d-%d] ", (*tablero)->fichasEnTablero[i]->value[0], (*tablero)->fichasEnTablero[i]->value[1]);
   }
   printf("\n");

   // Eliminar ficha del jugador
   printf("Eliminando ficha del jugador\n");
   free(jugador[pos]->fichasPerPlayer[fichaIndex]);
   for(int i = fichaIndex; i < jugador[pos]->cantidad - 1; i++) {
		jugador[pos]->fichasPerPlayer[i] = jugador[pos]->fichasPerPlayer[i + 1];
   }

   // Decrementar cantidad de fichas del jugador
   jugador[pos]->cantidad--;

   // Realocacion de memoria
   printf("Realocando memoria\n");
   aux = NULL;
   while(!aux) {
		aux = realloc(jugador[pos]->fichasPerPlayer, jugador[pos]->cantidad * sizeof(Ficha*));
   }
   jugador[pos]->fichasPerPlayer = aux;
   printf("Memoria Realocada\n");

   // Impresion de las fichas del jugador fines demostrativos
   for(int i = 0; i < jugador[pos]->cantidad; i++) {
		printf("%d - %d\n", jugador[pos]->fichasPerPlayer[i]->value[0], jugador[pos]->fichasPerPlayer[i]->value[1]);
   }
}

int CheckPieza(Player **jugador, int pos, int ficha, Tablero **tablero) {
	if((*tablero)->cantidad == 0) {
		return 1; // Primer turno: se puede jugar
	}

	// Banderas de posibilidad
	int left = 0, right = 0;
	int opc;

	// Valores de la ficha del jugador
	int jugadorLado1 = jugador[pos]->fichasPerPlayer[ficha]->value[0];
	int jugadorLado2 = jugador[pos]->fichasPerPlayer[ficha]->value[1];

	// Comparar con la última ficha del tablero (lado derecho)
	int tableroDer1 = (*tablero)->fichasEnTablero[(*tablero)->cantidad - 1]->value[0];
	int tableroDer2 = (*tablero)->fichasEnTablero[(*tablero)->cantidad - 1]->value[1];

	if (jugadorLado1 == tableroDer1 || jugadorLado1 == tableroDer2 || jugadorLado2 == tableroDer1 || jugadorLado2 == tableroDer2) {
		right = 1;
	}

	// Comparar con la primera ficha del tablero (lado izquierdo)
	int tableroIzq1 = (*tablero)->fichasEnTablero[0]->value[0];
	int tableroIzq2 = (*tablero)->fichasEnTablero[0]->value[1];

	if (jugadorLado1 == tableroIzq1 || jugadorLado1 == tableroIzq2 || jugadorLado2 == tableroIzq1 || jugadorLado2 == tableroIzq2) {
		left = 1;
	}

	// Se puede jugar en ambos extremos
	if (left && right) {
		do {
			printf("¿De qué lado quiere jugar la ficha?\n [1] Izquierda [2] Derecha\n");
			scanf("%d", &opc);
			ClearBuffer();
		} while (opc != 1 && opc != 2);
		return opc; // 1 para izquierda, 2 para derecha
	}

	// Solo se puede jugar en un extremo
	if (left) 
		return 1;
	if (right) 
		return 2;

	return 0; // No se puede jugar
}
