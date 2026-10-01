#ifndef ordenamiento_h
#define ordenamiento_h


typedef struct {
    int id;
    char titulo[100];
    char artista[50];
    char album[100];
    char genero[50];
    int duracion;
    int anho;
    int reproducciones;
} cancion;

void selection_sort(cancion arr[], int n, int campo);

void mostrar_catalogo(cancion arr[], int n);

int comparar_canciones(cancion a, cancion b, int campo);

void merge(cancion arr[], cancion aux[], int izq, int m, int der, int campo);

void mergeSort_recursivo(cancion arr[], cancion aux[], int izq, int der, int campo);

void mergeSort(cancion arr[], int n, int campo);

int busqueda_binaria_id(cancion arr[], int izq, int der, int x);

int busqueda_binaria_titulo_artista(cancion arr[], int izq, int der, char* x, int campo);

void obtener_canciones_artista(cancion arr[], int n, char artista[]);

void ranking(cancion arr[], int n, int top);

void obtener_cancion_mas_escuchada(cancion arr[], int n, int campo, char texto[]);



#endif // !ordenamiento_h