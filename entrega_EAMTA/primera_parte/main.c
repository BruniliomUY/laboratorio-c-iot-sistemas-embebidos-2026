#include "global.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    
    //prueba_eq_solver
    coeff_t coef = {1, -5, 3};                // Coeficientes de la ecuación x^2 - 5x + 3 = 0
    print_coeff_t(coef);
    root_t* solucion = eq_solver(&coef);
    print_root_t(*solucion);
    void free(void *solucion); // Función para liberar la memoria asignada a la solución.

    //prueba_bin2dec
    char binary[] = "1010";
    int decimal = bin2dec(binary, false);
    printf("Binario: %s, Decimal: %d\n", binary, decimal);

    //prueba_print_reverse_array
    char *array[] = {"Hola", "Mundo", "C", "IoT"};
    size_t array_size = sizeof(array) / sizeof(array[0]); 
    print_reverse_array((void *)array, sizeof(char *), array_size);

    //prueba_max_index
    int array_1[] = {1, 5, 3, 9, 2};
    size_t array_size_1 = sizeof(array) / sizeof(array[0]);
    max_index(array_1, sizeof(int), array_size_1);

    //prueba_min_index
    min_index(array_1, sizeof(int32_t), array_size_1);

    //prueba_matrix_sub
    int16_t **m1 = malloc(2 * sizeof(int16_t*));
    int16_t **m2 = malloc(2 * sizeof(int16_t*));
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
    print_matriz_t(*resultado);
    for (int i = 0; i < 2; i++) {
        free(m1[i]);
        free(m2[i]);
    }
    free(m1);
    free(m2);

    /* ===== swap ===== */
    int a = 5, b = 10;
    printf("Swap 1:\n");
    printf("Antes: a=%d, b=%d\n", a, b);
    swap(&a, &b, sizeof(int));
    printf("Despues: a=%d, b=%d\n\n", a, b);

    int c = 7;
    printf("Swap 2:\n");
    swap(&c, &c, sizeof(int)); /* mismo elemento */
    printf("c=%d\n\n", c);

    /* ===== strings ===== */
    char texto1[] = "estoy testeando";
    char texto2[] = "     deberia   andar!      ";  /* varios espacios */

    printf("Texto 1: \"%s\"\n", texto1);
    printf("Consonantes: %d\n", consonantes(texto1));
    printf("Vocales: %d\n", vocales(texto1));
    printf("Largo: %d\n", string_length(texto1));
    printf("Palabras: %d\n\n", string_words(texto1));

    printf("Texto 2: \"%s\"\n", texto2);
    printf("Consonantes: %d\n", consonantes(texto2));
    printf("Vocales: %d\n", vocales(texto2));
    printf("Largo: %d\n", string_length(texto2));
    printf("Palabras: %d\n\n", string_words(texto2));

    /* ===== reverse ===== */
    char *inv1 = reverse_string(texto1);
    printf("Reverse 1: \"%s\"\n", inv1);
    free(inv1);

    char texto3[] = "a";
    char *inv2 = reverse_string(texto3); /* un solo caracter */
    printf("Reverse 2: \"%s\"\n\n", inv2);
    free(inv2);

    /* ===== string_copy ===== */
    char destino1[50];
    string_copy(texto1, destino1);
    printf("Copy 1: \"%s\"\n", destino1);

    char origen2[] = "";
    char destino2[10];
    string_copy(origen2, destino2); /* string vacia */
    printf("Copy 2: \"%s\"\n\n", destino2);

    /* ===== NULL ===== */
    printf("Consonantes(NULL): %d\n", consonantes(NULL));
    printf("Vocales(NULL): %d\n", vocales(NULL));
    printf("Largo(NULL): %d\n", string_length(NULL));
    printf("Palabras(NULL): %d\n", string_words(NULL));

    //Prueba de find_in_string
    printf("%d\n", find_in_string("Nicolas", "as"));
    
    //prueba de string_to_caps
    char string_a_convertir_a_caps[]= "Hola mundo, soy nico, EsToy PRoba&nDO que eSTO N0 S3 R0MP4\n";
    string_to_caps(string_a_convertir_a_caps);

    //prueba de string_to_mins
    char string_a_convertir_a_mins[]= "Hola mundo, soy nico, EsToy PRoba&nDO que eSTO N0 S3 R0MP4\n";
    string_to_min(string_a_convertir_a_mins);

    //prueba de sum
    complex_t a_c = {1, 2};
    complex_t b_c = {3, 4};
    complex_t *result = sum(a_c, b_c);
    printf("Resultado: %d + %di\n", result->real, result->imag);
    //O
    complex_t *result2 = sum((complex_t){1, 2}, (complex_t){3, 4});
    printf("Resultado: %d + %di\n", result2->real, result2->imag);
    free(result);
    free(result2);

    //prueba de prod
    complex_t c_c = {1, 2};
    complex_t d_c = {3, 4};
    complex_t *result3 = prod(c_c, d_c);
    printf("Resultado: %d + %di\n", result3->real, result3->imag);
    free(result3);
    //O
    complex_t *result4 = prod((complex_t){1, 2}, (complex_t){3, 4});
    printf("Resultado: %d + %di\n", result4->real, result4->imag);
    free(result4);

    //Prueba de days_left
     date_t start;
     start.day=27;
     start.month=5;
     start.year=0;
    
    date_t finish;
     finish.day=27;
     finish.month=5;
     finish.year=9999;

    printf("Dias restantes: %d\n", days_left(start, finish));
    //O
    printf("Dias restantes: %d\n", days_left((date_t){27, 5, 0}, (date_t){27, 5, 9999}));
    
    return 0;
}


