#include <stdlib.h>
#include <stdio.h>
#include "pq.h" // Incluye el archivo de cabecera para la cola de prioridades

#define TOTAL_CHARS 256 // Define el total de caracteres posibles en ASCII extendido

int main(int argc, char* argv[]) {
    // Verifica que el nombre del archivo se haya pasado como argumento
    if (argc != 2) {
        printf("Forma de uso:\n");
        printf("\t%s nombre_de_archivo.txt\n", argv[0]); // Indica cómo usar el programa
        return 1; // Sale del programa si no se cumple la condición
    }

    int frequencies[TOTAL_CHARS] = {0}; // Inicializa un arreglo para contar las frecuencias de cada carácter
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
    fclose(file); // Cierra el archivo

    PQ* pq = pq_create(); // Crea una cola de prioridades
    if (pq == NULL) { // Verifica si hubo un error al crear la cola de prioridades
        printf("No se pudo crear la cola de prioridades.\n");
        return 1; // Sale del programa si no se puede crear la cola de prioridades
    }

    // Recorre el arreglo de frecuencias
    for (int i = 0; i < TOTAL_CHARS; i++) {
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
        printf("%c = %d\n", *charValue, frequencies[*charValue]); // Imprime el carácter y su frecuencia
        free(charValue); // Libera la memoria asignada para el valor del carácter
    }

    pq_destroy(pq); // Destruye la cola de prioridades y libera la memoria asociada
    return 0; // Termina el programa
}
