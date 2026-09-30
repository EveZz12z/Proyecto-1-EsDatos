/* Autor: Pablo Serón - main de prueba (no es el main final del proyecto) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "importacion.h"
#include "canciones.h"
#include "catalogo.h"
#include "exportacion.h"

int main(void)
{
    srand((unsigned)time(NULL));

    Cancion catalogo[MAX_CANCIONES];
    int total = 50;

    /* --- PRUEBA 1: generar catálogo --- */
    printf("=== Prueba 1: generar ===\n");
    printf("generar 50 -> %d (esperado 50)\n", generar_catalogo(catalogo, total));
    printf("generar 0 -> %d (esperado -1)\n", generar_catalogo(catalogo, 0));
    printf("generar 1001 -> %d (esperado -1)\n", generar_catalogo(catalogo, MAX_CANCIONES + 1));
    /* La llamada de 50 se hizo primero, el catálogo sigue válido. */

    printf("Primeras 3 canciones:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("  id=%d | %s | %s | %s | %s | %d s | %d | %d rep\n",
               catalogo[i].id, catalogo[i].titulo, catalogo[i].artista,
               catalogo[i].album, catalogo[i].genero, catalogo[i].duracion_seg,
               catalogo[i].anho, catalogo[i].num_reproducciones);
    }

    /* --- PRUEBA 2: artistas --- */
    printf("\n=== Prueba 2: artistas ===\n");
    char artistas[20][ARTISTA_MAX];
    int n_art = listar_artistas(catalogo, total, artistas, 20);
    printf("Artistas distintos: %d (esperado 8 o menos)\n", n_art);
    for (int i = 0; i < n_art; i++)
    {
        printf("  %d. %s\n", i + 1, artistas[i]);
    }

    /* --- PRUEBA 3: géneros --- */
    printf("\n=== Prueba 3: generos y conteo ===\n");
    char generos[20][GENERO_MAX];
    int n_gen = listar_generos(catalogo, total, generos, 20);
    int suma = 0;
    for (int i = 0; i < n_gen; i++)
    {
        int cant = contar_por_genero(catalogo, total, generos[i]);
        printf("  %-16s %d\n", generos[i], cant);
        suma += cant;
    }
    printf("Suma de conteos: %d (esperado %d)\n", suma, total);
    printf("Genero inexistente -> %d (esperado 0)\n",
           contar_por_genero(catalogo, total, "Inexistente"));
    printf("catalogo NULL -> %d (esperado -1)\n",
           contar_por_genero(NULL, total, "Rap"));

    /* --- PRUEBA 4: listar por género --- */
    printf("\n=== Prueba 4: listar por genero (Rap) ===\n");
    int indices[MAX_CANCIONES];
    int n_rap = listar_por_genero(catalogo, total, "Rap", indices, MAX_CANCIONES);
    printf("Encontradas: %d (debe coincidir con el conteo de Rap)\n", n_rap);
    for (int i = 0; i < n_rap; i++)
    {
        printf("  pos %d -> id %d, %s\n", indices[i],
               catalogo[indices[i]].id, catalogo[indices[i]].titulo);
    }

    /* --- PRUEBA 5: exportar --- */
    printf("\n=== Prueba 5: exportar ===\n");
    printf("exportar -> %d (esperado %d)\n",
           exportar_catalogo_csv(catalogo, total, "prueba.csv"), total);
    printf("ruta invalida -> %d (esperado -1)\n",
           exportar_catalogo_csv(catalogo, total, "/carpeta/que/no/existe/x.csv"));
    printf("catalogo NULL -> %d (esperado -1)\n",
           exportar_catalogo_csv(NULL, total, "x.csv"));


           /* --- PRUEBA 6: importar (ida y vuelta) --- */
    printf("\n=== Prueba 6: importar ===\n");
    Cancion leido[MAX_CANCIONES];
    printf("archivo_existe prueba.csv -> %d (esperado 1)\n", archivo_existe("prueba.csv"));
    printf("archivo_existe no_existe.csv -> %d (esperado 0)\n", archivo_existe("no_existe.csv"));

    int cargadas = cargar_catalogo_csv("prueba.csv", leido, MAX_CANCIONES);
    printf("cargadas -> %d (esperado %d)\n", cargadas, total);
    printf("archivo inexistente -> %d (esperado -1)\n",
           cargar_catalogo_csv("no_existe.csv", leido, MAX_CANCIONES));

    int iguales = 1;
    for (int i = 0; i < total && i < cargadas; i++)
    {
        if (leido[i].id != catalogo[i].id ||
            strcmp(leido[i].titulo, catalogo[i].titulo) != 0 ||
            strcmp(leido[i].artista, catalogo[i].artista) != 0 ||
            leido[i].num_reproducciones != catalogo[i].num_reproducciones)
        {
            iguales = 0;
        }
    }
    printf("datos identicos a los de memoria -> %d (esperado 1)\n", iguales);
    
        /* --- PRUEBA 7: logica de arranque --- */
    printf("\n=== Prueba 7: arranque ===\n");
    remove("arranque_test.csv");      /* partimos sin archivo */

    Cancion primera[MAX_CANCIONES], segunda[MAX_CANCIONES];

    int n1 = iniciar_catalogo(primera, 30, "arranque_test.csv");
    printf("1ra vez (genera) -> %d (esperado 30)\n", n1);
    printf("archivo creado -> %d (esperado 1)\n", archivo_existe("arranque_test.csv"));

    /* Pedimos 999 a proposito: si lee el CSV, ignorara ese numero */
    int n2 = iniciar_catalogo(segunda, 999, "arranque_test.csv");
    printf("2da vez (lee) -> %d (esperado 30, no 999)\n", n2);

    int mismos = 1;
    for (int i = 0; i < n1 && i < n2; i++)
    {
        if (primera[i].id != segunda[i].id)
        {
            mismos = 0;
        }
    }
    printf("mismo catalogo en ambas -> %d (esperado 1)\n", mismos);
    printf("ruta NULL -> %d (esperado -1)\n", iniciar_catalogo(primera, 30, NULL));

    
        /* --- PRUEBA 8: ordenamiento burbuja --- */
    printf("\n=== Prueba 8: ordenar ===\n");
    Cancion ordenado[MAX_CANCIONES];
    memcpy(ordenado, catalogo, sizeof(Cancion) * total);   /* copia: no tocamos el original */

    CampoCancion campos[] = { CAMPO_ID, CAMPO_TITULO, CAMPO_ARTISTA, CAMPO_ALBUM,
                              CAMPO_GENERO, CAMPO_DURACION, CAMPO_ANHO, CAMPO_REPRODUCCIONES };
    const char *nombres[] = { "id", "titulo", "artista", "album",
                              "genero", "duracion", "anho", "reproducciones" };

    for (int k = 0; k < 8; k++)
    {
        BubbleSort(ordenado, total, campos[k]);
        int ok = 1;
        for (int i = 0; i + 1 < total; i++)
        {
            if (comparar_canciones(&ordenado[i], &ordenado[i + 1], campos[k]) > 0)
            {
                ok = 0;
            }
        }
        printf("ordenado por %-15s -> %d (esperado 1)\n", nombres[k], ok);
    }
    printf("catalogo NULL -> %d (esperado -1)\n", BubbleSort(NULL, total, CAMPO_ID));

        /* --- PRUEBA 9: busqueda binaria --- */
    printf("\n=== Prueba 9: busqueda binaria ===\n");

    /* Por id: cada id debe encontrarse en su propia posicion */
    BubbleSort(ordenado, total, CAMPO_ID);
    int todos_ok = 1;
    for (int i = 0; i < total; i++)
    {
        Cancion clave_id = {0};
        clave_id.id = ordenado[i].id;
        if (busqueda_binaria(ordenado, total, &clave_id, CAMPO_ID) != i)
        {
            todos_ok = 0;
        }
    }
    printf("encuentra todos los ids -> %d (esperado 1)\n", todos_ok);

    Cancion clave = {0};
    clave.id = 99999;
    printf("id inexistente -> %d (esperado -1)\n",
           busqueda_binaria(ordenado, total, &clave, CAMPO_ID));
    printf("catalogo NULL -> %d (esperado -1)\n",
           busqueda_binaria(NULL, total, &clave, CAMPO_ID));
    printf("catalogo vacio -> %d (esperado -1)\n",
           busqueda_binaria(ordenado, 0, &clave, CAMPO_ID));

    /* Por artista: tomamos uno que sabemos que existe */
    BubbleSort(ordenado, total, CAMPO_ARTISTA);
    snprintf(clave.artista, ARTISTA_MAX, "%s", ordenado[total / 2].artista);
    int pos = busqueda_binaria(ordenado, total, &clave, CAMPO_ARTISTA);
    printf("artista '%s' -> pos %d, coincide: %d (esperado 1)\n", clave.artista, pos,
           pos >= 0 && strcmp(ordenado[pos].artista, clave.artista) == 0);

    snprintf(clave.artista, ARTISTA_MAX, "Artista_Inexistente");
    printf("artista inexistente -> %d (esperado -1)\n",
           busqueda_binaria(ordenado, total, &clave, CAMPO_ARTISTA));

    return 0;

}

