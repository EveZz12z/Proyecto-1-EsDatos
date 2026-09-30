/* Autor: Pablo Serón */

#include <stdio.h>

#include "canciones.h"
#include "catalogo.h"
#include "importacion.h"
#include "exportacion.h"

#define LARGO_LINEA 512

/**
 * @brief Indica si un archivo existe y si se puede leer
 *
 * @param ruta - nombre del archivo
 * @return int - 1 si existe, 0 si no existe o la ruta es NULL
 */
int archivo_existe(const char ruta[])
{
    if (ruta == NULL)
    {
        return 0;
    }

    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL)
    {
        return 0;
    }

    fclose(archivo);
    return 1;
}

/**
 * @brief Carga las canciones de un archivo CSV en el arreglo catalogo[]
 *
 * @param ruta - nombre del archivo CSV a leer
 * @param catalogo - arreglo de salida
 * @param max_canciones - capacidad maxima de catalogo[]
 * @return int - canciones cargadas, o -1 si hay parametros invalidos
 */
int cargar_catalogo_csv(const char ruta[], Cancion catalogo[], int max_canciones)
{
    if (ruta == NULL || catalogo == NULL || max_canciones <= 0)
    {
        return -1;
    }

    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL)
    {
        return -1;
    }

    char linea[LARGO_LINEA];
    int cargadas = 0;

    //Leemos y descartamos la fila de encabezado
    if (fgets(linea, sizeof(linea), archivo) == NULL)
    {
        fclose(archivo);
        return 0;       //archivo vacio
    }

    //Una iteracion por cancion
    while (cargadas < max_canciones && fgets(linea, sizeof(linea), archivo) != NULL)
    {
        Cancion c;

        //%63[^,] lee hasta 63 caracteres sin incluir comas (TITULO_MAX - 1)
        //%31[^,] es igual pero para el genero (GENERO_MAX - 1)
        int leidos = sscanf(linea, "%d,%63[^,],%63[^,],%63[^,],%31[^,],%d,%d,%d",
                            &c.id, c.titulo, c.artista, c.album, c.genero,
                            &c.duracion_seg, &c.anho, &c.num_reproducciones);

        //Si no se leyeron los 8 campos la linea se tomara como mal formada
        if (leidos != 8)
        {
            continue;
        }

        //Solo guardamos canciones con "valores razonables"
        if (validar_cancion(&c))
        {
            catalogo[cargadas] = c;
            cargadas++;
        }
    }

    fclose(archivo);
    return cargadas;
}

/**
 * @brief Prepara el catalogo al iniciar el programa
 *        Si el CSV existe este se carga
 *        En el caso de no ser asi generara uno nuevo y lo guarda
 *
 * @param catalogo - arreglo de salida
 * @param n_generar - cuantas canciones generar si el CSV no existe
 * @param ruta - nombre del CSV (ej. ARCHIVO_CATALOGO)
 * @return int - canciones disponibles en catalogo[], o -1 si hay un error
 */
int iniciar_catalogo(Cancion catalogo[], int n_generar, const char ruta[])
{
    if (catalogo == NULL || ruta == NULL)
    {
        return -1;
    }

    //Si el .csv existe lo leemos
    if (archivo_existe(ruta))
    {
        int cargadas = cargar_catalogo_csv(ruta, catalogo, MAX_CANCIONES);

        if (cargadas > 0)
        {
            return cargadas;
        }
        //Si el archivo estaba vacio generamos uno nuevo
    }

    //En el caso de que no exista el .csv "utilizable" (no tenga el catalogo), generamos el catalogo
    int generadas = generar_catalogo(catalogo, n_generar);
    if (generadas < 0)
    {
        return -1;
    }

    //Lo guardamos para que la proxima ejecucion lo lea
    if (exportar_catalogo_csv(catalogo, generadas, ruta) < 0)
    {
        return -1;
    }

    return generadas;
}