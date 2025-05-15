/* Ramon Manriquez Guerrero 2210376
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
	int cantidad;
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
Tablero *InitializeTablero();
Ficha **Initialize(int);
int Repartir(Ficha**, Player**, int, int);
Player **InitializePlayers(int);
Ficha **Desplazamiento(Ficha **, int, int);
void ImpresionFichas(Ficha **, int);


// Prototipos del juego
int CheckWinner(Player**, int);
int StarterPlayer(Player**, int);
int SelectFicha(Player **, int);
void UpdateTablero(Tablero *, Player **, int , int, int);
int CheckPieza(Player**, int, int, Tablero*);
int SearchPieza(Player**, Tablero*, int);
void EatPieza(Player **, Ficha ***, Tablero *, int , int *);
void ShowTablero(Tablero*);

// Prototipo para terminar
void FreeMemory(Ficha **, Player **, Tablero *, int, int);

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
	Tablero *tablero = InitializeTablero();

	// Repartir fichas
	cantidad = Repartir(fichas, jugadores, py, cantidad);

	// Impresion de fichas sin agarrar
	// ImpresionFichas(fichas, cantidad);

	// Juego Domino

	// Decidir jugador inicial
	int pos = StarterPlayer(jugadores, py);
	printf("\nComienza el jugador %d!\n", pos + 1);

	// Establecer orden
	int orden[py];
	for(int i = 0; i < py; i++) {
		orden[i] = (pos + i) % py; 
		printf("%d.- Jugador %d\n", i + 1, orden[i] + 1);
	}

	int turno = orden[0];

	while(!CheckWinner(jugadores, py)) {
		// Buscar ficha
		int i = 0;
		turno = (turno + i) % 4;
		if(!SearchPieza(jugadores, tablero, turno)) {
			// Si no hay ficha para jugar entonces se come una ficha
			EatPieza(jugadores, &fichas, tablero, turno, &cantidad);
		}
		// Seleccion de ficha a jugar del jugador
		int ficha = SelectFicha(jugadores, turno);
		// Comprobacion de ficha
		int lado = CheckPieza(jugadores, turno, ficha, tablero);
		// Si CheckPieza retorna 0 entonces la ficha seleccionada no es valida
		while(!lado) {
			ShowTablero(tablero);
			printf("Selecciona otra ficha\n");
			ficha = SelectFicha(jugadores, turno);
			lado = CheckPieza(jugadores, turno, ficha, tablero);
		}
		// Actualizacion del tablero
		UpdateTablero(tablero, jugadores, ficha, turno, lado);

		printf("\nTurno finalizado\n\n");
		i++;
	}

	// Liberacion de memoria
	FreeMemory(fichas, jugadores, tablero, cantidad, py);
}

Player **InitializePlayers(int py) {
	//printf("\nInicializando jugadores\n");
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

Tablero *InitializeTablero() {
	Tablero *tablero = (Tablero*)malloc(sizeof(Tablero));
	tablero->fichasEnTablero = NULL;
	tablero->cantidad = 0;
	return tablero;
}

Ficha **Initialize(int cantidad) {
	//printf("\nInicializando Fichas\n");
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
    (*fichas)->cantidad = 28;
	return fichas;
}

int Random(int cantidad) {
	return rand() % cantidad;
}

int Repartir(Ficha **fichas, Player **jugador, int py, int cantidad) {
    //printf("\nRepartiendo Fichas\n");
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
    printf("\nFichas sin jugar: %d\n", cantidad);
    for (int i = 0; i < cantidad; i++) {
        printf("%d - %d\n", fichas[i]->value[0], fichas[i]->value[1]);
    }
	} else {
    printf("\nNo hay fichas sin jugar.\n");
	}
}

void FreeMemory(Ficha **fichas, Player **jugadores, Tablero *tablero, int cantidad, int py) {
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
	/*
	for(int i = 0; i < tablero->cantidad; i++) {
		free(tablero->fichasEnTablero);
	}
	*/
	free(tablero->fichasEnTablero);
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
	printf("\nJugador %d\n", pos + 1);
	for(int j = 0; j < jugadores[pos]->cantidad; j++) {
		printf("[%d] %d - %d", j, jugadores[pos]->fichasPerPlayer[j]->value[0], jugadores[pos]->fichasPerPlayer[j]->value[1]);
		printf("\n");
	}
	printf("\nSelecciona tu ficha a jugar\n>> ");
	scanf("%d", &ficha);
	ClearBuffer();
	return ficha;
}

