#include <stdlib.h>
#include <stdio.h>
#include "pq.h"

#define SIZE 256 //Valores ASCII (Todos los caracteres posibles a encontrar en el .txt)

int main(int argc, char* argv[]) {
    // Verifica que el nombre del archivo se haya pasado como argumento
    if (argc != 2) {
        printf("Forma de uso:\n");
        printf("\t%s nombre_de_archivo.txt\n", argv[0]);
        return 1;
    }

    int frequencies[SIZE] = {0}; // Inicializa un arreglo para contar las frecuencias de cada carácter
    FILE* file = fopen(argv[1], "r"); // Abre el archivo de texto para lectura
    if (file == NULL) { // Verifica si hay un error al abrir el archivo
        printf("Error al abrir el archivo.\n");
        return 1; // Sale del programa si no se puede abrir el archivo
    }

    char c; // Variable para almacenar los caracteres leídos del archivo

    // Lee el archivo caracter por caracter hasta el final del archivo (EOF)
    while ((c = fgetc(file)) != EOF) {
        frequencies[(unsigned char)c]++; // Incrementa la frecuencia del carácter leído
    }
    fclose(file); // Cierra el archivo al llegar al final (EOF)

    PQ* pq = pq_create(); // Crea un PQ

    if (pq == NULL) { // Verifica si hubo un error al crear el PQ
        printf("No se pudo crear la cola de prioridades.\n");
        return 1; // Sale del programa si no se puede crear.
    }

    // Recorre el arreglo de frecuencias
    for (int i = 0; i < SIZE; i++) {
        if (frequencies[i] > 0) { // Si el carácter tiene al menos una ocurrencia
            int* charValue = malloc(sizeof(int)); // Reserva memoria para almacenar el valor del carácter
            *charValue = i; // Guarda el valor ASCII del carácter en la memoria asignada
            pq_add(pq, charValue, frequencies[i]); // Añade el carácter y su frecuencia a la cola de prioridades
        }
    }

    // Muestra las frecuencias de los caracteres en orden ascendente
    printf("Frecuencias de menor a mayor:\n");
    printf("Caracter | Frecuencia\n");
    while (pq_size(pq) > 0) { // Mientras haya elementos en la cola de prioridades
        int* charValue;
        pq_remove(pq, (void**)&charValue); // Extrae el elemento de menor prioridad (menor frecuencia)

        switch (*charValue) {
            case 10: // Salto de línea
                printf("Salto de Linea = %d\n", frequencies[*charValue]);
                break;
            case 32: // Espacio
                printf("Espacio = %d\n", frequencies[*charValue]);
                break;
            default: // Cualquier otro carácter
                printf("%c = %d\n", *charValue, frequencies[*charValue]); // Imprime el carácter y su frecuencia
                break;
        }

        free(charValue); // Libera la memoria asignada para el valor del carácter
    }


    pq_destroy(pq); // Destruye la cola de prioridades y libera la memoria asociada
    return 0; // Termina el programa
}