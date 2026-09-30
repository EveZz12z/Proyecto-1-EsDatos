/* Autor: Pablo Serón */

#include <stdio.h>

#include "canciones.h"
#include "exportacion.h"

/**
 * @brief Exporta el catalogo a un archivo CSV
 *
 * @param catalogo - arreglo de canciones a exportar
 * @param total - cantidad de canciones en catalogo[]
 * @param ruta - nombre del archivo de salida
 * @return int - canciones escritas o -1 en el caso de haber parametros invalidos
 */            
int exportar_catalogo_csv(const Cancion catalogo[], int total, const char ruta[])
{
    if (catalogo == NULL || ruta == NULL || total < 0)
    {
        return -1;
    }

    //"w" crea el archivo o lo sobreescribe si este ya existe
    FILE *archivo = fopen(ruta, "w");
    if (archivo == NULL)
    {
        return -1;
    }

    //Fila de encabezado
    fprintf(archivo, "id,título,artista,album,genero,duracion_seg,año,n_reproducciones\n");

    //Una linea por cancion
    for (int i = 0; i < total; i++)
    {
        fprintf(archivo, "%d,%s,%s,%s,%s,%d,%d,%d\n",
                catalogo[i].id,
                catalogo[i].titulo,
                catalogo[i].artista,
                catalogo[i].album,
                catalogo[i].genero,
                catalogo[i].duracion_seg,
                catalogo[i].anho,
                catalogo[i].num_reproducciones);
    }

    //fclose puede fallar si el disco llegase a estar lleno
    if (fclose(archivo) != 0)
    {
        return -1;
    }

    return total;
}