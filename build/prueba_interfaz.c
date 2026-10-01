#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prueba_interfaz.h"
#include "ordenamiento.h"


void menu(cancion arr[], int n) {
	
	int seleccion = 0;
	printf("Reproductor musical\n");
	printf("======================================================\n");
	printf("Seleccione que desea: \n");
	printf("Ingrese 1 - para buscar una cancion\n");
	printf("Ingrese 2 - para consultar un top de canciones\n");
	printf("Ingrese 3 - para escuchar la cancione mas popular\n");
	printf("======================================================\n");

	printf("\nIngrese su seleccion: ");
	scanf("%d", &seleccion);
	printf("\n");

	switch (seleccion)
	{
	case 1:
		buscador_de_canciones(arr, n);
		break;
	case 2:
		top_canciones(arr, n);
		break;
	case 3:
		cancion_mas_escuchada(arr, n);
		break;
	default:
		printf("Opcion no valida\n");
		break;
	}
}

void buscador_de_canciones(cancion arr[], int n) {
	int seleccion = 0;
	int id = 0;
	char titulo[50];
	char artista[50];
	int posicion;

	printf("Buscador de canciones \n");
	printf("ingrese 1-para buscar por id \n");
	printf("ingrese 2-para buscar por titulo \n");
	printf("ingrese 3-para buscar por artista \n");
	printf("Ingrese 4-para omitir");
	printf("\nIngrese su seleccion: ");
	scanf("%d", &seleccion);

	if (seleccion == 1) {

		printf("\nIngrese el ID que quiere buscar: ");
		scanf("%d", &id);

		selection_sort(arr, n, 1);
		posicion = busqueda_binaria_id(arr, 0, n - 1, id);

		if (posicion != -1) {
			printf("Cancion encontrada: %s - %s\n",
				arr[posicion].titulo,
				arr[posicion].artista);
		}
		else {
			printf("ID no encontrado\n");
		}
	}
	else if (seleccion == 2) {
		printf("\nIngrese el titulo que quiere buscar: ");
		scanf(" %29[^\n]", titulo);

		selection_sort(arr, n, 5);
		posicion = busqueda_binaria_titulo_artista(arr, 0, n - 1, titulo, 1);

		if (posicion != -1) {
			printf("Cancion encontrada: %s - %s\n",
				arr[posicion].titulo,
				arr[posicion].artista);
		}
		else {
			printf("Titulo no encontrado\n");
		}
	}
	else if (seleccion == 3) {
		printf("\nIngrese el Artista que quiere buscar: ");
		scanf(" %29[^\n]", artista);

		obtener_canciones_artista(arr, n, artista);
	}

	if (scanf("%d", &seleccion) != 1) {
    printf("Entrada invalida\n");
    return;
}
}

void top_canciones(cancion arr[], int n) {
	int top = 0;
	printf("Ingrese que top de reproducciones quiere consultar: ");
	scanf("%d", &top);

	ranking(arr, n, top);
}

void cancion_mas_escuchada(cancion arr[], int n) {
	int seleccion = 0;
	char artista[50];
	char genero[50];

	printf("Buscador de canciones mas escuchdas \n");
	printf("ingrese: 1-para buscar por artista \n");
	printf("ingrese: 2-para buscar por genero \n");
	printf("\nIngrese su seleccion: ");
	scanf("%d", &seleccion);

	if (seleccion == 1) {

		printf("Ingrese un artista: ");
		scanf(" %49[^\n]", artista);

		obtener_cancion_mas_escuchada(arr, n, 1, artista);
	}
	else if (seleccion == 2) {
		printf("Ingrese un genero: ");
		scanf(" %49[^\n]", genero);

		obtener_cancion_mas_escuchada(arr, n, 2, genero);
	}
}