
/*En este archivo.h se definira la estructura Cancion y 
las constantes compartidas por
todos los módulos del proyecto.*/

/*Nota "infdef" y "endif" sirven para que el contenido dentro de un archivo.h 
se incluya solo una vez por archivo compilado esto es para que no se reciba por asi decirlo
una misma informacion 2 veces por lo que lo haye una buena practica para que no haya
errores de compilacion (mas cuando mas de una persona va a trabajar con este archivo y los demas)*/
/**
 * @brief 
 * 
 */
#ifndef CANCIONES_H
#define CANCIONES_H

//Tamaños máximos de los campos de texto (este incluye el "\0" x si acaso :D)
#define TITULO_MAX   64
#define ARTISTA_MAX  64
#define ALBUM_MAX    64
#define GENERO_MAX   32

//Capacidad máxima del catálogo (arreglo estático)
#define MAX_CANCIONES 1000

// Rangos para validar los datos ya generados
#define DURACION_MIN_SEG   30
#define DURACION_MAX_SEG   900
#define ANHO_MIN           1950
#define ANHO_MAX           2026
#define REPRODUCCIONES_MAX 1000000

/* Autor: Pablo Serón */

//Representara las canciones del catalogo
/**
 * @brief 
 * 
 */
typedef struct _cancion {
    int  id;                        /* Único y autoincremental (segun lo pedido) */
    char titulo[TITULO_MAX];
    char artista[ARTISTA_MAX];
    char album[ALBUM_MAX];
    char genero[GENERO_MAX];
    int  duracion_seg;
    int  anho;
    int  num_reproducciones;
} Cancion;

#endif /* CANCIONES_H */