void UpdateTablero(Tablero *tablero, Player **jugador, int fichaIndex, int pos, int lado) {

    // Aumentar el tamaño del arreglo del tablero
    Ficha **aux = NULL;
    while(!aux) {
		aux = realloc(tablero->fichasEnTablero, (tablero->cantidad + 1) * sizeof(Ficha*));
	}
    tablero->fichasEnTablero = aux;

    // Inserta al inicio o al final
    if (lado == 1) {
    	for (int i = tablero->cantidad; i > 0; i--) {
        	tablero->fichasEnTablero[i] = tablero->fichasEnTablero[i - 1];
    	}
    	tablero->fichasEnTablero[0] = (Ficha*)malloc(sizeof(Ficha));
    	*(tablero->fichasEnTablero[0]) = *(jugador[pos]->fichasPerPlayer[fichaIndex]);

    	if (tablero->fichasEnTablero[0]->value[1] != tablero->fichasEnTablero[1]->value[0] && tablero->cantidad > 0) {
        	int aux = tablero->fichasEnTablero[0]->value[0];
        	tablero->fichasEnTablero[0]->value[0] = tablero->fichasEnTablero[0]->value[1];
        	tablero->fichasEnTablero[0]->value[1] = aux;
    	}
	} else {
    	tablero->fichasEnTablero[tablero->cantidad] = malloc(sizeof(Ficha));
    	*(tablero->fichasEnTablero[tablero->cantidad]) = *(jugador[pos]->fichasPerPlayer[fichaIndex]);
    	if (tablero->fichasEnTablero[tablero->cantidad - 1]->value[1] != tablero->fichasEnTablero[tablero->cantidad]->value[0] && tablero->cantidad > 0) {
        	int aux = tablero->fichasEnTablero[tablero->cantidad]->value[0];
        	tablero->fichasEnTablero[tablero->cantidad]->value[0] = tablero->fichasEnTablero[tablero->cantidad]->value[1];
        	tablero->fichasEnTablero[tablero->cantidad]->value[1] = aux;
    	}
	}


    tablero->cantidad++;

   // Imprimimos el tablero
   printf("\nTablero Actual\n");
	for(int i = 0; i < tablero->cantidad; i++) {
		printf("[%d-%d] ", tablero->fichasEnTablero[i]->value[0], tablero->fichasEnTablero[i]->value[1]);
   }
   printf("\n");

   // Eliminar ficha del jugador
   //printf("\nEliminando ficha del jugador\n");
   free(jugador[pos]->fichasPerPlayer[fichaIndex]);
   for(int i = fichaIndex; i < jugador[pos]->cantidad - 1; i++) {
		jugador[pos]->fichasPerPlayer[i] = jugador[pos]->fichasPerPlayer[i + 1];
   }

   // Decrementar cantidad de fichas del jugador
   jugador[pos]->cantidad--;

   // Realocacion de memoria
   //printf("\nRealocando memoria\n");
   aux = NULL;
   while(!aux) {
		aux = realloc(jugador[pos]->fichasPerPlayer, jugador[pos]->cantidad * sizeof(Ficha*));
   }
   jugador[pos]->fichasPerPlayer = aux;
   //printf("\nMemoria Realocada\n");
}

