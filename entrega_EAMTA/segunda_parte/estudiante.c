#include "estudiante.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
****************************************************************
    la idea de las listas enlazadas se inspiro en el video:
    https://www.youtube.com/watch?v=_WaoQWAcxw0

    aunque en el video usan una estructura tipo "lista" con una raiz (L.raiz),
    que complica el entendimiento.Aca se usa directamente un puntero a la cabeza (inicio) de la lista
*******************************************************************
*/

/*
=========================
  crear_nodo:
  crea un nodo nuevo para la lista enlazada y guarda los datos
  del estudiante recibido. El puntero siguiente arranca en NULL.
  parametros:
      estudiante: estructura con los datos del estudiante
  retorno:
      puntero al nodo creado, o NULL si malloc falla
=========================
*/
nodo_t *crear_nodo(estudiante_t estudiante)
{
    nodo_t *nuevo = (nodo_t *)malloc(sizeof(nodo_t));//al puntero nuevo se le asigna la direccion de memoria dinamica reservada para un nodo_t
    if (nuevo == NULL)
    {
        return NULL; //si fallo el malloc
    }

    nuevo->estudiante = estudiante;//guarda en el nodo al que apunta nuevo el estudiante 
    nuevo->siguiente = NULL;//apunta el puntero siguiente a null (a nada)

    return nuevo;//retorna la direccion del nuevo nodo
}

/*
=========================
  insertar_estudiante:
  inserta un estudiante al final de la lista enlazada.
  Si la lista esta vacia, el nuevo nodo pasa a ser la cabeza.
  Tambien revisa que no se repita la cedula.
  parametros:
      cabeza: direccion del puntero a la cabeza de la lista
      estudiante: datos del estudiante a insertar
  retorno:
      0 si salio bien, -1 si hubo error
=========================
*/
int insertar_estudiante(nodo_t **cabeza, estudiante_t estudiante)//el puntero doble significa que se recibe la dirección de una variable que guarda la dirección del primer nodo
{//eso es para poder modifica el puntero cabeza osea que nodo es el primero 
    nodo_t *nuevo;
    nodo_t *actual;

    if (cabeza == NULL)
    {
        return -1;//si hubo un error
    }

    if (buscar_por_ci(*cabeza, estudiante.ci) != NULL)//para evitar subir el mismo estudiante de nuevo
    {
        return -1;
    }

    nuevo = crear_nodo(estudiante);

    if (*cabeza == NULL)//si al lista esta vacia "nuevo" es la cabeza ahora 
    {
        *cabeza = nuevo;
        return 0;
    }

    actual = *cabeza;//si la lista no esta vacia el nodo "actual" (auxiliar para el while) es ese primer nodo "cabeza"

    while (actual->siguiente != NULL)//recorremos la lista hasta llegar al final osea cuando el puntero de siguiente de un nodo sea null
    {
        actual = actual->siguiente;//pasa al siguiente nodo
    }

    actual->siguiente = nuevo;// el ultimo nodo ahora apunta su puntero "siguiente" al nuevo nodo

    return 0;
}

/*
=========================
  eliminar_estudiante:
  elimina un estudiante de la lista usando la cedula.
  Hay que contemplar si el nodo a borrar es el primero
  o si esta en el medio/final de la lista.
  parametros:
      cabeza: direccion del puntero a la cabeza de la lista
      ci: cedula del estudiante a eliminar
  retorno:
      0 si lo elimino correctamente, -1 si no lo encontro o hubo error
=========================
*/
int eliminar_estudiante(nodo_t **cabeza,uint32_t ci){
    nodo_t *ptr = *cabeza; // Declaramos ptr y lo igualamos al inicio
    nodo_t *anterior = NULL;
    // Caso 1: La lista está vacía
    if (*cabeza == NULL) return 1;
    // Caso 2: El estudiante a eliminar es el primero (el head)
    if (ptr != NULL && ptr->estudiante.ci == ci) {
        *cabeza = ptr->siguiente; // El segundo pasa a ser el primero
        free(ptr);        // Liberamos la memoria del nodo eliminado
        return 1;
    }
    // Caso 3: Buscar el estudiante en el resto de la lista
    while (ptr != NULL && ptr->estudiante.ci != ci) {
        anterior = ptr;    // Guardamos el actual como anterior
        ptr = ptr->siguiente;   // Avanzamos al siguiente
    }
    // Si ptr es NULL, es porque recorrimos toda la lista y no encontramos la CI
    if (ptr == NULL) {
        printf("Estudiante con CI %u no encontrado.\n", ci);
        return 1;
    }
    // "Saltamos" el nodo actual conectando el anterior con el siguiente
    anterior->siguiente = ptr->siguiente;
    
    // Liberamos la memoria para evitar fugas (memory leaks)
    free(ptr);
    }
