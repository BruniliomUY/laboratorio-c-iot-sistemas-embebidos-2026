#ifndef GLOBAL_H
#define GLOBAL_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* ==========================================
   1. TIPOS DE DATOS 
   ========================================== */
typedef enum {
    TYPE_INT32,
    TYPE_INT8,
    TYPE_UINT32,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_DOUBLE,
} data_type_t;

typedef struct {  //defino la estructura de un numero imaginario
    int32_t real; //Parte real del número complejo.
    int32_t imag; //Parte imaginaria del número complejo.
} complex_t;

typedef struct {
    int8_t day;   // Día del mes (1-31)
    int8_t month; // Mes del año (1-12)
    int16_t year; // Año (por ejemplo, 2024)
} date_t;

typedef struct { //Coeficientes de la ecuación de segundo grado.
    double  a;  //Coeficiente del término cuadrático.
    double  b;  //Coeficiente del término lineal.
    double  c;  //Coeficiente del término independiente.
} coeff_t; 

typedef struct {
    double  real1;   //Parte real de la primera raíz.    
    double  imag1;   //Parte imaginaria de la primera raíz.
    double  real2;   //Parte real de la segunda raíz.
    double  imag2;   //Parte imaginaria de la segunda raíz.
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
void print_element(void *elem, data_type_t type);

size_t get_size(data_type_t type);

void print_coeff_t(coeff_t coef);

void print_root_t(root_t root);

void print_complex_t(complex_t c);

void print_date_t(date_t date);

void print_matriz_t(matriz_t matriz); 

void init_lab(void); //Imprime los nombres de los integrantes del grupo. 

root_t* eq_solver(coeff_t *coeficientes ); //Recibe un arreglo de coeficientes y devuelve un arreglo con las raíces de la ecuación.

int32_t bin2dec(char *binary,bool sign);  //Recibe un número binario en formato string y un booleano que indica si el número es con signo o sin signo, y devuelve su equivalente en decimal.

void print_reverse_array(void *array,data_type_t type,size_t array_size); //Imprime el array en orden inverso usando puntero genérico.

int max_index(void *array, data_type_t type, size_t array_size); //Imprime el índice y valor máximo del array.

int min_index(void *array, data_type_t type, size_t array_size); //Imprime el índice y valor mínimo del array.

matriz_t* matrix_sub (matriz_t A,matriz_t B); //Recibe dos matrices A y B, y devuelve la matriz resultante de restar B a A.

int swap(void *elem_1, void *elem_2, size_t data_type);

int consonantes(char *string);

int vocales(char *string);

char * reverse_string(char *string);

int32_t string_length(char *string);

int32_t string_words(char *string);

int string_copy(char *source, char *destination);

int find_in_string(char *haystack, char *needle);

void string_to_caps(char *string);

void string_to_min(char *string);

complex_t *sum(complex_t a, complex_t b);

complex_t *prod(complex_t a, complex_t b);

int chequear_si_bisiesto(int anio);

int largo_del_mes(int month, int year);

int lo_que_va_del_anio(date_t fecha);

int days_left(date_t start, date_t finish);

#endif //eso que dijo el profesor que es buena practica definir con if not def,tuve que buscar y hay que cerrarlo asi 