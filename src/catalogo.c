#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <time.h>       

#include "canciones.h" 
#include "catalogo.h"  

/* Autor: Pablo Serón */

/**
 * @brief Verifica que los campos numéricos de una canción estén dentro de los rangos permitidos.

 * @param c - puntero a la canción a validar
 * @return int si duracion, anho y reproducciones estan dentro de los rangos, 0 si alguno no lo esta
 */
int validar_cancion(const Cancion *c)
{

    //Entramos en el primer if para medir la duracion 
    //esta debe estar entre DURACION_MIN_SEG y DURACION_MAX_SEG
    //para evitar canciones con duraciones negativas o demasiado largas
    if(c->duracion_seg < DURACION_MIN_SEG || c->duracion_seg > DURACION_MAX_SEG)
    {
        return 0; //duracion fuera de rango
    }
    //Pasamos al segundo if con respecto al año
    //este debera estar entre los limites de ANHO_MIN y ANHO_MAX
    //Esto evitara años que no existen o futuros fuera de rango
    if(c->anho < ANHO_MIN || c->anho > ANHO_MAX) 
    {
        return 0; //anho fuera de rango
    }
    //Pasamos al ultimo if que limita las reproducciones
    //estas no podran ser negativas ni superar el maximo
    if(c->num_reproducciones < 0 || c->num_reproducciones > REPRODUCCIONES_MAX)
    {
        return 0; //reproducciones fuera de rango
    }

    return 1;//todos los campos numericos son validos

}

/**
 * @brief Mezcla aleatoriamente las canciones del catálogo
 * 
 * @param catalogo arreglo de canciones a mezclar
 * @param total cantidad de canciones válidas en catalogo[]
 */
void mezclar_catalogo(Cancion catalogo[], int total)
{
//Nota; Faltaria agregar un srand() en nustro archivo main

    for(int i = total - 1;i>0;i--)
    {

        int j = rand() % (i + 1);       //El indice sera aleatorio entre 0 y "i"
        Cancion temp = catalogo[i];     //Se intercambian
        catalogo[i] = catalogo[j];
        catalogo[j] = temp;

    }

}


/**
 * @brief Rellena una canción con datos aleatorios

 * @param c - puntero a la canción que se va a rellenar (salida)
 * @param id - identificador que se asigna a la canción
 * @return int 1 cuando la cancion fue generada (siempre; la validez de los rangos la comprueba en este caso generar_catalogo)
 */
int generar_una_cancion(Cancion *c, int id)
{

//Nota: usa snprintf para no desbordar los buffers de titulo y album.

    const char *artistas_disponibles[] =
    {
    "Los_Charros_de_Lumaco",
    "Canserbero",
    "Zúmbale_Primo",
    "Gipsy_Kings",
    "Duki",
    "Aventura",
    "Lit_Killah",
    "Milo_J"
    };

    int num_artistas = 8;

    const char *generos_disponibles[] = 
    {
        "Cumbia_Ranchera",
        "Rap",
        "Cumbia",
        "Salsa",
        "Trap",
        "Reggaeton",
        "Bachata",
    };

    int num_generos = 7;

    const char *palabras_titulo[] =
    {
        "Luna",
        "Fuego",
        "Silencio",
        "Camino",
        "Noche",
        "Sombra",
        "Cielo",
        "Ritmo"
    };
    
    int num_palabras = 8;

    //Asignamos el id recibido como parametro
    c->id = id;


//Esto combinara 2 palabras al azar del arreglo palabras_titulo
//(Esto no sera el titulo real de las canciones sino un dato generado
//(el enunciado permite formar texto aleatorio)
//Lo anterior lo aclaro para que no hayan confusiones, los titulos de las canciones no son reales o propios de los artistas
//snprintf en este caso respeta el tamaño maximo de TITULO_MAX y evita desbordar el mismo buffer propio
    snprintf(c->titulo, TITULO_MAX, "%s %s",
             palabras_titulo[rand() % num_palabras],
             palabras_titulo[rand() % num_palabras]);

//Volvemos a combinar 2 palabras al azar
    snprintf(c->album, ALBUM_MAX, "%s %s",
             palabras_titulo[rand() % num_palabras],
             palabras_titulo[rand() % num_palabras]);

//Aqui elegimos un artista desde el arreglo artistas_disponibles
    strcpy(c->artista, artistas_disponibles[rand() % num_artistas]);

//Elegimos un genro de el arreglo generos_disponibles
    strcpy(c->genero, generos_disponibles[rand() % num_generos]);

    //Definimos un numero aleatorio de duracion_seg que este permitido dentro de los rangos
    c->duracion_seg = DURACION_MIN_SEG + rand() % (DURACION_MAX_SEG - DURACION_MIN_SEG + 1);

    //Definimos el año/anho
    c->anho = ANHO_MIN + rand() % (ANHO_MAX - ANHO_MIN + 1);

    //Definimos el num_reproducciones
    c->num_reproducciones = rand() % (REPRODUCCIONES_MAX + 1);

    return 1;
}

