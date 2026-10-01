#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "canciones.h"
#include "catalogo.h"
#include "importacion.h"

#define ARCHIVO_CATALOGO    "catalogo.csv"
#define CANCIONES_INICIALES 200     

int main(void)
{
    //Se llama una sola (para comenzar a generar el catalogo) y se inicializan aquellos num aleatorios
    //(Lo inicializamos en el main para que no se repitan los mismos numeros)
    srand((unsigned)time(NULL));

    Cancion catalogo[MAX_CANCIONES];

    //Si el CSV existe lo lee; si no, genera el catalogo y lo guarda
    int total = iniciar_catalogo(catalogo, CANCIONES_INICIALES, ARCHIVO_CATALOGO);
    if (total < 0)
    {
        fprintf(stderr, "Error: A ocurrido un error al cargar el catalogo\n");
        return 1;
    }

    printf("Catalogo listo: %d canciones\n", total);

    //Provisorio: muestra las primeras 5 para comprobar que funciona
    for (int i = 0; i < 5 && i < total; i++)
    {
        printf("  id=%d | %s | %s | %s | %s | %d s | %d | %d rep\n",
               catalogo[i].id, catalogo[i].titulo, catalogo[i].artista,
               catalogo[i].album, catalogo[i].genero, catalogo[i].duracion_seg,
               catalogo[i].anho, catalogo[i].num_reproducciones);
    }

    return 0;
}