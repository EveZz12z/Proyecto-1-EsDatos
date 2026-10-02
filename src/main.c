#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "canciones.h"
#include "catalogo.h"
#include "importacion.h"
#include "exportacion.h"
#include "ordenamiento.h"
#include "fila_de_reproduccion.h"

#define ARCHIVO_CATALOGO    "catalogo.csv"
#define ARCHIVO_EXPORTADO   "catalogo_actualizado.csv"
#define CANCIONES_INICIALES 200
#define K_HISTORIAL         10      /* tamaño maximo del historial (ultimas K canciones) */

/* Lee un entero por teclado. Retorna -1 si la entrada no es un número. */
static int leer_entero(const char *mensaje)
{
    char texto_ingresado[32];
    char *fin_numero;

    printf("%s", mensaje);
    if (fgets(texto_ingresado, sizeof texto_ingresado, stdin) == NULL) return -1;

    long numero_leido = strtol(texto_ingresado, &fin_numero, 10);
    if (fin_numero == texto_ingresado) return -1;  /* no se leyo ningun digito */
    return (int)numero_leido;
}

/* Lee una línea de texto (con espacios) y le quita el salto de línea. */
static void leer_texto(const char *mensaje, char *destino, int tamanio_maximo)
{
    printf("%s", mensaje);
    if (fgets(destino, tamanio_maximo, stdin) == NULL) destino[0] = '\0';
    destino[strcspn(destino, "\n")] = '\0';
}

/* Retorna un puntero a la cancion con ese id (busqueda lineal) o NULL si no existe. */
static Cancion *buscar_por_id(Cancion catalogo[], int total_canciones, int id_buscado)
{
    for (int i = 0; i < total_canciones; i++)
        if (catalogo[i].id == id_buscado) return &catalogo[i];
    return NULL;
}

/* Cantidad de canciones por cada genero presente en el catalogo. */
static void cantidad_por_genero(Cancion catalogo[], int total_canciones)
{
    char generos[MAX_CANCIONES][GENERO_MAX];
    int cantidad_generos = listar_generos(catalogo, total_canciones, generos, MAX_CANCIONES);

    for (int i = 0; i < cantidad_generos; i++)
        printf("%-20s %d canciones\n", generos[i],
               contar_por_genero(catalogo, total_canciones, generos[i]));
}

/* Lista los artistas distintos del catalogo. */
static void mostrar_artistas(Cancion catalogo[], int total_canciones)
{
    char artistas[MAX_CANCIONES][ARTISTA_MAX];
    int cantidad_artistas = listar_artistas(catalogo, total_canciones, artistas, MAX_CANCIONES);

    for (int i = 0; i < cantidad_artistas; i++) printf("- %s\n", artistas[i]);
}

/* Muestra las canciones de un genero ingresado por teclado. */
static void listar_genero_ingresado(Cancion catalogo[], int total_canciones)
{
    char genero_buscado[GENERO_MAX];
    int posiciones_encontradas[MAX_CANCIONES];

    leer_texto("Genero: ", genero_buscado, sizeof genero_buscado);
    int cantidad_encontradas = listar_por_genero(catalogo, total_canciones, genero_buscado,
                                                 posiciones_encontradas, MAX_CANCIONES);
    if (cantidad_encontradas <= 0) { puts("No hay canciones de ese genero"); return; }

    for (int i = 0; i < cantidad_encontradas; i++)
        mostrar_catalogo(&catalogo[posiciones_encontradas[i]], 1);
}

/* Ordena el catalogo por el campo y algoritmo elegidos (selection sort o merge sort). */
static void ordenar_catalogo(Cancion catalogo[], int total_canciones)
{
    int campo_orden = leer_entero("Campo (1=ID 2=Anho 3=Duracion 4=Reproducciones 5=Titulo 6=Artista 7=Album 8=Genero): ");
    int algoritmo   = leer_entero("Algoritmo (1=Selection 2=Merge): ");

    if (campo_orden < 1 || campo_orden > 8 || algoritmo < 1 || algoritmo > 2) {
        puts("Opcion invalida");
        return;
    }

    if (algoritmo == 1) selection_sort(catalogo, total_canciones, campo_orden);
    else                mergeSort(catalogo, total_canciones, campo_orden);

    mostrar_catalogo(catalogo, total_canciones);
}

