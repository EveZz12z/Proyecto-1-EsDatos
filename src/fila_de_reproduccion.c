#include "fila_de_reproduccion.h"

void consultar_fila(int n){
    FILE* f;
    f = fopen("build/catalogo.csv","r");
    if (f == NULL){
        printf("Error: No se pudo abrir el archivo\n");
        return 1;
    }

    

    fclose(f);
    return;
}