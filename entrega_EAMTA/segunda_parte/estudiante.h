#ifndef  ESTUDIANTE_H
#define  ESTUDIANTE_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
=========================
    Datos del estudiante.
=========================
*/
typedef struct estudiante_t{
    char nombre[64];
    char apellido[64];
    uint32_t ci;
    uint8_t grado;
    float promedio;
} estudiante_t;

/*
=========================
    Nodo de la lista enlazada simple.
=========================
*/
typedef struct nodo{
    estudiante_t estudiante;//El dato que guarda
    struct nodo *siguiente;//puntero al siguiente nodo
} nodo_t;

/*
*****************************************
    Funciones principales de la lista.
*****************************************
*/

/*
=========================
    Crea un nodo nuevo con los datos recibidos.
    Retorna un puntero al nodo creado.
    Si malloc falla, retorna NULL.
=========================
*/
nodo_t * crear_nodo(estudiante_t estudiante);

/*
=========================
    Inserta un estudiante al final de la lista.
    Recibe la direccion de la cabeza porque puede cambiar.
    Retorna 0 si sale bien y -1 si hay error.
=========================
*/
int insertar_estudiante(nodo_t **cabeza, estudiante_t estudiante);

/*
=========================
    Elimina un estudiante de la lista usando la CI.
    Retorna 0 si lo elimina y -1 si no lo encuentra o hay error.
=========================
*/
int eliminar_estudiante(nodo_t **cabeza, uint32_t ci);

/*
=========================
    Busca un estudiante por CI.
    Retorna el nodo si lo encuentra.
    Retorna NULL si no existe.
=========================
*/
nodo_t * buscar_por_ci(nodo_t *cabeza, uint32_t ci);

/*
=========================
    Busca un estudiante por nombre exacto.
    Retorna el nodo si lo encuentra.
    Retorna NULL si no existe.
=========================
*/
nodo_t * buscar_por_nombre(nodo_t *cabeza, char *nombre);

/*
=========================
    Muestra un estudiante en pantalla.
=========================
*/
void mostrar_estudiante(estudiante_t estudiante);

/*
=========================
    Muestra toda la lista.
=========================
*/
void mostrar_lista(nodo_t *cabeza);

/*
=========================
    Ordena la lista por apellido ascendente.
=========================
*/
void ordenar_por_apellido(nodo_t *cabeza);

/*
=========================
    Ordena la lista por CI ascendente.
=========================
*/
void ordenar_por_ci(nodo_t *cabeza);

/*
=========================
    Devuelve la letra correspondiente al promedio.
=========================
*/
char * letra_calificacion(float promedio);

/*
=========================
    Muestra cada estudiante con su letra de calificacion.
=========================
*/
void mostrar_calificaciones(nodo_t *cabeza);

/*
=========================
    Libera toda la memoria de la lista.
=========================
*/
void liberar_lista(nodo_t **cabeza);

#endif