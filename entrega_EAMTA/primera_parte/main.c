#include "global.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    //Prueba de find_in_string
    printf("%d\n", find_in_string("Nicolas", "as"));
    
    //prueba de string_to_caps
    char string_a_convertir_a_caps[]= "Hola mundo, soy nico, EsToy PRoba&nDO que eSTO N0 S3 R0MP4";
    string_to_caps(string_a_convertir_a_caps);

    //prueba de string_to_mins
    char string_a_convertir_a_mins[]= "Hola mundo, soy nico, EsToy PRoba&nDO que eSTO N0 S3 R0MP4";
    string_to_mins(string_a_convertir_a_mins);

    //prueba de sum
    complex_t a = {1, 2};
    complex_t b = {3, 4};
    complex_t *result = sum(a, b);
    printf("Resultado: %d + %di\n", result->real, result->imag);
    //O
    complex_t *result2 = sum((complex_t){1, 2}, (complex_t){3, 4});
    printf("Resultado: %d + %di\n", result2->real, result2->imag);
    free(result);
    free(result2);

    //prueba de prod
    complex_t c = {1, 2};
    complex_t d = {3, 4};
    complex_t *result3 = prod(c, d);
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
