#include "global.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    
    //prueba_eq_solver
    coeff_t coef = {1, -5, 3};                // Coeficientes de la ecuación x^2 - 5x + 3 = 0
    root_t* solucion = eq_solver(&coef);
    printf("Raíz 1: %d + %di\n", solucion->real1, solucion->imag1);
    printf("Raíz 2: %d + %di\n", solucion->real2, solucion->imag2);
    void free(void *solucion); // Función para liberar la memoria asignada a la solución.

    //prueba_bin2dec
    char binary[] = "1010";
    int32_t decimal = bin2dec(binary, false);
    printf("Binario: %s, Decimal: %d\n", binary, decimal);

    //prueba_print_reverse_array(void *array,size_t data_type,size_t array_size)
    char *array[] = {"Hola", "Mundo", "C", "IoT"};
    size_t array_size = sizeof(array) / sizeof(array[0]); 
    print_reverse_array((void *)array, sizeof(char *), array_size);

    //prueba_max_index
    int32_t array_1[] = {1, 5, 3, 9, 2};
    size_t array_size_1 = sizeof(array) / sizeof(array[0]);
    max_index(array_1, sizeof(int32_t), array_size_1);

    //prueba_min_index
    min_index(array_1, sizeof(int32_t), array_size_1);
    return 0;
    
    //prueba_matrix_sub
    int16_t **m1;
    int16_t **m2;
    m1 = malloc(2 * sizeof(int16_t*));       //Crea las filas
    
    for (int i = 0; i < 2; i++) {            //Crea las columnas para cada fila
        m1[i] = malloc(2 * sizeof(int16_t));
    }
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;

    m2 = malloc(2 * sizeof(int16_t*));
    for (int i = 0; i < 2; i++) {
        m2[i] = malloc(2 * sizeof(int16_t));
    }
    m2[0][0] = 4;
    m2[0][1] = 3;       
    m2[1][0] = 2;
    m2[1][1] = 1;

    matriz_t A = {m1, 2, 2};
    matriz_t B = {m2, 2, 2};
    matriz_t *resultado = matrix_sub(A, B);
    for (size_t i = 0; i < resultado->rows; i++) {
        for (size_t j = 0; j < resultado->cols; j++) {
            printf("%d ", resultado->data[i][j]);
        }
        printf("\n");

    }
    void free(void *m1);
    void free(void *m2);
}
