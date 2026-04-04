#include "estudiante.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


node *head = NULL;

void agregar_estudiante(char nombre[64],char apellido[64],uint32_t ci,uint8_t grado,float promedio){
    node *nuevo = malloc(sizeof(node));
    if (nuevo == NULL) return;

    strcpy(nuevo->data.nombre, nombre);
    strcpy(nuevo->data.apellido, apellido);
    nuevo->data.ci = ci;
    nuevo->data.grado = grado;
    nuevo->data.promedio = promedio;

    nuevo->link = head;
    head = nuevo;
}

void elimina_estudiante(uint32_t ci){
    node *ptr = head; // Declaramos ptr y lo igualamos al inicio
    node *anterior = NULL;
    // Caso 1: La lista está vacía
    if (head == NULL) return;
    // Caso 2: El estudiante a eliminar es el primero (el head)
    if (ptr != NULL && ptr->data.ci == ci) {
        head = ptr->link; // El segundo pasa a ser el primero
        free(ptr);        // Liberamos la memoria del nodo eliminado
        return;
    }
    // Caso 3: Buscar el estudiante en el resto de la lista
    while (ptr != NULL && ptr->data.ci != ci) {
        anterior = ptr;    // Guardamos el actual como anterior
        ptr = ptr->link;   // Avanzamos al siguiente
    }
    // Si ptr es NULL, es porque recorrimos toda la lista y no encontramos la CI
    if (ptr == NULL) {
        printf("Estudiante con CI %u no encontrado.\n", ci);
        return;
    }
    // "Saltamos" el nodo actual conectando el anterior con el siguiente
    anterior->link = ptr->link;
    
    // Liberamos la memoria para evitar fugas (memory leaks)
    free(ptr);
    }
void mostrar_lista() {
    node *ptr = head; // Declaramos ptr y lo igualamos al inicio
    while (ptr != NULL) {
        printf("Nombre: %s | Apellido: %s | CI: %u | Grado: %hhu | Promedio: %.2f\n", 
               ptr->data.nombre, 
               ptr->data.apellido, 
               ptr->data.ci, 
               ptr->data.grado, 
               ptr->data.promedio);
        ptr = ptr->link; // Avanzamos al siguiente nodo
    }
}

