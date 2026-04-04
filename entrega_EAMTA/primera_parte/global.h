#ifndef GLOBAL_H
#define GLOBAL_H

typedef struct { //defino la estructura de un numero imaginario
    int32_t real;
    int32_t imag;
} complex_t;

typedef struct {
    int8_t day;
    int8_t month;
    int16_t year;
} date_t;

/* ==========================================
   2. PROTOTIPOS DE FUNCIONES 
   ========================================== */

   int find_in_string(char *haystack, char *needle);

   void string_to_caps(char *string);

   void string_to_mins(char *string);

   complex_t *sum(complex_t a, complex_t b);

   complex_t *prod(complex_t a, complex_t b);

   int days_left(date_t start, date_t finish);

#endif // GLOBAL_H