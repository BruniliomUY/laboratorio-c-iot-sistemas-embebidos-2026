#include "estudiante.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int select = 0;
    while (select != 8){
    printf("Lista de estudiantes\n"
            "Menu:\n"
            "1) Agregar estudiante\n"
            "2) Quitar estudiante\n"
            "3) Ordenar y mostrar lista segun CI\n"
            "4) Ordenar y mostrar lista segun apellido\n"
            "5) Mostrar lista\n"
            "6) Mostrar estudiante\n"
            "7) Mostrar promedios\n"
            "8) Liberar lista\n"
            "Seleccione una opcion: ");
    scanf("%i",&select);
        if (select == 1){
            char apellido_t[64];
            char nombre_t[64];
            uint32_t ci_t;
            uint8_t grado_t;
            float promedio_t;
            printf("___DATOS___\n");
            printf("Apellido:");
            scanf("%63s",apellido_t);
            printf("\nNombre:");
            scanf("%63s",nombre_t);
            printf("\nCI:");
            scanf("%u",&ci_t);
            printf("\nGrado:");
            scanf("%hhu",&grado_t);
            printf("\nPromedio:");
            scanf("%f",&promedio_t);
            estudiante_t estudiante = {0};
            strncpy(estudiante.nombre, nombre_t, sizeof(estudiante.nombre) - 1);
            strncpy(estudiante.apellido, apellido_t, sizeof(estudiante.apellido) - 1);
            estudiante.ci = ci_t;
            estudiante.grado = grado_t;
            estudiante.promedio = promedio_t;
            insertar_estudiante(&cabeza, estudiante);
        }else if(select == 2){
            uint32_t ci_a_eliminar;
            printf("\n========================================\n");
            printf("ELIMINACION DE ESTUDIANTE\n");
            printf("========================================\n");
            printf("Ingrese la CI del estudiante a eliminar: ");
            scanf("%u", &ci_a_eliminar);
             if (eliminar_estudiante(&cabeza, ci_a_eliminar) == 0)
                 printf("Se elimino correctamente\n");
             else
                 printf("No se pudo eliminar el estudiante.\n");
        }else if(select == 3){
            printf("\n========================================\n");
            printf("LISTA ORDENADA POR CI\n");
            printf("========================================\n");
            ordenar_por_ci(cabeza);
            mostrar_lista(*cabeza);
        }else if(select == 4){
            printf("\n========================================\n");
            printf("LISTA ORDENADA POR APELLIDO\n");
            printf("========================================\n");
            ordenar_por_apellido(cabeza);
            mostrar_lista(*cabeza);
        }else if(select == 5){
            printf("\n========================================\n");
            printf("LISTA ORIGINAL\n");
            printf("========================================\n");
            mostrar_lista(*cabeza);
        }else if(select == 6){ 
             printf("\n========================================\n");
            printf("BUSQUEDA POR NOMBRE/CEDULA\n");
            printf("========================================\n");
            printf("1) Busqueda por CI\n");
            printf("2) Busqueda por nombre\n");
            int subselect;
            scanf("%d", &subselect);
            if (subselect == 1){
                uint32_t ci;
                printf("Ingrese la CI del estudiante a buscar: ");
                scanf("%u", &ci);
                buscar_por_ci(nodo_t *cabeza, uint32_t ci);
            }else if (subselect == 2){
                char nombre[64];
                printf("Ingrese el nombre del estudiante a buscar: ");
                scanf("%63s", nombre);
                buscar_por_nombre(nodo_t *cabeza, char *nombre);
            }
            mostrar_estudiante(estudiante_t estudiante);
        }else if(select == 7){
            printf("\n========================================\n");
            printf("CALIFICACIONES\n");
            printf("========================================\n");
            mostrar_calificaciones(nodo_t *cabeza);;
        }else if(select == 8){
            printf("\n========================================\n");
            printf("LIBERANDO MEMORIA\n");
            printf("========================================\n");
            liberar_lista(&cabeza);
            if (cabeza == NULL){
                printf("La lista fue liberada correctamente.\n");
            }else{
                printf("Hubo un problema al liberar la lista.\n");
            }
            return 0;
        }
    }
}
