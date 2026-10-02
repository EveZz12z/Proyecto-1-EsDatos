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

/*Genera n canciones aleatorias dentro de catalogo[]
    Retorna la cantidad de canciones generadas o -1 en el caso que n no sea valido
    (n <= 0 o n > MAX_CANCIONES)*/
int generar_catalogo(Cancion catalogo[], int n);

/* Verifica la duracion, anho y num_reproducciones de la cancion esten dentro
   de los rangos de canciones.h*/
int validar_cancion(const Cancion *c);

/* Rellena la cancion con sus correspondientes datos aleatorios (titulo y album formados con
   palabras al azar, artista y genero elegidos desde arreglos) ademas se le asigna un id*/
int generar_una_cancion(Cancion *c, int id);

/* Mezcla aleatoriamente las primeras total canciones de catalogo[]*/
void mezclar_catalogo(Cancion catalogo[], int total);

/* Guarda en el arreglo artistas[] los nombres de artista distintos del catalogo, sin repetir estos*/
int listar_artistas(const Cancion catalogo[], int total, char artistas[][ARTISTA_MAX], int max_artistas);

/* Cuenta cuantas canciones del arreglo catalogo[] pertenecen al mismo genero
   Retorna la cantidad (0 si no hay ninguna) o -1 si hay parametros invalidos. */
int contar_por_genero(const Cancion catalogo[], int total, const char genero[]);

/* Guarda en indices[] las posiciones de catalogo[] cuyas canciones son del
   genero correspondiente */
int listar_por_genero(const Cancion catalogo[], int total, const char genero[],int indices[], int max_resultados);

/* Guarda en generos[] los generos distintos del catalogo sin repetirlos
   Escribe a lo mas max_generos sus nombres
   Retorna la cantidad guardada o -1 si hay parametros invalidos. */
int listar_generos(const Cancion catalogo[], int total, char generos[][GENERO_MAX], int max_generos);

/* Crea una copia en memoria dinamica de catalogo[] (el llamador debe hacer free).
   Retorna NULL si hay parametros invalidos o falla malloc. */
Cancion *duplicar_catalogo(const Cancion catalogo[], int total);

/* Suma 1 a num_reproducciones de la cancion con ese id (busqueda lineal).
   Retorna 1 si la encontro o 0 si no existe (o hay parametros invalidos). */
int incrementar_reproducciones(Cancion catalogo[], int total, int id);

#endif /* CATALOGO_H */