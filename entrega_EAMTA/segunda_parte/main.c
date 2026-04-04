#include "estudiante.h"
#include <stdio.h>
#include <stdint.h>

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
            "8) Salir\n"
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
            agregar_estudiante(nombre_t,apellido_t,ci_t, grado_t,promedio_t);
        }else if(select == 5){
            mostrar_lista();
        }
    }
}