int CheckPieza(Player **jugador, int pos, int ficha, Tablero *tablero) {
	if (tablero->cantidad == 0) {
		return 1; // Primer turno: se puede jugar, por default a la izquierda
	}

	// Obtener valores de la ficha del jugador
	int jugadorLado0 = jugador[pos]->fichasPerPlayer[ficha]->value[0];
	int jugadorLado1 = jugador[pos]->fichasPerPlayer[ficha]->value[1];

	// Obtener valores de los extremos del tablero
	int tableroIzq = tablero->fichasEnTablero[0]->value[0];
	int tableroDer = tablero->fichasEnTablero[tablero->cantidad - 1]->value[1];

	// Banderas
	int puedeIzquierda = 0;
	int puedeDerecha = 0;
	int opc;

	// Comparar con izquierda
	if (jugadorLado0 == tableroIzq || jugadorLado1 == tableroIzq) {
		puedeIzquierda = 1;
	}

	// Comparar con derecha
	if (jugadorLado0 == tableroDer || jugadorLado1 == tableroDer) {
		puedeDerecha = 1;
	}

	printf("Puede izquierda: %d\n", puedeIzquierda);
	printf("Puede derecha : %d\n", puedeDerecha);

	// Ambos lados posibles
	if (puedeIzquierda && puedeDerecha) {
		do {
			printf("\n¿De qué lado quiere jugar la ficha?\n [1] Izquierda [2] Derecha\n>> ");
			scanf("%d", &opc);
			ClearBuffer();
		} while (opc != 1 && opc != 2);
		return opc; // 1 = izquierda, 2 = derecha
	}

	// Solo un lado
	if (puedeIzquierda) return 1;
	if (puedeDerecha) return 2;

	return 0; // No se puede jugar
}

int SearchPieza(Player **jugador, Tablero *tablero, int pos) {
	if (tablero->cantidad == 0)
		return 1; // Primer turno, puede jugar cualquier ficha

	int izquierda = tablero->fichasEnTablero[0]->value[0];
	int derecha = tablero->fichasEnTablero[tablero->cantidad - 1]->value[1];

	for (int i = 0; i < jugador[pos]->cantidad; i++) {
		int v0 = jugador[pos]->fichasPerPlayer[i]->value[0];
		int v1 = jugador[pos]->fichasPerPlayer[i]->value[1];

		if (v0 == izquierda || v1 == izquierda || v0 == derecha || v1 == derecha) {
			return 1; // Puede jugar
		}
	}
	return 0; // No puede jugar
}


void EatPieza(Player **jugador, Ficha ***fichas, Tablero *tablero, int pos, int *cantidad) {
	if (*cantidad <= 0) {
		printf("No hay más fichas para tomar.\n");
		return;
	}

	// Aumentar el tamaño del arreglo del jugador
	Ficha **aux = NULL;
	while(!aux) {
		aux = realloc(jugador[pos]->fichasPerPlayer, (jugador[pos]->cantidad + 1) * sizeof(Ficha*));
	}
	jugador[pos]->fichasPerPlayer = aux;

	// Tomar una ficha aleatoria
	int indexFicha = Random(*cantidad);
	jugador[pos]->fichasPerPlayer[jugador[pos]->cantidad] = malloc(sizeof(Ficha));
	*(jugador[pos]->fichasPerPlayer[jugador[pos]->cantidad]) = *(*fichas)[indexFicha];
	jugador[pos]->cantidad++;

	// Eliminar ficha del montón
	free((*fichas)[indexFicha]);
	for (int i = indexFicha; i < *cantidad - 1; i++) {
		(*fichas)[i] = (*fichas)[i + 1];
	}
	*cantidad -= 1;
	*fichas = realloc(*fichas, (*cantidad) * sizeof(Ficha*));

	// Si aún no puede jugar, repetir
	if (!SearchPieza(jugador, tablero, pos)) {
		EatPieza(jugador, fichas, tablero, pos, cantidad);
	}
}


void ShowTablero(Tablero *tablero) {
	printf("\nTablero Actual\n");
	for(int i = 0; i < tablero->cantidad; i++) {
		printf("[%d-%d] ", tablero->fichasEnTablero[i]->value[0],tablero->fichasEnTablero[i]->value[1]);
	}
	printf("\n");
}	
