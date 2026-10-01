/**
 * @file fila_de_reproduccion.h
 * @author Yanira Mansilla (you@domain.com)
 * @brief Archivo
 * 
 */
#ifndef FILA_DE_REPRODUCCION
#define FILA_DE_REPRODUCCION

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void vaciar_fila(Cancion filas[MAX_CANCIONES]);
int detectar_id(Cancion filas[MAX_CANCIONES], int id);
int anadir_cancion(Cancion filas[MAX_CANCIONES], Cancion cancion);
void consultar_fila(Cancion filas[MAX_CANCIONES]);
int buscar_indice_por_id(Cancion filas[MAX_CANCIONES], int id);
int eliminar_cancion_por_id_de_fila(Cancion filas[MAX_CANCIONES], Cancion cancion);




#endif

