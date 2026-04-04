#ifndef global_h_ 
#define global_h_

#include <stdint.h> //para los int32_t, int16_t, int8_t
#include <stdbool.h> //para usar bool
#include <stddef.h>//para size_t??

/* =========================
        estructuras
   ========================= */

typedef struct coeff_t
{
    int32_t a;
    int32_t b;
    int32_t c;
} coeff_t;

typedef struct root_t
{
    int32_t real1;
    int32_t imag1;
    int32_t real2;
    int32_t imag2;
    bool complex;
} root_t;

typedef struct complex_t
{
    int32_t real;
    int32_t imag;
} complex_t;

typedef struct date_t
{
    int8_t day;
    int8_t month;
    int16_t year;
} date_t;

typedef struct matriz_t
{
    int16_t **data;
    size_t rows;
    size_t cols;
} matriz_t;

/* =========================
   declaraciones de las funciones print_<tipo> para mostrar la info de cada estructura
   ========================= */

void print_coeff_t(coeff_t coef); 
void print_root_t(root_t root);
void print_complex_t(complex_t c);
void print_date_t(date_t date);
void print_matriz_t(matriz_t matriz);

/* =========================
   Declaracion de las funciones pedidas
   ========================= */

void init_lab(void);
root_t * eq_solver(coeff_t *coeficientes);
int32_t bin2dec(char *binary, bool sign);
void print_reverse_array(void *array, size_t data_type, size_t array_size);
void max_index(void *array, size_t data_type, size_t array_size);
void min_index(void *array, size_t data_type, size_t array_size);
matriz_t * matrix_sub(matriz_t A, matriz_t B);
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
complex_t * sum(complex_t a, complex_t b);
complex_t * prod(complex_t a, complex_t b);
int days_left(date_t start, date_t finish);

#endif //eso que dijo el profesor que es buena practica definir con if not def,tuve que buscar y hay que cerrarlo asi 