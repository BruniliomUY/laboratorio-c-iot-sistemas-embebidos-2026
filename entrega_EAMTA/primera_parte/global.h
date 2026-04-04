#ifndef GLOBAL_H
#define GLOBAL_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* ==========================================
   1. DEFINICIÓN DE TIPOS 
   ========================================== */
typedef struct { //Coeficientes de la ecuación de segundo grado.
    int32_t  a;  //Coeficiente del término cuadrático.
    int32_t  b;  //Coeficiente del término lineal.
    int32_t  c;  //Coeficiente del término independiente.
} coeff_t; 

typedef struct {
    int32_t  real1;   //Parte real de la primera raíz.    
    int32_t  imag1;   //Parte imaginaria de la primera raíz.
    int32_t  real2;   //Parte real de la segunda raíz.
    int32_t  imag2;   //Parte imaginaria de la segunda raíz.
    bool     complex; //Indica si las raíces son complejas o reales.
} root_t; //Estructura para representar una raíz compleja.

typedef struct {
    int16_t ** data;  //Puntero  o mapa de la matris.
    size_t rows;     // Número de filas
    size_t cols;     // Número de columnas
} matriz_t;          //Estructura para representar matrices.



/* ==========================================
   2. PROTOTIPOS DE FUNCIONES 
   ========================================== */
void init_lab(void); //Imprime los nombres de los integrantes del grupo. 

root_t* eq_solver(coeff_t *coeficientes ); //Recibe un arreglo de coeficientes y devuelve un arreglo con las raíces de la ecuación.

int32_t bin2dec(char *binary,bool sign);  //Recibe un número binario en formato string y un booleano que indica si el número es con signo o sin signo, y devuelve su equivalente en decimal.

void print_reverse_array(void *array,size_t data_type,size_t array_size); //Imprime el array en orden inverso usando puntero genérico.

void max_index(void *array, size_t data_type, size_t array_size); //Imprime el índice y valor máximo del array.

void min_index(void *array, size_t data_type, size_t array_size); //Imprime el índice y valor mínimo del array.

matriz_t* matrix_sub (matriz_t A,matriz_t B); //Recibe dos matrices A y B, y devuelve la matriz resultante de restar B a A.

int swap(void *elem_1, void *elem_2, size_t data_type);

int consonantes(char *string);

int vocales(char *string);

char * reverse_string(char *string);

int32_t string_length(char *string);

int32_t string_words(char *string);

int string_copy(char *source, char *destination);

#endif //eso que dijo el profesor que es buena practica definir con if not def,tuve que buscar y hay que cerrarlo asi 