/* Busca por ID título o artista con búsqueda binaria sobre una copia ordenada. */
static void buscar(Cancion catalogo[], int total_canciones)
{
    int tipo_busqueda = leer_entero("Buscar por (1=ID 2=Titulo 3=Artista): ");
    if (tipo_busqueda < 1 || tipo_busqueda > 3) { puts("Opcion invalida"); return; }

    /* Se ordena una copia para no alterar el orden del catalogo original */
    Cancion *copia_catalogo = duplicar_catalogo(catalogo, total_canciones);
    if (copia_catalogo == NULL) { puts("Error de memoria"); return; }

    int posicion_encontrada;

    if (tipo_busqueda == 1) {
        int id_buscado = leer_entero("ID: ");
        mergeSort(copia_catalogo, total_canciones, 1);
        posicion_encontrada = busqueda_binaria_id(copia_catalogo, 0, total_canciones - 1, id_buscado);
    } else {
        char texto_buscado[TITULO_MAX];
        int campo_orden, campo_busqueda;

        if (tipo_busqueda == 2) { campo_orden = 5; campo_busqueda = 1; }   /* titulo */
        else                    { campo_orden = 6; campo_busqueda = 2; }   /* artista */

        leer_texto("Texto exacto: ", texto_buscado, sizeof texto_buscado);
        mergeSort(copia_catalogo, total_canciones, campo_orden);
        posicion_encontrada = busqueda_binaria_titulo_artista(copia_catalogo, 0, total_canciones - 1,
                                                              texto_buscado, campo_busqueda);
    }

    if (posicion_encontrada < 0) puts("No encontrada");
    else                         mostrar_catalogo(&copia_catalogo[posicion_encontrada], 1);

    free(copia_catalogo);
}

/* Ranking (mostrar_ranking = 1) o más escuchada por artista/genero (mostrar_ranking = 0).
   Trabaja sobre una copia para no alterar el catalogo. */
static void estadisticas(Cancion catalogo[], int total_canciones, int mostrar_ranking)
{
    Cancion *copia_catalogo = duplicar_catalogo(catalogo, total_canciones);
    if (copia_catalogo == NULL) { puts("Error de memoria"); return; }

    if (mostrar_ranking) {
        ranking(copia_catalogo, total_canciones, leer_entero("Top N: "));
    } else {
        int campo_busqueda = leer_entero("Buscar por (1=Artista 2=Genero): ");
        char nombre_buscado[ARTISTA_MAX];
        leer_texto("Nombre: ", nombre_buscado, sizeof nombre_buscado);
        obtener_cancion_mas_escuchada(copia_catalogo, total_canciones, campo_busqueda, nombre_buscado);
    }

    free(copia_catalogo);
}

/* Quita una canción de la fila por posicion (1..n) o por ID. */
static void quitar_de_fila(Cancion fila_reproduccion[])
{
    int tipo_quitar = leer_entero("Quitar por (1=Posicion 2=ID): ");
    int valor_ingresado = leer_entero("Valor: ");
    Cancion cancion_a_quitar = {0};

    if (tipo_quitar == 1 && valor_ingresado >= 1 && valor_ingresado <= MAX_CANCIONES
        && fila_reproduccion[valor_ingresado - 1].id != -1) {
        cancion_a_quitar = fila_reproduccion[valor_ingresado - 1];
    } else if (tipo_quitar == 2) {
        cancion_a_quitar.id = valor_ingresado;
    } else {
        puts("Posicion o opcion invalida");
        return;
    }

    eliminar_cancion_por_id(fila_reproduccion, cancion_a_quitar);
}

/* Reproduce la primera cancion de la fila: la muestra, suma una reproduccion en el
   catalogo, la agrega al historial y la saca de la fila. */
static void reproducir(Cancion fila_reproduccion[], Cancion historial[],
                       Cancion catalogo[], int total_canciones)
{
    if (fila_reproduccion[0].id == -1) { puts("La fila esta vacia"); return; }

    Cancion cancion_actual = fila_reproduccion[0];
    if (reproduccion_fila(historial, &cancion_actual, K_HISTORIAL) == 1) {
        incrementar_reproducciones(catalogo, total_canciones, cancion_actual.id);
        eliminar_cancion_por_id(fila_reproduccion, cancion_actual);
    }
}

