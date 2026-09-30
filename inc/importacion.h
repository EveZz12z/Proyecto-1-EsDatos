/* Autor: Pablo Serón */

#ifndef IMPORTACION_H
#define IMPORTACION_H

#include "canciones.h"

//Retornara 1 si el archivo existe y 0 si no
int archivo_existe(const char ruta[]);

/* Carga un CSV en catalogo[] (máx. max_canciones).
   Retornara la cantidad de canciones cargadas o-1 en el caso de haber parametros
   invalidos (como se menciona en los demas archivos) */
int cargar_catalogo_csv(const char ruta[], Cancion catalogo[], int max_canciones);

int iniciar_catalogo(Cancion catalogo[], int n_generar, const char ruta[]);

#endif /* IMPORTACION_H */