#include "global.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

void init_lab(void) {
    printf("Integrantes del grupo:\n");
    printf("Nicolas Mayer\n");
    printf("Victoria Amor\n");
    printf("Bruno Moreira\n");
}

root_t eq_solver(coeff_t *coeficientes) {
    root_t solucion;  // Asignamos var local para almacenar la solución
    
    double a = (double)coeficientes->a; // Convertimos a double para mayor precisión en el cálculo intermedio
    double b = (double)coeficientes->b;
    double c = (double)coeficientes->c;

	double discriminante = coeficientes->b*coeficientes->b - 4*coeficientes->a*coeficientes->c;// Calculamos el discriminante.
	double x1 = (-coeficientes->b + sqrt(discriminante)) / (2.0 * coeficientes->a);          // Calculamos la primera raíz usando el método de Bhaskara.
	double x2 = (-coeficientes->b - sqrt(discriminante)) / (2.0 * coeficientes->a);          // Calculamos la segunda raíz usando el método de Bhaskara.

    //Segun el metodo de Bhaskara y el discriminante, asignamos los valores a la estructura de solución.
	if (discriminante > 0) {
        solucion.real1 = (int32_t)x1;
        solucion.imag1 = 0;
        solucion.real2 = (int32_t)x2;
        solucion.imag2 = 0;
        solucion.complex = false;
	} else if (discriminante < 0) {
		solucion.real1 = (int32_t)(-b / (2.0 * a));
        solucion.imag1 = (int32_t)(sqrt(-discriminante) / (2.0 * a));
        solucion.real2 = (int32_t)(-b / (2.0 * a));
        solucion.imag2 = (int32_t)(-sqrt(-discriminante) / (2.0 * a));
        solucion.complex = true;
	} else {
		solucion.real1 = (int32_t)(-b / (2.0 * a));
        solucion.imag1 = 0;
        solucion.real2 = (int32_t)(-b / (2.0 * a));
        solucion.imag2 = 0;
        solucion.complex = false;
	}
    return solucion;  
}

int32_t bin2dec(char *binary,bool sign) {
    int32_t num_dec = 0;                                   //Variable para almacenar el número decimal resultante.
    size_t len = strlen(binary);                        //Longitud del número binario para iterar sobre cada dígito.

    for (int i = 0; i < len; i++) {                        //Iteramos para calcular el valor de cada digito.
        if (binary[i] == '1') {              
            num_dec = num_dec + pow(2, len - 1 - i); //Desplazamos el puntero y sumamos la potencia de 2 correspondiente al encontrar un 1.
        }
    }
    if (sign && binary[0] == '1') {                       //Unsigned o Signed.
        num_dec = -num_dec;
    }
    return num_dec;
}

void print_reverse_array(void *array,size_t data_type,size_t array_size) {
    uint8_t *pa = (uint8_t *)array;                 //Puntero generico que recorre el array por byte. 
    printf("Array en orden inverso:\n{");   //Marca el inicio de el array invertido.
    for (int i = array_size - 1; i >= 0; i--) {    //Iteramos el array restando 1 al indice.
        uint8_t *actual = pa + (i * data_type);    //Calculamos la dirección del elemento actual teniendo en cuenta el tamaño del tipo de dato.
        printf("%s", *(char **)actual);    //Imprimimos el valor del elemento actual.
    }
    printf("}\n");
    }

void max_index(void *array, size_t data_type, size_t array_size) {
    uint8_t *pa = (uint8_t *)array;                            //Puntero generico que recorre el array por byte. 
    int32_t max_val = *(int32_t *)pa;                          //Inicializamos el valor máximo con el primer elemento del array.
    size_t  max_indx = 0;                                      //Definimos variable para almacenar el indice.
             
    for (size_t i = 1; i < array_size; i++){                   //Interamos para recorrer el array y comparar.       
        int32_t *val_ptr = (int32_t *)(pa + (i * data_type));  //Calculamos la dirección del elemento actual teniendo en cuenta el tamaño del tipo de dato.
        int32_t  valor_actual = *val_ptr;
        if (valor_actual > max_val) {                          //Almacenamos si el valor actual es mayor que el max anterior.
            max_val = valor_actual;
            max_indx = i;                                      //Almacenamos el indice del nuevo valor máximo.
        }
      }
        printf("Indice max: %d\n", max_indx);           //Imprimimos el indice del valor máximo encontrado.
        printf("Valor max: %d\n", max_val);            //Imprimimos el valor máximo encontrado %d para int32_t.
    }

void min_index(void *array, size_t data_type, size_t array_size) { //Analoga a max_index pero para encontrar el valor mínimo y su indice.
    uint8_t *pa = (uint8_t *)array;                            
    int32_t min_val = *(int32_t *)pa;                          
    size_t  min_indx = 0;                                      

    for (size_t i = 1; i < array_size; i++){                    
        int32_t *val_ptr = (int32_t *)(pa + (i * data_type));  
        int32_t  valor_actual = *val_ptr;                       
        if (valor_actual < min_val) {
            min_val = valor_actual;
            min_indx = i;
        }
      }
        printf("Indice min: %d\n", min_indx);
        printf("Valor min: %d\n", min_val);
    }

matriz_t matrix_sub (matriz_t A,matriz_t B){
    size_t n_filas = A.rows;             //Definimos variables para almacenar el número de filas y columnas de las matrices A y B.
    size_t n_columna = A.cols;

    matriz_t matriz_error;               //Definimos una matriz de error para retornar en caso de que las dimensiones de las matrices no sean compatibles para la resta.
    matriz_error.rows = 0;
    matriz_error.cols = 0;
    matriz_error.data = NULL;            //Def NULL para respresentar la matriz de error.


    if (n_filas != B.rows || n_columna != B.cols) {
        return matriz_error;              // Retorna la matriz de error si las dimensiones no coinciden
    }
 
	matriz_t matriz_resultado;           //Definimos matriz resiltado.
    matriz_resultado.rows = n_filas;
    matriz_resultado.cols = n_columna;
    
	for (int i = 0; i < n_filas; i++) {  //Recorremos las 2 matrices y las restamos con 2 for anidados.
		for (int j = 0; j < n_columna; j++) {
			matriz_resultado.data[i][j] = A.data[i][j] - B.data[i][j];
		}
	}
	return matriz_resultado;            //Retornamos el resultado de la resta de las matrices.
}
 

