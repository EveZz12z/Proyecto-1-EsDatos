#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ordenamiento.h"

int comparar_canciones(cancion a, cancion b, int campo) {

    switch (campo) {

    case 1:
        return a.id <= b.id;

    case 2:
        return a.anho <= b.anho;

    case 3:
        return a.duracion <= b.duracion;

    case 4:
        return a.reproducciones <= b.reproducciones;

    case 5:
        return strcmp(a.titulo, b.titulo) <= 0;

    case 6:
        return strcmp(a.artista, b.artista) <= 0;

    case 7:
        return strcmp(a.album, b.album) <= 0;

    case 8:
        return strcmp(a.genero, b.genero) <= 0;

    default:
        return 0;
    }
}

// arr: catálogo que quieres ordenar
// n: numero de canciones
// campo: atributo a vallidar y ordenar
void selection_sort(cancion arr[], int n, int campo) {
    //variable temporal para guardar la cancion y luego cambiarla completa
    cancion temp;

    if (campo < 1 || campo > 8) {
        printf("Campo invalido\n");
        return;
    }

    // Recorre todas las posiciones a ordenar
    for (int i = 0; i < n - 1; i++) {

        int min_index = i;

        //recorre las posiciones despues de i
        for (int j = i + 1; j < n; j++) {

            //si j debe ir antes que la cancion menor acutal, se guarda
            if (comparar_canciones(arr[j], arr[min_index], campo)) {
                min_index = j;
            }
        }
        
        //se produce el intercambio
        temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}

void mostrar_catalogo(cancion arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("ID: %d | Titulo: %s | Artista: %s | Album: %s | Genero: %s | Duracion: %d | Anho: %d | Reproducciones: %d\n",
            arr[i].id,
            arr[i].titulo,
            arr[i].artista,
            arr[i].album,
            arr[i].genero,
            arr[i].duracion,
            arr[i].anho,
            arr[i].reproducciones);
    }
}
// arr: catálogo que quieres ordenar
// aux: arreglo auxiliar 
// izq: inicio de la sección actual
// m: medio
// der: final de la sección actual
// campo: atributo por el que estás ordenando
void merge(cancion arr[], cancion aux[], int izq, int m, int der, int campo) {

    int i = izq;
    int j = m + 1;
    int k;
    
    //copia el arreglo en aux
    for (k = izq; k <= der; k++) {
        aux[k] = arr[k];
    }

    //mezcla las dos mitades previamente ordenadas
    for (k = izq; k <= der; k++) {

        //si i paso la mitad izquierda se guarda y avanza
        if (i > m) {
            arr[k] = aux[j];
            j++;
        }

        //si j paso la mitad derecha se guarda y avanza
        else if (j > der) {
            arr[k] = aux[i];
            i++;
        }

        //si la cancion de la izquierda va antes
        else if (comparar_canciones(aux[i], aux[j], campo)) {
            arr[k] = aux[i];
            i++;
        }

        //si la cancion de la derecha va antes
        else {
            arr[k] = aux[j];
            j++;
        }
    }
}

// arr: catálogo que quieres ordenar
// aux: arreglo auxiliar que usa merge()
// izq: inicio de la sección actual
// der: final de la sección actual
// campo: atributo por el que estás ordenando
void mergeSort_recursivo(cancion arr[], cancion aux[], int izq, int der, int campo) {

    //caso base
    if (izq >= der) {
        return;
    }

    int medio = izq + (der - izq) / 2;

    //divide ambas mitades
    mergeSort_recursivo(arr, aux, izq, medio, campo);
    mergeSort_recursivo(arr, aux, medio + 1, der, campo);

    //une las mitades
    merge(arr, aux, izq, medio, der, campo);
}

// se ejecuta megresort
// arr: catalogo de canciones
// n: cantidad de canciones
// campo: criterio  para ordenar.
void mergeSort(cancion arr[], int n, int campo) {

    if (campo < 1 || campo > 8) {
        printf("Campo invalido\n");
        return;
    }

    //reserva memoria para un arreglo auxiliar
    cancion* aux = malloc(n * sizeof(cancion));

    if (aux == NULL) {
        printf("Error al reservar memoria\n");
        return;
    }

    mergeSort_recursivo(arr, aux, 0, n - 1, campo);

    //libera la memoria reservada
    free(aux);
}

