/**
 * @file fila_de_reproduccion.c
 * @author Yanira Mansilla(you@domain.com)
 * @brief 
 */
#include "fila_de_reproduccion.h"
#include "canciones.h"

/**
 * @brief Función para consultar por la fila de reproducción.
 * 
 */
void consultar_fila(){

    FILE* f;
    int cont = 0;
    char *buffer = (char *)malloc(1000 * sizeof(char)), *token;

    

    f = fopen("build/fila_reproduccion.csv","r");
    if (f == NULL){
        printf("Error: No se pudo abrir el archivo\n");
        return;
    }

    while (fgets(buffer, 1000, f) != NULL) {
        cont ++;

        token = strtok(buffer, ",");

        if(cont == 1){
            printf(" \t");
        }
        else
            printf("%d\t",cont);
        

        while(token != NULL){
            printf("%-15s\t", token);
        }

        printf("\n");
        
    }
    
    free(buffer);

    fclose(f);
    return;
}


/**
 * @brief Función que añáde una canción al inicio de la fila de reproducción
 * 
 * @param cancion puntero de tipo char que pasar los datos de la canción que se quiere agregar
 */
void anhadir_cancion_comienzo(char *cancion){
    FILE *og;
    FILE *temp;
    char *buffer = (char * )malloc(1000 * sizeof(char));
    int cont_lineas = 0, existia = 0;

    if(buffer == NULL){
        printf("Error: No se pudo crear espacio de memoria\n");
        return;
    }

    og = fopen("build/fila_reproduccion.csv", "r");
    temp = fopen("build/archivo_temporal.csv", "w");
    if (temp == NULL){
        printf("Error: No fue posible crear el archivo\n");
        if(og)
            fclose(og);
        free(buffer);
        return;
    }

    /*en caso que el archivo exista*/
    if (og != NULL){
        existia = 1;
        while(fgets(buffer, 1000, og) != NULL) {
            fputs(buffer,temp);
            cont_lineas ++;
            if(cont_lineas == 1)
                fputs(cancion, temp);
        } 
        fclose(og);
    }
    
     if (cont_lineas == 0){
        fputs(ENCABEZADO_FILA,temp);
        fputs(cancion,temp);
    }
    
    
    fclose(temp);
    free(buffer);

    /*En caso que el archivo exista */
    if (existia && remove("build/fila_reproduccion.csv") != 0) {
        printf("Error al eliminar el archivo original.\n");
        return;
    }

    if (rename("build/archivo_temporal.csv", "build/fila_reproduccion.csv") != 0){
        printf("Error al renombrar el archivo temporal.\n");
        return;
    }

    printf("Canción añadida al principio de la fila de reproducción. \n");
    
    
    return;
}