int main(void)
{
    srand((unsigned)time(NULL));

    Cancion catalogo[MAX_CANCIONES];
    Cancion fila_reproduccion[MAX_CANCIONES];
    Cancion historial[MAX_CANCIONES];

    int total_canciones = iniciar_catalogo(catalogo, CANCIONES_INICIALES, ARCHIVO_CATALOGO);
    if (total_canciones < 0) {
        fprintf(stderr, "Error: no se pudo cargar ni generar el catalogo\n");
        return 1;
    }
    vaciar_fila(fila_reproduccion);
    vaciar_fila(historial);

    int opcion = -1;
    while (opcion != 0 && !feof(stdin)) {
        printf("\n===== REPRODUCTOR (%d canciones) =====\n"
               " 1 Generar catalogo        2 Listar artistas       3 Cantidad por genero\n"
               " 4 Listar por genero       5 Contar un genero      6 Ordenar catalogo\n"
               " 7 Buscar cancion          8 Canciones de artista  9 Ranking top N\n"
               "10 Mas escuchada           11 Ver fila             12 Anadir a fila\n"
               "13 Quitar de fila          14 Vaciar fila          15 Ver historial\n"
               "16 Reproducir              17 Exportar CSV         18 Mostrar catalogo\n"
               " 0 Salir\n", total_canciones);
        opcion = leer_entero("Opcion: ");

        switch (opcion) {
        case 1: {
            int cantidad_generada = generar_catalogo(catalogo, leer_entero("N canciones (1-1000): "));
            if (cantidad_generada < 0) { puts("N invalido"); break; }
            total_canciones = cantidad_generada;
            vaciar_fila(fila_reproduccion);
            vaciar_fila(historial);
            break;
        }
        case 2:  mostrar_artistas(catalogo, total_canciones); break;
        case 3:  cantidad_por_genero(catalogo, total_canciones); break;
        case 4:  listar_genero_ingresado(catalogo, total_canciones); break;
        case 5: {
            char genero_buscado[GENERO_MAX];
            leer_texto("Genero: ", genero_buscado, sizeof genero_buscado);
            printf("%s: %d canciones\n", genero_buscado,
                   contar_por_genero(catalogo, total_canciones, genero_buscado));
            break;
        }
        case 6:  ordenar_catalogo(catalogo, total_canciones); break;
        case 7:  buscar(catalogo, total_canciones); break;
        case 8: {
            char artista_buscado[ARTISTA_MAX];
            leer_texto("Artista: ", artista_buscado, sizeof artista_buscado);
            obtener_canciones_artista(catalogo, total_canciones, artista_buscado);
            break;
        }
        case 9:  estadisticas(catalogo, total_canciones, 1); break;
        case 10: estadisticas(catalogo, total_canciones, 0); break;
        case 11: consultar_fila(fila_reproduccion); break;
        case 12: {
            Cancion *cancion_encontrada = buscar_por_id(catalogo, total_canciones,
                                                        leer_entero("ID de la cancion: "));
            if (cancion_encontrada == NULL) puts("ID no existe en el catalogo");
            else                            anadir_cancion(fila_reproduccion, *cancion_encontrada);
            break;
        }
        case 13: quitar_de_fila(fila_reproduccion); break;
        case 14: vaciar_fila(fila_reproduccion); puts("Fila vaciada"); break;
        case 15: consultar_historial_fila(historial, K_HISTORIAL); break;
        case 16: reproducir(fila_reproduccion, historial, catalogo, total_canciones); break;
        case 17:
            if (exportar_catalogo_csv(catalogo, total_canciones, ARCHIVO_EXPORTADO) < 0)
                puts("Error al exportar");
            else
                printf("Catalogo exportado a %s\n", ARCHIVO_EXPORTADO);
            break;
        case 18: mostrar_catalogo(catalogo, total_canciones); break;
        case 0:  puts("Hasta luego"); break;
        default: puts("Opcion invalida");
        }
    }
    return 0;
}