// arr arreglo de canciones
// izq índice inicial de la zona donde estás buscando
// der índice final
// x ID que quieres encontrar
int busqueda_binaria_id(cancion arr[], int izq, int der, int x) {
    
    //caso base
    if (izq > der) {
        return -1;
    }
    else {
        int mid = izq + (der - izq) / 2;
        
        //si el id esta en el medio
        if (arr[mid].id == x) {
            return mid;
        }

        //si el id es menor que el del medio
        if (arr[mid].id > x) {
            //elimia la mitad derecha hasta 1 antes de mid y busca a la izquierda
            return busqueda_binaria_id(arr, izq, mid - 1, x);
        }

        //si el id es mayor al del medio
        else {
            //elimina la mitad izquierda hasta 1 mas que mid y busca a la derecha
            return busqueda_binaria_id(arr, mid + 1, der, x);
        }
    }
}

// arr arreglo de canciones
// izq índice inicial de la zona donde estás buscando
// der índice final
// x texto que se quiere busscar
// campo atributo a buscar
int busqueda_binaria_titulo_artista(cancion arr[], int izq, int der, char* x, int campo) {
    
    //caso base
    if (izq > der) {
        return -1;
    }
    else {
        int mid = izq + (der - izq) / 2;
        int verificacion = 0;

        switch (campo)
        {
            case 1:
                verificacion = strcmp(arr[mid].titulo, x);
                break;
            case 2:
                verificacion = strcmp(arr[mid].artista, x);
                break;
            default:
                return -1;
        }

        if (verificacion == 0) {
            return mid;
        }

        if (verificacion > 0) {
            //elimia la mitad derecha hasta 1 antes de mid y busca a la izquierda
            return busqueda_binaria_titulo_artista(arr, izq, mid - 1, x, campo);
        }
        else {
            //elimina la mitad izquierda hasta 1 mas que mid y busca a la derecha
            return busqueda_binaria_titulo_artista(arr, mid + 1, der, x, campo);
        }
    }
}

// arr arreglo de canciones
// n numero de canciones
// artista a buscar
void obtener_canciones_artista(cancion arr[], int n, char artista[]) {
    int i;
    int cont = 0;

    //recorre las canciones
    for (i = 0; i < n; i++) {
        //si coinciden se imprimen y se van sumando en cont
        if (strcmp(arr[i].artista, artista) == 0) {
            printf("Titulo: %s\n", arr[i].titulo);
            cont++;
        }
    }

    if (cont == 0) {
        printf("Artista no encontrado\n");
    }
}

// arr arreglo de canciones
// n numero de canciones
//top el top que se quiera buscar
void ranking(cancion arr[], int n, int top) {
    int i;
    int cont = 1;

    if (top <= 0) {
        printf("El top es invalido\n");
        return;
    }
    else if (top > n) {
        printf("El top es invalido\n");
        return;
    }

    //se llama al metodo de ordenamiento con el campo de reproducciones
    selection_sort(arr, n, 4);

    printf("==================================================================================\n");
    printf("Top %d de canciones con mas reproducciones:\n", top);
    printf("----------------------------------------------------------------------------------\n");

    //selecion sort viene de menor a mayor, este for invierte eso
    for (i = n - 1; i >= n - top; i--) {
        printf(" %-2d) %-25s | %-25s | %d reproducciones\n",
            cont,
            arr[i].titulo,
            arr[i].artista,
            arr[i].reproducciones);

        cont++;
    }

    printf("==================================================================================\n");
}

// arr arreglo de canciones
// n numero de canciones
// campo atributo a buscar 1=artista 2=genero
//texto donde se ingresara artista o genero
void obtener_cancion_mas_escuchada(cancion arr[], int n, int campo, char texto[]) {
    int i;

    //se llama al metodo de ordenamiento con el campo de reproducciones
    selection_sort(arr, n, 4);

    switch (campo) {

    case 1:
        //se recorre el arreglo del final al principio
        for (i = n - 1; i >= 0; i--) {

            //si coinciden se imprime la cancion mas escuchada
            if (strcmp(arr[i].artista, texto) == 0) {
                printf("Cancion mas escuchada de %s: %s con: %d reproducciones\n",
                    texto,
                    arr[i].titulo, arr[i].reproducciones);
                return;
            }
        }

        printf("Artista no encontrado\n");
        break;

    case 2:
        //se recorre el arreglo del final al principio
        for (i = n - 1; i >= 0; i--) {
            if (strcmp(arr[i].genero, texto) == 0) {
            
                //si coinciden se imprime la cancion mas escuchada
                printf("Cancion mas escuchada de %s: %s con: %d reproducciones\n",
                    texto,
                    arr[i].titulo, arr[i].reproducciones);
                return;
            }
        }

        printf("Genero no encontrado\n");
        break;

    default:
        printf("Campo invalido\n");
        break;
    }
}