/*
=========================
  mostrar_lista:
  muestra todos los estudiantes de la lista.
  parametros:
      cabeza: direccion del puntero a la cabeza de la lista
  retorno:
        no retorna nada, solo imprime los datos de cada estudiante
=========================
*/
void mostrar_lista(nodo_t *cabeza) {
    nodo_t *ptr = cabeza; // Declaramos ptr y lo igualamos al inicio
    while (ptr != NULL) {
        printf("Nombre: %s | Apellido: %s | CI: %u | Grado: %hhu | Promedio: %.2f\n", 
               ptr->estudiante.nombre, 
               ptr->estudiante.apellido, 
               ptr->estudiante.ci, 
               ptr->estudiante.grado, 
               ptr->estudiante.promedio);
        ptr = ptr->siguiente; // Avanzamos al siguiente nodo
    }
}
/*
=========================
  mostrar_estudiante:
  muestra todos los estudiantes de la lista.
  parametros:
      cabeza: direccion del puntero a la cabeza de la lista
  retorno:
        no retorna nada, solo imprime los datos de cada estudiante
=========================
*/
void mostrar_estudiante(estudiante_t estudiante) {
    printf("Nombre: %s | Apellido: %s | CI: %u | Grado: %hhu | Promedio: %.2f\n", 
           estudiante.nombre, 
           estudiante.apellido, 
           estudiante.ci, 
           estudiante.grado, 
           estudiante.promedio);
}
/*
=========================
  buscar_por_ci:
  recorre la lista y busca un estudiante por su cedula.
  parametros:
      cabeza: puntero al primer nodo de la lista
      ci: cedula del estudiante a buscar
  retorno:
      puntero al nodo encontrado o NULL si no encuentra
=========================
*/
nodo_t *buscar_por_ci(nodo_t *cabeza, uint32_t ci)
{
    nodo_t *actual = cabeza;//puntero auxiliar.empieza en el primer nodo (la "cabeza")

    while (actual != NULL)
    {
        if (actual->estudiante.ci == ci)
        {
            return actual;
        }
        actual = actual->siguiente;//el puntero actual pasa a apuntar a la dirección a la que apunta siguiente (al siguiente nodo)
    }

    return NULL;
}

/*
=========================
  buscar_por_nombre:
  recorre la lista y busca un estudiante por nombre exacto.
  Si hay varios con el mismo nombre, devuelve el primero.
  parametros:
      cabeza: puntero al primer nodo de la lista
      nombre: nombre a buscar
  retorno:
      puntero al nodo encontrado o NULL si no encuentra
=========================
*/
nodo_t *buscar_por_nombre(nodo_t *cabeza, char *nombre)
{
    nodo_t *actual = cabeza;

    while (actual != NULL)
    {
        if (strcmp(actual->estudiante.nombre, nombre) == 0)//usa str compare para ver si el nombre del estudiante que está guardado en ese nodo al que apunta actual es igual al nombre buscado
        {//strcmp devuelve 0 si son iguales
            return actual;
        }
        actual = actual->siguiente;
    }

    return NULL;
}

/*
=========================
  ordenar_por_apellido:
    ordena la lista por apellido de forma ascendente.
    no mueve nodos sino que cambia los datos
    de los estudiantes entre nodos.
  parametros:
      cabeza: direccion del puntero a la cabeza de la lista
  retorno:
      no retorna nada
=========================
*/
void ordenar_por_apellido(nodo_t *cabeza)
{
    int cambio = 1;//se usa como flag 1 es hay un cambio,seguir revisandoo o 0 no hubo cambio
    nodo_t *actual;
    estudiante_t aux;//para guardar temporalmente un estudiante

    if (cabeza == NULL)//si la lista esta vacia
    {
        return;
    }

    while (cambio != 0)//la idea es si en una pasada no hay cambios ,la lista esta ordenada, sino hay que volver a revisar
    {
        cambio = 0;
        actual = cabeza;

        while (actual->siguiente != NULL)
        {
            if (strcmp(actual->estudiante.apellido, actual->siguiente->estudiante.apellido) > 0)//supuestamente strcmp funciona dando 0 si son iguales. < 0 si el primero va antes o > 0 si el segundo va antes alfabeticamente
            {
                aux = actual->estudiante;//te guardas el estudiante actual en el auxiliar
                actual->estudiante = actual->siguiente->estudiante;//ahora en "actual" te guardas al estudiante del nodo siguiente (copias el nodo siguiente)
                actual->siguiente->estudiante = aux;//en el nodo siguiente al actual guardas el estudiante que estaba en "auxiliar" osea el estudiante original de actual.Intercambiando asi lugares para ir ordenando alfabeticamente en cada pasada 
                cambio = 1;
            }

            actual = actual->siguiente;
        }
    }
}

/*
=========================
  ordenar_por_ci:
  ordena la lista por cedula de menor a mayor.
  Igual que en la funcion anterior, se intercambian
  los datos de los estudiantes y no los nodos.
  parametros:
      cabeza: direccion del puntero a la cabeza de la lista
  retorno:
      no retorna nada
=========================
*/
void ordenar_por_ci(nodo_t *cabeza)
{
    int cambio = 1;
    nodo_t *actual;
    estudiante_t aux;

    if (cabeza == NULL)
    {
        return;
    }

    while (cambio)
    {
        cambio = 0;
        actual = cabeza;

        while (actual->siguiente != NULL)
        {
            if (actual->estudiante.ci > actual->siguiente->estudiante.ci)
            {
                aux = actual->estudiante;
                actual->estudiante = actual->siguiente->estudiante;
                actual->siguiente->estudiante = aux;
                cambio = 1;
            }

            actual = actual->siguiente;
        }
    }
}

/*
=========================
  liberar_lista:
  libera toda la memoria dinamica reservada para la lista.
  Va borrando nodo por nodo hasta dejar la cabeza en NULL.
  parametros:
      cabeza: direccion del puntero a la cabeza de la lista
  retorno:
      no retorna nada
=========================
*/
void liberar_lista(nodo_t **cabeza)
{
    nodo_t *actual;
    nodo_t *temp;//guarda el nodo a guardar 

    if (cabeza == NULL)//como se ha usado en tras funcione si al direccion es invalida retorna null 
    {
        return;
    }

    actual = *cabeza;

    while (actual != NULL)
    {
        temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
// primero se avanza al siguiente nodo y luego se libera "actual" porque si se libera antes ya no se sabe quien es actual->siguiente
    *cabeza = NULL;
}
