#ifndef ordenamiento_h
#define ordenamiento_h

#include "canciones.h" 
#include "catalogo.h"  


void selection_sort(Cancion arr[], int n, int campo);

void mostrar_catalogo(Cancion arr[], int n);

void merge(Cancion arr[], Cancion aux[], int izq, int m, int der, int campo);

void mergeSort_recursivo(Cancion arr[], Cancion aux[], int izq, int der, int campo);

void mergeSort(Cancion arr[], int n, int campo);

int busqueda_binaria_id(Cancion arr[], int izq, int der, int x);

int busqueda_binaria_titulo_artista(Cancion arr[], int izq, int der, char* x, int campo);

void obtener_canciones_artista(Cancion arr[], int n, char artista[]);

void ranking(Cancion arr[], int n, int top);

void obtener_cancion_mas_escuchada(Cancion arr[], int n, int campo, char texto[]);



#endif // !ordenamiento_h