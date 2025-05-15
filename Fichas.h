// Fichas.h

#ifndef _FICHAS_H
#define _FICHAS_H

typedef struct {
    int value[2];
} Ficha;

Ficha **Initialize(int cantidad);
Ficha **Desplazamiento(Ficha **, int, int);
void ImpresionFichas(Ficha **, int);

#endif

