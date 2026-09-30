

/*Prototipos de las funciones de gestión de catálogo:
generación aleatoria, validación, mezcla y consultas por género/artista.*/

/*Nota "infdef" y "endif" sirven para que el contenido dentro de un archivo.h 
se incluya solo una vez por archivo compilado esto es para que no se reciba por asi decirlo
una misma informacion 2 veces por lo que lo haye una buena practica para que no haya
errores de compilacion (mas cuando mas de una persona va a trabajar con este archivo y los demas)*/

/* Autor: Pablo Serón */

#ifndef CATALOGO_H
#define CATALOGO_H

#include "canciones.h"


//Campos por los que se puede ordenar o buscar (escencial para el BubbleSort)
typedef enum {
    CAMPO_ID,
    CAMPO_TITULO,
    CAMPO_ARTISTA,
    CAMPO_ALBUM,
    CAMPO_GENERO,
    CAMPO_DURACION,
    CAMPO_ANHO,
    CAMPO_REPRODUCCIONES
} CampoCancion;

/* Compara dos canciones segun un campo.
   Retorna negativo si a < b, 0 en el caso de ser iguales, positivo si a > b. */
int comparar_canciones(const Cancion *a, const Cancion *b, CampoCancion campo);

/* Ordena catalogo[] de menor a mayor por el campo indicado (Bubble Sort).
   Retorna 0 si ordeno correctamente o -1 si hay parametros invalidos. */
int BubbleSort(Cancion catalogo[], int total, CampoCancion campo);

/*Genera n canciones aleatorias dentro de catalogo[]
    Retorna la cantidad de canciones generadas o -1 en el caso que n no sea valido
    (n <= 0 o n > MAX_CANCIONES)*/
int generar_catalogo(Cancion catalogo[], int n);


int validar_cancion(const Cancion *c);

int generar_una_cancion(Cancion *c, int id);

void mezclar_catalogo(Cancion catalogo[], int total);

int listar_artistas(const Cancion catalogo[], int total, char artistas[][ARTISTA_MAX], int max_artistas);

int contar_por_genero(const Cancion catalogo[], int total, const char genero[]);

int listar_por_genero(const Cancion catalogo[], int total, const char genero[],int indices[], int max_resultados);

int listar_generos(const Cancion catalogo[], int total, char generos[][GENERO_MAX], int max_generos);

int busqueda_binaria(const Cancion catalogo[], int total, const Cancion *clave, CampoCancion campo);

#endif /* CATALOGO_H */