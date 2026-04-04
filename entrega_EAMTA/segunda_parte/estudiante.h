#ifndef  ESTUDIANTE_H
#define  ESTUDIANTE_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* ==========================================
   1. DEFINICIÓN DE TIPOS 
   ========================================== */
typedef struct estudiante_t{                 //Definicion de nodo 
    char        nombre[64];      //Nombre del estudiante 
    char        apellido[64];    //Apellido del estudiante
    uint32_t    ci;              //Ci del estudiante
    uint8_t     grado;           //Año que cursa 
    float       promedio;        //Promedio de calificación (0.0 – 100.0)
}estudiante_t;

typedef struct node{
    estudiante_t data;
    struct node *link;
}node;


/* ==========================================
   2. PROTOTIPOS DE FUNCIONES 
   ========================================== */

void agregar_estudiante(char nombre[64],char apellido[64],uint32_t ci,uint8_t grado,float promedio);

void elimina_estudiante(uint32_t ci);

void mostrar_lista();

void mostrar_estudiante_ci(uint32_t ci);

void mostrar_estudiante_nombre(uint32_t nombre);

void ordenar_lista_apellido();

void ordenar_lista_ci();

void letra_promedio(uint32_t nombre);

#endif // ESTUDIANTE_H