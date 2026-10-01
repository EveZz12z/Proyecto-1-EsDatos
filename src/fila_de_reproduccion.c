#include "canciones.h"
#include "fila_de_reproduccion.h"


/**
 * @brief Función para vaciar la fila de reproducción por completo
 * 
 * @param filas arreglo de estructuras Cancion que representa a una fila de reprodución
 */
void vaciar_fila(Cancion filas[MAX_CANCIONES]){
    for(int i = 0; i < MAX_CANCIONES; i++){
        filas[i].id = -1;
        strcpy(filas[i].titulo, "holder");
        strcpy(filas[i].album, "holder");
        strcpy(filas[i].artista, "holder");
        strcpy(filas[i].genero, "holder");
        filas[i].num_reproducciones = -1;
        filas[i].duracion_seg = -1;
        filas[i].anho = -1;
    }
    return;
}


/**
 * @brief Detecta 
 * 
 * @param filas arreglo de estructuras Cancion que representa a una fila de reproducción
 * @param id entero id
 * @return int retorna 0 si no se ha encontrado la canción o retorna 1 si se ha encontrado la canción.
 */
int detectar_id(Cancion filas[MAX_CANCIONES], int id){
    for(int i = 0; i < MAX_CANCIONES; i++){
        if(filas[i].id == id)
            return 1;
        
        if(filas[i].id == -1)
            break;
    }

    return 0;
}

/**
 * @brief 
 * 
 * @param filas Arreglo de estructuras Cancion que representa a una fila de reprodución 
 * @param cancion De tipo Cancion
 * @return int Retorna 0 si la canción ya esta en en la fila de reproducción
 *             o si la fila de reproducción se encuentra llena. Retorna 1 si
 *             la canción ha sido añadida a la lista.
 */
int anadir_cancion(Cancion filas[MAX_CANCIONES], Cancion cancion){
    /*Detector de duplicados*/
    if(filas[MAX_CANCIONES-1].id != -1){
        printf("Error: Fila de reproducción llena\n");
        return 0;
    }

    if(detectar_id(filas, cancion.id)){
        printf("Canción ya esta en la fila de reproducción\n");
        return 0;
    }

    for(int i = MAX_CANCIONES - 1; i > 0; i--){
        filas[i] = filas[i - 1];
    }
    filas[0] = cancion;
    return 1; 
}

/**
 * @brief Muestra por pantalla las canciones dentro del arreglo filas que no estén vacías
 * 
 * @param filas Arreglo de estructuras Cancion que representa a una fila de reprodución 
 */

void consultar_fila(Cancion filas[MAX_CANCIONES]){
    int cont = 0;

    for(int i = 0; i < MAX_CANCIONES; i++){
        if(filas[i].id ==-1 ){
            if(cont == 0)
                printf("Fila de reproducción vacía\n");
            return;
        }
        cont++;
        printf("%d |\t %d %s %s", cont, filas[i].id,
                filas[i].titulo, filas[i].artista);
    }
    return;
}

/**
 * @brief Busca el indice de una cancion en el arreglo filas por la id
 * 
 * @param filas Arreglo de estructuras Cancion que representa a una fila de reprodución 
 * @param id Entero id de la cancion
 * @return int Retorna -1 si llegase a fallar la función, retorna 1 si
 *             se encuentra con un elemento vacío y retorna i (el indice)
 *             si encuentra la id correspondiente en el arreglo.
 */
int buscar_indice_por_id(Cancion filas[MAX_CANCIONES], int id){
    for(int i = 0; i < MAX_CANCIONES; i++){
            if(filas[i].id == -1)
                break;

            if(filas[i].id == id)
                return i;
        }
    return -1;
}


/**
 * @brief Elimina la canción de la fila utilizando la id
 * 
 * @param filas Arreglo de estructuras Cancion que representa a una fila de reprodución 
 * @param cancion Canción a eliminar
 * @return int Retorna 0 si no encuentra la id, retorna 1 si se ha borrado la canción de
 *             lista de reproducción
 */
int eliminar_cancion_por_id_de_fila(Cancion filas[MAX_CANCIONES], Cancion cancion){
    int indice = buscar_indice_por_id(filas, cancion.id);

    if(indice == -1){
        printf("Error: Id no identificada en la fila de reproducción\n");
        return 0;
    }
        for (int i = indice; i < MAX_CANCIONES - 1; i++){
            filas[i] = filas[i+1];
        }

        filas[MAX_CANCIONES - 1].id = -1;

        printf("Se ha borrado la canción de la lista de reproducción\n");
        return 1;
}