/**
 * @brief Genera n canciones aleatorias
 * 
 * @param catalogo - arreglo de salida (capacidad mínima n)
 * @param n - cantidad de canciones a generar
 * @return int "n" (cantidad de canciones generadas) o -1 si n <= 0 o n > MAX_CANCIONES
 */
int generar_catalogo(Cancion catalogo[], int n)
{
    if (n <= 0 || n > MAX_CANCIONES)
    {
        return -1;
    }

    for (int i = 0; i < n; i++)
    {
        generar_una_cancion(&catalogo[i], i + 1);

        while (!validar_cancion(&catalogo[i]))
        {
            generar_una_cancion(&catalogo[i], i + 1);
        }
    }

    mezclar_catalogo(catalogo, n);

    return n;
}


/**
 * @brief Contara cuantas canciones pertenecen al genero
 * 
 * @param catalogo - arreglo de canciones
 * @param total - cantidad de canciones en catalogo[]
 * @param genero - genero a buscar
 * @return int cantidad de canciones del genero (0 si no hay ninguna) o -1 si hay parametros invalidos
 */
int contar_por_genero(const Cancion catalogo[], int total, const char genero[])
{
    if (catalogo == NULL || genero == NULL || total < 0)
    {
        return -1;
    }

    int contador = 0;

    for (int i = 0; i < total; i++)
    {
        if (strcmp(catalogo[i].genero, genero) == 0)
        {
            contador++;
        }
    }

    return contador;
}


/**
 * @brief Guardara en indices[] las posiciones (en este caso dentro de catalogo[])
 * las canciones que pertenecen a su respectivo genero
 * 
 * @param catalogo - arreglo de canciones
 * @param total  - cantidad de canciones en catalogo[]
 * @param genero - genero a buscar
 * @param indices - arreglo de salida con las posiciones encontradas
 * @param max_resultados - capacidad maxima de indices[]
 * @return int cantidad de posiciones guardadas en indices[] (0 si no hay ninguna) o -1 si hay parametros invalidos
 */
int listar_por_genero(const Cancion catalogo[], int total, const char genero[],int indices[], int max_resultados)
{
    if (catalogo == NULL || genero == NULL || indices == NULL ||
        total < 0 || max_resultados <= 0)
    {
        return -1;
    }

    int encontrados = 0;

    for (int i = 0; i < total && encontrados < max_resultados; i++)
    {
        if (strcmp(catalogo[i].genero, genero) == 0)
        {
            indices[encontrados] = i;
            encontrados++;
        }
    }

    return encontrados;
}


