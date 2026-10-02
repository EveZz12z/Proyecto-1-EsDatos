# Reproductor de Música

Proyecto desarrollado en C para la asignatura de Estructura de Datos.

El programa simula un reproductor de música utilizando arreglos para administrar un catálogo de canciones, realizar búsquedas y ordenamientos, generar rankings, utilizar una fila de reproducción, mantener un historial y exportar los datos actualizados a archivos CSV.

---

## Integrantes

- Nombre integrante 1
- Nombre integrante 2
- Nombre integrante 3

---

## Funcionalidades

El programa permite:

- Generar un catálogo de canciones aleatorias.
- Cargar un catálogo previamente generado desde un archivo CSV.
- Mostrar las canciones almacenadas.
- Listar los artistas disponibles.
- Listar y consultar géneros musicales.
- Contar canciones pertenecientes a un género.
- Ordenar las canciones por:
  - ID.
  - Título.
  - Artista.
  - Álbum.
  - Género.
  - Duración.
  - Año.
  - Número de reproducciones.
- Buscar canciones por:
  - ID.
  - Título.
  - Artista.
- Mostrar todas las canciones pertenecientes a un artista.
- Generar un ranking de las canciones más reproducidas.
- Obtener la canción más escuchada de un artista.
- Obtener la canción más escuchada de un género.
- Agregar canciones a una fila de reproducción.
- Consultar la fila de reproducción.
- Eliminar canciones de la fila.
- Vaciar la fila de reproducción.
- Reproducir canciones.
- Mantener un historial de las últimas canciones reproducidas.
- Exportar el catálogo actualizado a un archivo CSV.

---

## Algoritmos utilizados

Durante el desarrollo del proyecto se implementaron distintos algoritmos estudiados durante la asignatura.

### Ordenamiento iterativo

Se implementó **Selection Sort**, permitiendo seleccionar el atributo de la canción por el cual se desea ordenar el catálogo.

### Ordenamiento recursivo

Se implementó **Merge Sort**, utilizando recursividad para dividir el catálogo y posteriormente unir las secciones ordenadas.

### Búsqueda

Se implementó **Búsqueda Binaria Recursiva** para realizar búsquedas sobre arreglos previamente ordenados.

Para algunas consultas donde pueden existir múltiples coincidencias, como mostrar todas las canciones de un artista, se realiza un recorrido del catálogo completo.

---

## Estructura del proyecto

```text
Proyecto/
│
├── src/
│   ├── main.c
│   ├── catalogo.c
│   ├── importacion.c
│   ├── exportacion.c
│   ├── ordenamiento.c
│   └── fila_de_reproduccion.c
│
├── inc/
│   ├── canciones.h
│   ├── catalogo.h
│   ├── importacion.h
│   ├── exportacion.h
│   ├── ordenamiento.h
│   └── fila_de_reproduccion.h
│
├── catalogo.csv
├── Makefile
└── README.md