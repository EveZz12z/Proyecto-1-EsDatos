#include "ordenamiento.h"
#include "prueba_interfaz.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {

    cancion canciones[6] = {

        {6, "Aquiesce", "Oasis", "The Masterplan", "Rock", 288, 1998, 18320},

        {5, "Aquiesce", "Oasis", "The Masterplan", "Rock", 288, 1998, 18320},

        {4, "Aquiesce", "Oasis", "The Masterplan", "Rock", 288, 1998, 18320},

        {2, "Hood", "Trueno", "Bien o Mal", "Hip-Hop", 178, 2022, 8730},

        {3, "Everlong", "Foo Fighters", "The Colour", "Rock", 250, 1997, 25000},

        {1, "Amigo", "Las Ardillas Azules", "No", "Funk", 195, 2026, 9992}
    };

    int n = 6;

    menu(canciones, n);
    return 0;
}