/**
 * @brief Guarda en el arreglo de artistas[] los mismos artistas del catalogo (sin repetirlos)
 * 
 * @param catalogo - arreglo de canciones
 * @param total - cantidad de canciones en catalogo[]
 * @param artistas - arreglo de salida con los nombres encontrados
 * @param max_artistas -  capacidad máxima de artistas[]
 * @return int - cantidad de artistas guardados o-1 en el caso de haber parametros invalidos
 */
int listar_artistas(const Cancion catalogo[], int total,char artistas[][ARTISTA_MAX], int max_artistas)
{
    
    if (catalogo == NULL || artistas == NULL || total < 0 || max_artistas <= 0)
    {
        return -1;
    }

    int cantidad = 0;

    //recorremos las canciones del catalogo
    for (int i = 0; i < total && cantidad < max_artistas; i++)
    {
        //Bandera que indica si el artista de esta cancion ya esta en la lista
        int ya_esta = 0;
        
        //recorre solo los artistas ya guardados
        for (int j = 0; j < cantidad; j++)
        {
            if (strcmp(artistas[j], catalogo[i].artista) == 0)
            {
                ya_esta = 1;
                break;
            }
        }

        //Si no estaba lo copiamos a la lista
        if (!ya_esta)
        {
            strcpy(artistas[cantidad], catalogo[i].artista);
            cantidad++;
        }
    }

    return cantidad;

}


/**
 * @brief Guarda dentro del arreglo generos[] los generos distintos del catalogo (sin repetirlos)
 * 
 * @param catalogo - arreglo de canciones
 * @param total - cantidad de canciones en catalogo
 * @param generos - arreglo de salida con los generos encontrados
 * @param max_generos - capacidad maxima de generos[]
 * @return int cantidad de generos guardados en generos[] o -1 si hay parametros invalidos
 */
int listar_generos(const Cancion catalogo[], int total, char generos[][GENERO_MAX], int max_generos)
{

    if (catalogo == NULL || generos == NULL || total < 0 || max_generos <= 0)
    {
        return -1;
    }

    int cantidad = 0;

    for (int i = 0; i < total && cantidad < max_generos; i++)
    {
        int ya_esta = 0;

        for (int j = 0; j < cantidad; j++)
        {
            if (strcmp(generos[j], catalogo[i].genero) == 0)
            {
                ya_esta = 1;
                break;
            }
        }

        if (!ya_esta)
        {
            strcpy(generos[cantidad], catalogo[i].genero);
            cantidad++;
        }
    }

    return cantidad;

}

/**
 * @brief Crea una copia del catalogo en memoria dinamica
 *        (sirve para ordenar o rankear sin alterar el orden del catalogo original)
 *
 * @param catalogo - arreglo de canciones a copiar
 * @param total - cantidad de canciones en catalogo[]
 * @return Cancion* - copia (hay que liberarla con free) o NULL si hay un error
 */
Cancion *duplicar_catalogo(const Cancion catalogo[], int total)
{
    if (catalogo == NULL || total <= 0)
    {
        return NULL;
    }

    Cancion *copia = malloc(total * sizeof(Cancion));
    if (copia == NULL)
    {
        return NULL;
    }

    memcpy(copia, catalogo, total * sizeof(Cancion));
    return copia;
}

/**
 * @brief Suma una reproduccion a la cancion con el id indicado
 *        (busqueda lineal porque el catalogo puede estar ordenado por cualquier campo)
 *
 * @param catalogo - arreglo de canciones (se modifica)
 * @param total - cantidad de canciones en catalogo[]
 * @param id - id de la cancion reproducida
 * @return int - 1 si se actualizo, 0 si el id no existe o hay parametros invalidos
 */
int incrementar_reproducciones(Cancion catalogo[], int total, int id)
{
    if (catalogo == NULL || total <= 0)
    {
        return 0;
    }

    for (int i = 0; i < total; i++)
    {
        if (catalogo[i].id == id)
        {
            catalogo[i].num_reproducciones++;
            return 1;
        }
    }

    return 0;
}